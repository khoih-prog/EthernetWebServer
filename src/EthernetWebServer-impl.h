/****************************************************************************************************************************
   EthernetWebServer-impl.h - Dead simple web-server.
   For Ethernet shields

   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license
   Version: 1.0.5

   Original author:
   @file       Esp8266WebServer.h
   @author     Ivan Grokhotkov

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
    1.0.1   K Hoang      20/02/2020 Add support to lambda functions
    1.0.2   K Hoang      20/02/2020 Add support to UIPEthernet library for ENC28J60
    1.0.3   K Hoang      23/02/2020 Add support to SAM DUE / SAMD21 boards
    1.0.4   K Hoang      16/04/2020 Add support to SAMD51 boards
    1.0.5   K Hoang      24/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, 
                                    Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, etc.
                                    More Custom Ethernet libraries supported such as Ethernet2, Ethernet3, EthernetLarge
 *****************************************************************************************************************************/

#ifndef EthernetWebServer_impl_h
#define EthernetWebServer_impl_h

#include <Arduino.h>
#include <libb64/cencode.h>
#include "EthernetWebServer.h"
#include "detail/RequestHandlersImpl.h"
#include "detail/Debug.h"

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

EthernetWebServer::~EthernetWebServer() {
  if (_currentHeaders)
    delete[]_currentHeaders;
  _headerKeysCount = 0;
  RequestHandler* handler = _firstHandler;
  while (handler) {
    RequestHandler* next = handler->next();
    delete handler;
    handler = next;
  }
  close();
}

void EthernetWebServer::begin() {
  _currentStatus = HC_NONE;
  _server.begin();
  if (!_headerKeysCount)
    collectHeaders(0, 0);
}

bool EthernetWebServer::authenticate(const char * username, const char * password) {
  if (hasHeader(AUTHORIZATION_HEADER)) {
    String authReq = header(AUTHORIZATION_HEADER);
    if (authReq.startsWith("Basic")) {
      authReq = authReq.substring(6);
      authReq.trim();
      char toencodeLen = strlen(username) + strlen(password) + 1;
      char *toencode = new char[toencodeLen + 1];
      if (toencode == NULL) {
        authReq = String();
        return false;
      }
      char *encoded = new char[base64_encode_expected_len(toencodeLen) + 1];
      if (encoded == NULL) {
        authReq = String();
        delete[] toencode;
        return false;
      }
      sprintf(toencode, "%s:%s", username, password);
      if (base64_encode_chars(toencode, toencodeLen, encoded) > 0 && authReq.equals(encoded)) {
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

void EthernetWebServer::requestAuthentication() {
  sendHeader("WWW-Authenticate", "Basic realm=\"Login Required\"");
  send(401);
}

void EthernetWebServer::on(const String &uri, EthernetWebServer::THandlerFunction handler) {
  on(uri, HTTP_ANY, handler);
}

void EthernetWebServer::on(const String &uri, HTTPMethod method, EthernetWebServer::THandlerFunction fn) {
  on(uri, method, fn, _fileUploadHandler);
}

void EthernetWebServer::on(const String &uri, HTTPMethod method, EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn) {
  _addRequestHandler(new FunctionRequestHandler(fn, ufn, uri, method));
}

void EthernetWebServer::addHandler(RequestHandler* handler) {
  _addRequestHandler(handler);
}

void EthernetWebServer::_addRequestHandler(RequestHandler* handler) {
  if (!_lastHandler) {
    _firstHandler = handler;
    _lastHandler = handler;
  }
  else {
    _lastHandler->next(handler);
    _lastHandler = handler;
  }
}

void EthernetWebServer::handleClient() {
  if (_currentStatus == HC_NONE) 
  {
    EthernetClient client = _server.available();
    if (!client) 
    {
      //LOGINFO(F("handleClient:No client"));
      return;
    }

    LOGINFO(F("handleClient:New client"));

    _currentClient = client;
    _currentStatus = HC_WAIT_READ;
    _statusChange = millis();
  }

  if (!_currentClient.connected()) 
  {
    _currentClient = EthernetClient();
    LOGINFO(F("handleClient:Client connected"));
    _currentStatus = HC_NONE;
    return;
  }

  // Wait for data from client to become available
  if (_currentStatus == HC_WAIT_READ) 
  {
    LOGINFO(F("handleClient:_currentStatus = HC_WAIT_READ"));
    if (!_currentClient.available()) 
    {
      LOGINFO(F("handleClient:Client not available"));
      if (millis() - _statusChange > HTTP_MAX_DATA_WAIT) 
      {
        LOGINFO(F("HTTP_MAX_DATA_WAIT Timeout"));
        _currentClient = EthernetClient();
        _currentStatus = HC_NONE;
      }
      yield();
      return;
    }

    if (!_parseRequest(_currentClient)) 
    {
      LOGINFO(F("Unable to parse request"));
      _currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      return;
    }
    _currentClient.setTimeout(HTTP_MAX_SEND_WAIT);
    _contentLength = CONTENT_LENGTH_NOT_SET;
    _handleRequest();

    if (!_currentClient.connected()) 
    {
      LOGINFO(F("Connection closed"));
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
    //if (millis() - _statusChange > HTTP_MAX_CLOSE_WAIT * 10) 
    {
      _currentClient = EthernetClient();
      _currentStatus = HC_NONE;
      LOGINFO(F("HTTP_MAX_CLOSE_WAIT Timeout"));
      yield();
    } 
    else 
    {
      yield();
      return;
    }
  }
}

void EthernetWebServer::close() {
  // TODO: Write close method for Ethernet library and uncomment this
  //_server.close();
}

void EthernetWebServer::stop() {
  close();
}

void EthernetWebServer::sendHeader(const String& name, const String& value, bool first) {
  String headerLine = name;
  headerLine += ": ";
  headerLine += value;
  headerLine += "\r\n";

  if (first) {
    _responseHeaders = headerLine + _responseHeaders;
  }
  else {
    _responseHeaders += headerLine;
  }
}

void EthernetWebServer::setContentLength(size_t contentLength) {
  _contentLength = contentLength;
}

void EthernetWebServer::_prepareHeader(String& response, int code, const char* content_type, size_t contentLength) {
  response = "HTTP/1." + String(_currentVersion) + " ";
  response += String(code);
  response += " ";
  response += _responseCodeToString(code);
  response += "\r\n";

  if (!content_type)
    content_type = "text/html";

  sendHeader("Content-Type", content_type, true);
  if (_contentLength == CONTENT_LENGTH_NOT_SET) {
    sendHeader("Content-Length", String(contentLength));
  } else if (_contentLength != CONTENT_LENGTH_UNKNOWN) {
    sendHeader("Content-Length", String(_contentLength));
  } else if (_contentLength == CONTENT_LENGTH_UNKNOWN && _currentVersion) { //HTTP/1.1 or above client
    //let's do chunked
    _chunked = true;
    sendHeader("Accept-Ranges", "none");
    sendHeader("Transfer-Encoding", "chunked");
  }
  sendHeader("Connection", "close");

  response += _responseHeaders;
  response += "\r\n";
  _responseHeaders = String();
}

void EthernetWebServer::send(int code, const char* content_type, const String& content) {
  String header;
  // Can we asume the following?
  //if(code == 200 && content.length() == 0 && _contentLength == CONTENT_LENGTH_NOT_SET)
  //  _contentLength = CONTENT_LENGTH_UNKNOWN;

  LOGDEBUG1(F("send1: len = "), content.length());
  LOGDEBUG1(F("content = "), content);

  _prepareHeader(header, code, content_type, content.length());

  _currentClient.write((const uint8_t *)header.c_str(), header.length());
  if (content.length())
  {
    //sendContent(content);
    sendContent(content, content.length());
  }
}

void EthernetWebServer::send(int code, char* content_type, const String& content, size_t contentLength)
{
  String header;

  LOGDEBUG1(F("send2: len = "), contentLength);
  LOGDEBUG1(F("content = "), content);

  char type[64];
  memccpy((void*)type, content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);

  LOGDEBUG1(F("send2: hdrlen = "), header.length());
  LOGDEBUG1(F("header = "), header);

  _currentClient.write((const uint8_t *) header.c_str(), header.length());
  if (contentLength)
  {
    sendContent(content, contentLength);
  }
}

void EthernetWebServer::send(int code, char* content_type, const String& content) {
  send(code, (const char*)content_type, content);
}

void EthernetWebServer::send(int code, const String& content_type, const String& content) {
  send(code, (const char*)content_type.c_str(), content);
}

#if !( defined(CORE_TEENSY) || (ETHERNET_USE_SAMD) || ETHERNET_USE_SAM_DUE || ETHERNET_USE_NRF528XX )
void EthernetWebServer::send_P(int code, PGM_P content_type, PGM_P content) {
  size_t contentLength = 0;

  if (content != NULL) {
    contentLength = strlen_P(content);
  }

  String header;
  char type[64];
  memccpy_P((void*)type, (PGM_VOID_P)content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);
  _currentClient.write(header.c_str(), header.length());
  sendContent_P(content);
}

void EthernetWebServer::send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength) {
  String header;
  char type[64];
  memccpy_P((void*)type, (PGM_VOID_P)content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);
  sendContent(header);
  sendContent_P(content, contentLength);
}

void EthernetWebServer::sendContent_P(PGM_P content) {
  sendContent_P(content, strlen_P(content));
}

void EthernetWebServer::sendContent_P(PGM_P content, size_t size) {
  const char * footer = "\r\n";
  if (_chunked) {
    char * chunkSize = (char *)malloc(11);
    if (chunkSize) {
      sprintf(chunkSize, "%x%s", size, footer);
      _currentClient.write(chunkSize, strlen(chunkSize));
      free(chunkSize);
    }
  }
  _currentClient.write(content, size);
  if (_chunked) {
    _currentClient.write(footer, 2);
  }
}
#endif

void EthernetWebServer::sendContent(const String& content) {
  const char * footer = "\r\n";
  size_t len = content.length();
  if (_chunked) {
    char * chunkSize = (char *)malloc(11);
    if (chunkSize) {
      sprintf(chunkSize, "%x%s", len, footer);
      _currentClient.write(chunkSize, strlen(chunkSize));
      free(chunkSize);
    }
  }
  _currentClient.write(content.c_str(), len);
  if (_chunked) {
    _currentClient.write(footer, 2);
  }
}

void EthernetWebServer::sendContent(const String& content, size_t size)
{
  const char * footer = "\r\n";
  if (_chunked) {
    char * chunkSize = (char *)malloc(11);
    if (chunkSize) {
      sprintf(chunkSize, "%x%s", size, footer);
      _currentClient.write(chunkSize, strlen(chunkSize));
      free(chunkSize);
    }
  }
  _currentClient.write(content.c_str(), size);
  if (_chunked) {
    _currentClient.write(footer, 2);
  }
}

String EthernetWebServer::arg(String name) {
  for (int i = 0; i < _currentArgCount; ++i) {
    if ( _currentArgs[i].key == name )
      return _currentArgs[i].value;
  }
  return String();
}

String EthernetWebServer::arg(int i) {
  if (i < _currentArgCount)
    return _currentArgs[i].value;
  return String();
}

String EthernetWebServer::argName(int i) {
  if (i < _currentArgCount)
    return _currentArgs[i].key;
  return String();
}

int EthernetWebServer::args() {
  return _currentArgCount;
}

bool EthernetWebServer::hasArg(String  name) {
  for (int i = 0; i < _currentArgCount; ++i) {
    if (_currentArgs[i].key == name)
      return true;
  }
  return false;
}


String EthernetWebServer::header(String name) {
  for (int i = 0; i < _headerKeysCount; ++i) {
    if (_currentHeaders[i].key == name)
      return _currentHeaders[i].value;
  }
  return String();
}

void EthernetWebServer::collectHeaders(const char* headerKeys[], const size_t headerKeysCount) {
  _headerKeysCount = headerKeysCount + 1;
  if (_currentHeaders)
    delete[]_currentHeaders;
  _currentHeaders = new RequestArgument[_headerKeysCount];
  _currentHeaders[0].key = AUTHORIZATION_HEADER;
  for (int i = 1; i < _headerKeysCount; i++) {
    _currentHeaders[i].key = headerKeys[i - 1];
  }
}

String EthernetWebServer::header(int i) {
  if (i < _headerKeysCount)
    return _currentHeaders[i].value;
  return String();
}

String EthernetWebServer::headerName(int i) {
  if (i < _headerKeysCount)
    return _currentHeaders[i].key;
  return String();
}

int EthernetWebServer::headers() {
  return _headerKeysCount;
}

bool EthernetWebServer::hasHeader(String name) {
  for (int i = 0; i < _headerKeysCount; ++i) {
    if ((_currentHeaders[i].key == name) &&  (_currentHeaders[i].value.length() > 0))
      return true;
  }
  return false;
}

String EthernetWebServer::hostHeader() {
  return _hostHeader;
}

void EthernetWebServer::onFileUpload(THandlerFunction fn) {
  _fileUploadHandler = fn;
}

void EthernetWebServer::onNotFound(THandlerFunction fn) {
  _notFoundHandler = fn;
}

void EthernetWebServer::_handleRequest() 
{
  bool handled = false;
  if (!_currentHandler) 
  {
    LOGWARN(F("request handler not found"));
  }
  else 
  {
    handled = _currentHandler->handle(*this, _currentMethod, _currentUri);
    if (!handled) 
    {
      LOGWARN(F("_handleRequest failed"));
    }
  }

  if (!handled) 
  {
    if (_notFoundHandler) 
    {
      _notFoundHandler();
    }
    else 
    {
      send(404, "text/plain", String("Not found: ") + _currentUri);
    }
  }

  _currentUri = String();
}

String EthernetWebServer::_responseCodeToString(int code) 
{
  switch (code) {
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

#endif //EthernetWebServer_impl_h
