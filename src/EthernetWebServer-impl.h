/****************************************************************************************************************************
   EthernetWebServer-impl.h - Dead simple web-server.
   For Ethernet shields

   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license

   Original author:
   @file       Esp8266WebServer.h
   @author     Ivan Grokhotkov
   
   Version: 1.7.1

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
    ...
    1.6.0   K Hoang      04/09/2021 Add support to QNEthernet Library for Teensy 4.1
    1.7.0   K Hoang      09/09/2021 Add support to Portenta H7 Ethernet
    1.7.1   K Hoang      04/10/2021 Change option for PIO `lib_compat_mode` from default `soft` to `strict`. Update Packages Patches
 *************************************************************************************************************************************/

#pragma once

#include <Arduino.h>
#include <libb64/cencode.h>
#include "EthernetWebServer.h"
#include "detail/RequestHandlersImpl.h"
#include "detail/Debug.h"
#include "detail/mimetable.h"

const char * AUTHORIZATION_HEADER = "Authorization";

EthernetWebServer::EthernetWebServer(int port)
  : _server(port)
  , _currentMethod(HTTP_ANY)
  , _currentVersion(0)
  , _currentHandler(0)
  , _firstHandler(0)
  , _lastHandler(0)
  , _currentArgCount(0)
  , _currentArgs(0)
  , _headerKeysCount(0)
  , _currentHeaders(0)
  , _contentLength(0)
  , _chunked(false)
{
}

EthernetWebServer::~EthernetWebServer() 
{
  if (_currentHeaders)
    delete[]_currentHeaders;
    
  _headerKeysCount = 0;
  RequestHandler* handler = _firstHandler;
  
  while (handler) 
  {
    RequestHandler* next = handler->next();
    delete handler;
    handler = next;
  }
  
  close();
}

void EthernetWebServer::begin() 
{
  _currentStatus = HC_NONE;
  _server.begin();
  
  if (!_headerKeysCount)
    collectHeaders(0, 0);
}

bool EthernetWebServer::authenticate(const char * username, const char * password) 
{
  if (hasHeader(AUTHORIZATION_HEADER)) 
  {
    String authReq = header(AUTHORIZATION_HEADER);
    
    if (authReq.startsWith("Basic")) 
    {
      authReq = authReq.substring(6);
      authReq.trim();
      char toencodeLen = strlen(username) + strlen(password) + 1;
      char *toencode = new char[toencodeLen + 1];
      
      if (toencode == NULL) 
      {
        authReq = String();
        return false;
      }
      
      char *encoded = new char[base64_encode_expected_len(toencodeLen) + 1];
      
      if (encoded == NULL) 
      {
        authReq = String();
        delete[] toencode;
        return false;
      }
      
      sprintf(toencode, "%s:%s", username, password);
      
      if (base64_encode_chars(toencode, toencodeLen, encoded) > 0 && authReq.equals(encoded)) 
      {
        authReq = String();
        delete[] toencode;
        delete[] encoded;
        return true;
      }
      
      delete[] toencode;
      delete[] encoded;
    }
    
    authReq = String();
  }
  
  return false;
}

void EthernetWebServer::requestAuthentication() 
{
  sendHeader("WWW-Authenticate", "Basic realm=\"Login Required\"");
  send(401);
}

void EthernetWebServer::on(const String &uri, EthernetWebServer::THandlerFunction handler) 
{
  on(uri, HTTP_ANY, handler);
}

void EthernetWebServer::on(const String &uri, HTTPMethod method, EthernetWebServer::THandlerFunction fn) 
{
  on(uri, method, fn, _fileUploadHandler);
}

void EthernetWebServer::on(const String &uri, HTTPMethod method, EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn) 
{
  _addRequestHandler(new FunctionRequestHandler(fn, ufn, uri, method));
}

void EthernetWebServer::addHandler(RequestHandler* handler) 
{
  _addRequestHandler(handler);
}

void EthernetWebServer::_addRequestHandler(RequestHandler* handler) 
{
  if (!_lastHandler) 
  {
    _firstHandler = handler;
    _lastHandler = handler;
  }
  else 
  {
    _lastHandler->next(handler);
    _lastHandler = handler;
  }
}

//KH
#if USE_NEW_WEBSERVER_VERSION

void EthernetWebServer::handleClient() 
{
  if (_currentStatus == HC_NONE) 
  {
    EthernetClient client = _server.available();
    
    if (!client) 
    {
      //ET_LOGDEBUG(F("handleClient: No Client"));
      return;
    }

    ET_LOGDEBUG(F("handleClient: New Client"));

    _currentClient = client;
    _currentStatus = HC_WAIT_READ;
    _statusChange = millis();
  }

  bool keepCurrentClient = false;
  bool callYield = false;

  if (_currentClient.connected() || _currentClient.available()) 
  {
    switch (_currentStatus) 
    {
    case HC_NONE:
      // No-op to avoid C++ compiler warning
      break;
    case HC_WAIT_READ:
      // Wait for data from client to become available
      if (_currentClient.available()) 
      {
        if (_parseRequest(_currentClient)) 
        {
          _currentClient.setTimeout(HTTP_MAX_SEND_WAIT);
          _contentLength = CONTENT_LENGTH_NOT_SET;
          _handleRequest();

          if (_currentClient.connected()) 
          {
            _currentStatus = HC_WAIT_CLOSE;
            _statusChange = millis();
            keepCurrentClient = true;
          }
        }
      } 
      else 
      { // !_currentClient.available()
        if (millis() - _statusChange <= HTTP_MAX_DATA_WAIT) 
        {
          keepCurrentClient = true;
        }
        
        callYield = true;
      }
      
      break;
    case HC_WAIT_CLOSE:
      // Wait for client to close the connection
      if (millis() - _statusChange <= HTTP_MAX_CLOSE_WAIT) 
      {
        keepCurrentClient = true;
        callYield = true;
      }
    }
  }

  if (!keepCurrentClient) 
  {
    ET_LOGDEBUG(F("handleClient: Don't keepCurrentClient"));
    _currentClient = EthernetClient();
    _currentStatus = HC_NONE;
    // KH
    //_currentUpload.reset();
  }

  if (callYield) 
  {
    yield();
  }
  
  // KH, fix bug. Have to close the connection
  _currentClient.stop();
  //ET_LOGDEBUG(F("handleClient: Client disconnected"));
}
 
#else

#if 1

// KH, rewritten for Portenta H7 from v1.7.0

void EthernetWebServer::handleClient() 
{
  if (_currentStatus == HC_NONE)
  {
    EthernetClient client = _server.available();
    
    if (!client)
    {
      return;
    }

    ET_LOGDEBUG(F("handleClient: New Client"));

    _currentClient = client;
    _currentStatus = HC_WAIT_READ;
    _statusChange = millis();
  }

  if (!_currentClient.connected())
  {
    ET_LOGDEBUG(F("handleClient: Client not connected"));
    
    //_currentClient = EthernetClient();    
    _currentStatus = HC_NONE;
    
    goto stopClient;
    //return;
  }

  // Wait for data from client to become available
  if (_currentStatus == HC_WAIT_READ)
  {
    //ET_LOGDEBUG(F("handleClient: _currentStatus = HC_WAIT_READ"));
    
    if (!_currentClient.available())
    {
      //ET_LOGDEBUG(F("handleClient: Client not available"));
      
      if (millis() - _statusChange > HTTP_MAX_DATA_WAIT)
      {
        ET_LOGDEBUG(F("handleClient: HTTP_MAX_DATA_WAIT Timeout"));
        
        //_currentClient = EthernetClient();
        _currentStatus = HC_NONE;
        
        goto stopClient;
      }
      
      yield();
      return;
    }

    ET_LOGDEBUG(F("handleClient: Parsing Request"));
    
    if (!_parseRequest(_currentClient))
    {
      ET_LOGDEBUG(F("handleClient: Can't parse request"));
      
      //_currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      
      goto stopClient;
      //return;
    }
    
    _currentClient.setTimeout(HTTP_MAX_SEND_WAIT);
    _contentLength = CONTENT_LENGTH_NOT_SET;
    
    //ET_LOGDEBUG(F("handleClient _handleRequest"));
    _handleRequest();

    if (!_currentClient.connected())
    {
      ET_LOGDEBUG(F("handleClient: Connection closed"));
      
      //_currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      
      goto stopClient;
      //return;
    }
    else
    {
      _currentStatus = HC_WAIT_CLOSE;
      _statusChange = millis();
      return;
    }
  }

  if (_currentStatus == HC_WAIT_CLOSE)
  {
    if (millis() - _statusChange > HTTP_MAX_CLOSE_WAIT)
    {
      //_currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      
      ET_LOGDEBUG(F("handleClient: HTTP_MAX_CLOSE_WAIT Timeout"));
      
      yield();
    }
    else
    {
      yield();
      return;
    }
  }

stopClient:
  
  // KH, fix bug. Have to close the connection
  _currentClient.stop();
  ET_LOGDEBUG(F("handleClient: Client disconnected"));
}

#else

void EthernetWebServer::handleClient() 
{
  if (_currentStatus == HC_NONE)
  {
    EthernetClient client = _server.available();
    
    if (!client)
    {
      //LOGINFO(F("handleClient:No client"));
      return;
    }

    ET_LOGDEBUG(F("handleClient: New Client"));

    _currentClient = client;
    _currentStatus = HC_WAIT_READ;
    _statusChange = millis();
  }

  if (!_currentClient.connected())
  {
    ET_LOGDEBUG(F("handleClient: Client not connected"));
    
    _currentClient = EthernetClient();    
    _currentStatus = HC_NONE;
    return;
  }

  // Wait for data from client to become available
  if (_currentStatus == HC_WAIT_READ)
  {
    ET_LOGDEBUG(F("handleClient: _currentStatus = HC_WAIT_READ"));
    
    if (!_currentClient.available())
    {
      ET_LOGDEBUG(F("handleClient: Client not available"));
      
      if (millis() - _statusChange > HTTP_MAX_DATA_WAIT)
      {
        ET_LOGDEBUG(F("handleClient: HTTP_MAX_DATA_WAIT Timeout"));
        
        _currentClient = EthernetClient();
        _currentStatus = HC_NONE;
      }
      
      yield();
      return;
    }

    ET_LOGDEBUG(F("handleClient: Parsing Request"));
    
    if (!_parseRequest(_currentClient))
    {
      ET_LOGDEBUG(F("handleClient: Can't parse request"));
      
      _currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      return;
    }
    
    _currentClient.setTimeout(HTTP_MAX_SEND_WAIT);
    _contentLength = CONTENT_LENGTH_NOT_SET;
    
    //ET_LOGDEBUG(F("handleClient _handleRequest"));
    _handleRequest();

    if (!_currentClient.connected())
    {
      ET_LOGDEBUG(F("handleClient: Connection closed"));
      
      _currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      return;
    }
    else
    {
      _currentStatus = HC_WAIT_CLOSE;
      _statusChange = millis();
      return;
    }
  }

  if (_currentStatus == HC_WAIT_CLOSE)
  {
    if (millis() - _statusChange > HTTP_MAX_CLOSE_WAIT)
    {
      _currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      
      ET_LOGDEBUG(F("handleClient: HTTP_MAX_CLOSE_WAIT Timeout"));
      
      yield();
    }
    else
    {
      yield();
      return;
    }
  }
  
  // KH, fix bug. Have to close the connection
  _currentClient.stop();
  ET_LOGDEBUG(F("handleClient: Client disconnected"));
}

#endif

#endif

void EthernetWebServer::close() 
{
  // TODO: Write close method for Ethernet library and uncomment this
  //_server.close();
}

void EthernetWebServer::stop() 
{
  close();
}

void EthernetWebServer::sendHeader(const String& name, const String& value, bool first) 
{
  String headerLine = name;
  headerLine += ": ";
  headerLine += value;
  headerLine += "\r\n";

  if (first) 
  {
    _responseHeaders = headerLine + _responseHeaders;
  }
  else 
  {
    _responseHeaders += headerLine;
  }
}

void EthernetWebServer::setContentLength(size_t contentLength) 
{
  _contentLength = contentLength;
}

void EthernetWebServer::_prepareHeader(String& response, int code, const char* content_type, size_t contentLength) 
{
  response = "HTTP/1." + String(_currentVersion) + " ";
  response += String(code);
  response += " ";
  response += _responseCodeToString(code);
  response += "\r\n";

 using namespace mime;
 
  if (!content_type)
      content_type = mimeTable[html].mimeType;

  sendHeader("Content-Type", content_type, true);
  
  if (_contentLength == CONTENT_LENGTH_NOT_SET) 
  {
    sendHeader("Content-Length", String(contentLength));
  } 
  else if (_contentLength != CONTENT_LENGTH_UNKNOWN) 
  {
    sendHeader("Content-Length", String(_contentLength));
  } 
  else if (_contentLength == CONTENT_LENGTH_UNKNOWN && _currentVersion) 
  { 
    //HTTP/1.1 or above client
    //let's do chunked
    _chunked = true;
    sendHeader("Accept-Ranges", "none");
    sendHeader("Transfer-Encoding", "chunked");
  }
  
  ET_LOGDEBUG(F("_prepareHeader sendHeader Conn close"));
  
  sendHeader("Connection", "close");

  response += _responseHeaders;
  response += "\r\n";
  
  //MR & KH fix
  _responseHeaders = *(new String());
}

void EthernetWebServer::send(int code, const char* content_type, const String& content) 
{
  String header;
  
  // Can we asume the following?
  //if(code == 200 && content.length() == 0 && _contentLength == CONTENT_LENGTH_NOT_SET)
  //  _contentLength = CONTENT_LENGTH_UNKNOWN;

  ET_LOGDEBUG1(F("send1: len = "), content.length());
  ET_LOGDEBUG1(F("content = "), content);

  _prepareHeader(header, code, content_type, content.length());

  _currentClient.write((const uint8_t *)header.c_str(), header.length());
  
  if (content.length())
  {
    ET_LOGDEBUG1(F("send1: write header = "), header);
    //sendContent(content);
    sendContent(content, content.length());
  }
}

void EthernetWebServer::send(int code, char* content_type, const String& content, size_t contentLength)
{
  String header;

  ET_LOGDEBUG1(F("send2: len = "), contentLength);
  ET_LOGDEBUG1(F("content = "), content);

  char type[64];
  
  memccpy((void*)type, content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);

  ET_LOGDEBUG1(F("send2: hdrlen = "), header.length());
  ET_LOGDEBUG1(F("header = "), header);

  _currentClient.write((const uint8_t *) header.c_str(), header.length());
  
  if (contentLength)
  {
    sendContent(content, contentLength);
  }
}

void EthernetWebServer::send(int code, char* content_type, const String& content) 
{
  send(code, (const char*)content_type, content);
}

void EthernetWebServer::send(int code, const String& content_type, const String& content) 
{
  send(code, (const char*)content_type.c_str(), content);
}

void EthernetWebServer::sendContent(const String& content) 
{
  const char * footer = "\r\n";
  size_t len = content.length();
  
  if (_chunked) 
  {
    char * chunkSize = (char *) malloc(11);
    
    if (chunkSize) 
    {
      sprintf(chunkSize, "%x%s", len, footer);
      _currentClient.write(chunkSize, strlen(chunkSize));
      free(chunkSize);
    }
  }
  
  _currentClient.write(content.c_str(), len);
  
  if (_chunked) 
  {
    _currentClient.write(footer, 2);
  }
}

void EthernetWebServer::sendContent(const String& content, size_t size)
{
  const char * footer = "\r\n";
  
  if (_chunked) 
  {
    char * chunkSize = (char *) malloc(11);
    
    if (chunkSize) 
    {
      ET_LOGDEBUG(F("sendContent: _chunked"));
      
      sprintf(chunkSize, "%x%s", size, footer);
      _currentClient.write(chunkSize, strlen(chunkSize));
      free(chunkSize);
    }
  }
  
  ET_LOGDEBUG1(F("sendContent: Client.write content: "), content);
  
  _currentClient.write(content.c_str(), size);
  
  if (_chunked) 
  {
    _currentClient.write(footer, 2);
  }
}

// KH, Restore PROGMEM commands
void EthernetWebServer::send_P(int code, PGM_P content_type, PGM_P content) 
{
  size_t contentLength = 0;

  if (content != NULL) 
  {
    contentLength = strlen_P(content);
  }

  String header;
  char type[64];
  
  memccpy_P((void*)type, (PGM_VOID_P)content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);
  
  ET_LOGDEBUG1(F("send_P: len = "), contentLength);
  ET_LOGDEBUG1(F("content = "), content);
  ET_LOGDEBUG1(F("send_P: hdrlen = "), header.length());
  ET_LOGDEBUG1(F("header = "), header);
  
  _currentClient.write(header.c_str(), header.length());
  
  if (contentLength)
  {
    sendContent_P(content);
  }
}

void EthernetWebServer::send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength) 
{
  String header;
  char type[64];
  
  memccpy_P((void*)type, (PGM_VOID_P)content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);
  
  ET_LOGDEBUG1(F("send_P: len = "), contentLength);
  ET_LOGDEBUG1(F("content = "), content);
  ET_LOGDEBUG1(F("send_P: hdrlen = "), header.length());
  ET_LOGDEBUG1(F("header = "), header);

  _currentClient.write((const uint8_t *) header.c_str(), header.length());
  
  if (contentLength)
  {
    sendContent_P(content, contentLength);
  }
}


void EthernetWebServer::sendContent_P(PGM_P content) 
{
  sendContent_P(content, strlen_P(content));
}

void EthernetWebServer::sendContent_P(PGM_P content, size_t size) 
{
  const char * footer = "\r\n";
  
  if (_chunked) 
  {
    char * chunkSize = (char *) malloc(11);
    
    if (chunkSize) 
    {
      sprintf(chunkSize, "%x%s", size, footer);
      _currentClient.write(chunkSize, strlen(chunkSize));
      free(chunkSize);
    }
  }

  uint8_t* buffer = new uint8_t[SENDCONTENT_P_BUFFER_SZ];
  
  if (buffer)
  {
    uint16_t count = size / SENDCONTENT_P_BUFFER_SZ;
    uint16_t remainder = size % SENDCONTENT_P_BUFFER_SZ;
    uint16_t i = 0;

    for (i = 0; i < count; i++) 
    {
      /* code */
      memcpy_P(buffer, &content[i * SENDCONTENT_P_BUFFER_SZ], SENDCONTENT_P_BUFFER_SZ);
      _currentClient.write(buffer, SENDCONTENT_P_BUFFER_SZ);
    }
    
    memcpy_P(buffer, &content[i * SENDCONTENT_P_BUFFER_SZ], remainder);
    _currentClient.write(buffer, remainder);
    
    delete [] buffer;
  }
  else
  {
    ET_LOGERROR1(F("sendContent_P: Error, can't allocate buffer, Sz ="), SENDCONTENT_P_BUFFER_SZ);
    return;
  }
  
  if (_chunked) 
  {
    _currentClient.write(footer, 2);
  }
}
//////
#if (ESP32 || ESP8266)
#include "FS.h"
void EthernetWebServer::serveStatic(const char* uri, FS& fs, const char* path, const char* cache_header) {
    _addRequestHandler(new StaticFileRequestHandler(fs, path, uri, cache_header));
}

void EthernetWebServer::_streamFileCore(const size_t fileSize, const String &fileName, const String &contentType)
{
  using namespace mime;
  setContentLength(fileSize);
  if (fileName.endsWith(String(FPSTR(mimeTable[gz].endsWith))) &&
      contentType != String(FPSTR(mimeTable[gz].mimeType)) &&
      contentType != String(FPSTR(mimeTable[none].mimeType))) {
    sendHeader(F("Content-Encoding"), F("gzip"));
  }
  send(200, contentType, emptyString);
}
#endif

String EthernetWebServer::arg(String name) 
{
  for (int i = 0; i < _currentArgCount; ++i) 
  {
    if ( _currentArgs[i].key == name )
      return _currentArgs[i].value;
  }
  
  return String();
}

String EthernetWebServer::arg(int i) 
{
  if (i < _currentArgCount)
    return _currentArgs[i].value;
    
  return String();
}

String EthernetWebServer::argName(int i) 
{
  if (i < _currentArgCount)
    return _currentArgs[i].key;
    
  return String();
}

int EthernetWebServer::args() 
{
  return _currentArgCount;
}

bool EthernetWebServer::hasArg(String  name) 
{
  for (int i = 0; i < _currentArgCount; ++i) 
  {
    if (_currentArgs[i].key == name)
      return true;
  }
  
  return false;
}

String EthernetWebServer::header(String name) 
{
  for (int i = 0; i < _headerKeysCount; ++i) 
  {
    if (_currentHeaders[i].key == name)
      return _currentHeaders[i].value;
  }
  
  return String();
}

void EthernetWebServer::collectHeaders(const char* headerKeys[], const size_t headerKeysCount) 
{
  _headerKeysCount = headerKeysCount + 1;
  
  if (_currentHeaders)
    delete[]_currentHeaders;
    
  _currentHeaders = new RequestArgument[_headerKeysCount];
  _currentHeaders[0].key = AUTHORIZATION_HEADER;
  
  for (int i = 1; i < _headerKeysCount; i++) 
  {
    _currentHeaders[i].key = headerKeys[i - 1];
  }
}

String EthernetWebServer::header(int i) 
{
  if (i < _headerKeysCount)
    return _currentHeaders[i].value;
    
  return String();
}

String EthernetWebServer::headerName(int i) 
{
  if (i < _headerKeysCount)
    return _currentHeaders[i].key;
    
  return String();
}

int EthernetWebServer::headers() 
{
  return _headerKeysCount;
}

bool EthernetWebServer::hasHeader(String name) 
{
  for (int i = 0; i < _headerKeysCount; ++i) 
  {
    if ((_currentHeaders[i].key == name) &&  (_currentHeaders[i].value.length() > 0))
      return true;
  }
  
  return false;
}

String EthernetWebServer::hostHeader() 
{
  return _hostHeader;
}

void EthernetWebServer::onFileUpload(THandlerFunction fn) 
{
  _fileUploadHandler = fn;
}

void EthernetWebServer::onNotFound(THandlerFunction fn) 
{
  _notFoundHandler = fn;
}

void EthernetWebServer::_handleRequest()
{
  bool handled = false;
  
  if (!_currentHandler)
  {
    ET_LOGDEBUG(F("_handleRequest: request handler not found"));
  }
  else
  {
    ET_LOGDEBUG(F("_handleRequest handle"));
    
    handled = _currentHandler->handle(*this, _currentMethod, _currentUri);
    
    if (!handled)
    {
      ET_LOGDEBUG(F("_handleRequest: _handleRequest failed"));
    }
    else
    {
      ET_LOGDEBUG(F("_handleRequest OK"));
    }
  }

  if (!handled && _notFoundHandler) 
  {
    _notFoundHandler();
    handled = true;
  }
  
  if (!handled) 
  {
    using namespace mime;
    
    send(404, mimeTable[html].mimeType, String("Not found: ") + _currentUri);
    handled = true;
  }
  
  if (handled) 
  {
    _finalizeResponse();
  }
  
#if ETHERNET_USE_PORTENTA_H7
  ET_LOGDEBUG(F("_handleRequest: Clear _currentUri"));
  //_currentUri = String();
  ET_LOGDEBUG(F("_handleRequest: Done Clear _currentUri"));
#else  
  //MR & KH fix
  _currentUri = *(new String());
#endif  
}

void EthernetWebServer::_finalizeResponse() 
{
  if (_chunked) 
  {
    sendContent(String());
  }
}

String EthernetWebServer::_responseCodeToString(int code)
{
  switch (code) 
  {
    case 100: return F("Continue");
    case 101: return F("Switching Protocols");
    case 200: return F("OK");
    case 201: return F("Created");
    case 202: return F("Accepted");
    case 203: return F("Non-Authoritative Information");
    case 204: return F("No Content");
    case 205: return F("Reset Content");
    case 206: return F("Partial Content");
    case 300: return F("Multiple Choices");
    case 301: return F("Moved Permanently");
    case 302: return F("Found");
    case 303: return F("See Other");
    case 304: return F("Not Modified");
    case 305: return F("Use Proxy");
    case 307: return F("Temporary Redirect");
    case 400: return F("Bad Request");
    case 401: return F("Unauthorized");
    case 402: return F("Payment Required");
    case 403: return F("Forbidden");
    case 404: return F("Not Found");
    case 405: return F("Method Not Allowed");
    case 406: return F("Not Acceptable");
    case 407: return F("Proxy Authentication Required");
    case 408: return F("Request Time-out");
    case 409: return F("Conflict");
    case 410: return F("Gone");
    case 411: return F("Length Required");
    case 412: return F("Precondition Failed");
    case 413: return F("Request Entity Too Large");
    case 414: return F("Request-URI Too Large");
    case 415: return F("Unsupported Media Type");
    case 416: return F("Requested range not satisfiable");
    case 417: return F("Expectation Failed");
    case 500: return F("Internal Server Error");
    case 501: return F("Not Implemented");
    case 502: return F("Bad Gateway");
    case 503: return F("Service Unavailable");
    case 504: return F("Gateway Time-out");
    case 505: return F("HTTP Version not supported");
    default:  return "";
  }
}

