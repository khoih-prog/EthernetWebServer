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

  Version: 2.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
  ...
  2.0.0   K Hoang      16/01/2022 To coexist with ESP32 WebServer and ESP8266 ESP8266WebServer
  2.0.1   K Hoang      02/03/2022 Fix decoding error bug
  2.0.2   K Hoang      14/03/2022 Fix bug when using QNEthernet staticIP. Add staticIP option to NativeEthernet
  2.1.0   K Hoang      03/04/2022 Use Ethernet_Generic library as default. Support SPI2 for ESP32
  2.1.1   K Hoang      04/04/2022 Fix compiler error for Portenta_H7 using Portenta Ethernet
  2.1.2   K Hoang      08/04/2022 Add support to SPI1 for RP2040 using arduino-pico core
  2.1.3   K Hoang      27/04/2022 Change from `arduino.cc` to `arduino.tips` in examples
  2.2.0   K Hoang      05/05/2022 Add support to custom SPI for Teensy, Mbed RP2040, Portenta_H7, etc.
  2.2.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  2.2.2   K Hoang      06/09/2022 Slow SPI clock for old W5100 shield or SAMD Zero. Improve support for SAMD21
  2.2.3   K Hoang      17/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.2.4   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.3.0   K Hoang      15/11/2022 Add new features, such as CORS. Update code and examples to send big data
 *************************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_WEBSERVER_IMPL_H
#define ETHERNET_WEBSERVER_IMPL_H

#include <Arduino.h>
#include <libb64/cencode.h>
#include "EthernetWebServer.hpp"
#include "detail/RequestHandlersImpl.h"
#include "detail/Debug.h"
#include "detail/mimetable.h"

const char * ETHERNET_AUTHORIZATION_HEADER = "Authorization";

// New to use EWString

////////////////////////////////////////

EWString fromString(const String& str)
{
  return str.c_str();
}

////////////////////////////////////////

EWString fromString(const String&& str)
{
  return str.c_str();
}

////////////////////////////////////////

String fromEWString(const EWString& str)
{
  return str.c_str();
}

////////////////////////////////////////

String fromEWString(const EWString&& str)
{
  return str.c_str();
}

////////////////////////////////////////
////////////////////////////////////////

EthernetWebServer::EthernetWebServer(int port)
  : _corsEnabled(false)
  , _server(port)
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
  , _clientContentLength(0)
  , _chunked(false)
{
}

////////////////////////////////////////

EthernetWebServer::~EthernetWebServer()
{
  if (_currentHeaders)
    delete[]_currentHeaders;

  _headerKeysCount = 0;
  ethernetRequestHandler* handler = _firstHandler;

  while (handler)
  {
    ethernetRequestHandler* next = handler->next();
    delete handler;
    handler = next;
  }

  close();
}

////////////////////////////////////////

void EthernetWebServer::begin()
{
  _currentStatus = HC_NONE;
  _server.begin();

  if (!_headerKeysCount)
    collectHeaders(0, 0);
}

////////////////////////////////////////

bool EthernetWebServer::authenticate(const char * username, const char * password)
{
  if (hasHeader(ETHERNET_AUTHORIZATION_HEADER))
  {
    String authReq = header(ETHERNET_AUTHORIZATION_HEADER);

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

////////////////////////////////////////

void EthernetWebServer::requestAuthentication()
{
  sendHeader("WWW-Authenticate", "Basic realm=\"Login Required\"");
  send(401);
}

////////////////////////////////////////

void EthernetWebServer::on(const String &uri, EthernetWebServer::THandlerFunction handler)
{
  on(uri, HTTP_ANY, handler);
}

////////////////////////////////////////

void EthernetWebServer::on(const String &uri, HTTPMethod method, EthernetWebServer::THandlerFunction fn)
{
  on(uri, method, fn, _fileUploadHandler);
}

////////////////////////////////////////

void EthernetWebServer::on(const String &uri, HTTPMethod method, EthernetWebServer::THandlerFunction fn,
                           EthernetWebServer::THandlerFunction ufn)
{
  _addRequestHandler(new ethernetFunctionRequestHandler(fn, ufn, uri, method));
}

////////////////////////////////////////

void EthernetWebServer::addHandler(ethernetRequestHandler* handler)
{
  _addRequestHandler(handler);
}

////////////////////////////////////////

void EthernetWebServer::_addRequestHandler(ethernetRequestHandler* handler)
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

////////////////////////////////////////

//KH
#if USE_NEW_WEBSERVER_VERSION

////////////////////////////////////////

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

#if 0

            // Fix for issue with Chrome based browsers: https://github.com/espressif/arduino-esp32/issues/3652
            if (_currentClient.connected())
            {
              _currentStatus = HC_WAIT_CLOSE;
              _statusChange = millis();
              keepCurrentClient = true;
            }

#endif
          }
        }
        else
        {
          // !_currentClient.available()
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

////////////////////////////////////////

#else   // USE_NEW_WEBSERVER_VERSION

////////////////////////////////////////

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
    if (!_currentClient.available())
    {
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

////////////////////////////////////////

#endif   // USE_NEW_WEBSERVER_VERSION

////////////////////////////////////////

void EthernetWebServer::close()
{
  // TODO: Write close method for Ethernet library and uncomment this
  //_server.close();

  // KH, New v2.3.0
  _currentStatus = HC_NONE;

  if (!_headerKeysCount)
    collectHeaders(0, 0);

  //////
}

////////////////////////////////////////

void EthernetWebServer::stop()
{
  close();
}

////////////////////////////////////////

void EthernetWebServer::sendHeader(const String& name, const String& value, bool first)
{
  EWString headerLine = fromString(name);

  headerLine += ": ";
  headerLine += fromString(value);
  headerLine += RETURN_NEWLINE;

  if (first)
  {
    _responseHeaders = fromEWString(headerLine + fromString(_responseHeaders));
  }
  else
  {
    _responseHeaders = fromEWString(fromString(_responseHeaders) + headerLine);
  }
}

////////////////////////////////////////

void EthernetWebServer::setContentLength(size_t contentLength)
{
  _contentLength = contentLength;
}

////////////////////////////////////////

void EthernetWebServer::_prepareHeader(String& response, int code, const char* content_type, size_t contentLength)
{
  EWString aResponse = fromString(response);

  aResponse = "HTTP/1." + fromString(String(_currentVersion)) + " ";
  aResponse += fromString(String(code));
  aResponse += " ";
  aResponse += fromString(_responseCodeToString(code));
  aResponse += RETURN_NEWLINE;

  ET_LOGDEBUG1(F("_prepareHeader aResponse ="), fromEWString(aResponse));

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

  if (_corsEnabled)
  {
    sendHeader("Access-Control-Allow-Origin",  "*");
    sendHeader("Access-Control-Allow-Methods", "*");
    sendHeader("Access-Control-Allow-Headers", "*");
  }

  ET_LOGDEBUG(F("_prepareHeader sendHeader Conn close"));

  sendHeader("Connection", "close");

  aResponse += fromString(_responseHeaders);
  aResponse += RETURN_NEWLINE;

  response = fromEWString(aResponse);

  _responseHeaders = String("");
}

////////////////////////////////////////

#if ! ( ETHERNET_USE_AVR_MEGA || ETHERNET_USE_MEGA_AVR || ETHERNET_USE_DXCORE )
void EthernetWebServer::_prepareHeader(EWString& response, int code, const char* content_type, size_t contentLength)
{
  response = "HTTP/1." + fromString(String(_currentVersion)) + " ";
  response += fromString(String(code));
  response += " ";
  response += fromString(_responseCodeToString(code));
  response += RETURN_NEWLINE;

  //ET_LOGDEBUG1(F("_prepareHeader response ="), fromEWString(response));

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

  if (_corsEnabled)
  {
    sendHeader("Access-Control-Allow-Origin",  "*");
    sendHeader("Access-Control-Allow-Methods", "*");
    sendHeader("Access-Control-Allow-Headers", "*");
  }

  ET_LOGDEBUG(F("_prepareHeader sendHeader Conn close"));

  sendHeader("Connection", "close");

  response += fromString(_responseHeaders);
  response += RETURN_NEWLINE;

  _responseHeaders = String("");
}
#endif

////////////////////////////////////////

void EthernetWebServer::send(int code, const char* content_type, const String& content)
{
  EWString header;

  _prepareHeader(header, code, content_type, content.length());

  _currentClient.write((const uint8_t *)header.c_str(), header.length());

  if (content.length())
  {
    sendContent(content, content.length());
  }
}

////////////////////////////////////////

void EthernetWebServer::send(int code, char* content_type, const String& content, size_t contentLength)
{
  EWString header;

  char type[64];

  memccpy((void*)type, content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);

  _currentClient.write((const uint8_t *) header.c_str(), header.length());

  if (contentLength)
  {
    sendContent(content, contentLength);
  }
}

////////////////////////////////////////

void EthernetWebServer::send(int code, char* content_type, const String& content)
{
  send(code, (const char*)content_type, content);
}

////////////////////////////////////////

void EthernetWebServer::send(int code, const String& content_type, const String& content)
{
  send(code, (const char*)content_type.c_str(), content);
}

////////////////////////////////////////

// KH New

void EthernetWebServer::send(int code, const char* content_type, const char* content)
{
  send(code, content_type, content, content ? strlen(content) : 0);
}

////////////////////////////////////////

void EthernetWebServer::send(int code, const char* content_type, const char* content, size_t contentLength)
{
  String header;

  _prepareHeader(header, code, content_type, contentLength);

  _currentClient.write((const uint8_t *) header.c_str(), header.length());

  if (contentLength)
  {
    sendContent(content, contentLength);
  }
}

////////////////////////////////////////

void EthernetWebServer::sendContent(const char* content, size_t contentLength)
{
  const char * footer = RETURN_NEWLINE;

  if (_chunked)
  {
    char chunkSize[11];

    ET_LOGDEBUG1(F("sendContent_char: _chunked, _currentVersion ="), _currentVersion);

    sprintf(chunkSize, "%x%s", contentLength, footer);
    _currentClient.write(chunkSize, strlen(chunkSize));
  }

  _currentClient.write(content, contentLength);

  if (_chunked)
  {
    _currentClient.write(footer, 2);

    if (contentLength == 0)
    {
      _chunked = false;
    }
  }
}

////////////////////////////////////////

void EthernetWebServer::sendContent(const String& content)
{
  sendContent(content.c_str(), content.length());
}

////////////////////////////////////////

void EthernetWebServer::sendContent(const String& content, size_t contentLength)
{
  sendContent(content.c_str(), contentLength);
}

////////////////////////////////////////

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

////////////////////////////////////////

void EthernetWebServer::send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength)
{
  EWString header;

  char type[64];

  memccpy_P((void*)type, (PGM_VOID_P)content_type, 0, sizeof(type));
  _prepareHeader(header, code, (const char* )type, contentLength);

  ET_LOGDEBUG1(F("send_P: len = "), contentLength);
  ET_LOGDEBUG1(F("content = "), content);
  ET_LOGDEBUG1(F("send_P: hdrlen = "), header.length());
  ET_LOGDEBUG1(F("header = "), fromEWString(header));

  _currentClient.write((const uint8_t *) header.c_str(), header.length());

  if (contentLength)
  {
    sendContent_P(content, contentLength);
  }
}

////////////////////////////////////////

void EthernetWebServer::sendContent_P(PGM_P content)
{
  sendContent_P(content, strlen_P(content));
}

////////////////////////////////////////

void EthernetWebServer::sendContent_P(PGM_P content, size_t contentLength)
{
  const char * footer = RETURN_NEWLINE;

  if (_chunked)
  {
    char chunkSize[11];

    ET_LOGDEBUG1(F("sendContent_P: _chunked, _currentVersion ="), _currentVersion);

    sprintf(chunkSize, "%x%s", contentLength, footer);
    _currentClient.write(chunkSize, strlen(chunkSize));
  }

  uint8_t* _sendContentBuffer = new uint8_t[SENDCONTENT_P_BUFFER_SZ];

  if (_sendContentBuffer)
  {
    uint16_t count = contentLength / SENDCONTENT_P_BUFFER_SZ;
    uint16_t remainder = contentLength % SENDCONTENT_P_BUFFER_SZ;
    uint16_t i = 0;

    for (i = 0; i < count; i++)
    {
      /* code */
      memcpy_P(_sendContentBuffer, &content[i * SENDCONTENT_P_BUFFER_SZ], SENDCONTENT_P_BUFFER_SZ);
      _currentClient.write(_sendContentBuffer, SENDCONTENT_P_BUFFER_SZ);
    }

    memcpy_P(_sendContentBuffer, &content[i * SENDCONTENT_P_BUFFER_SZ], remainder);
    _currentClient.write(_sendContentBuffer, remainder);

    delete [] _sendContentBuffer;
  }
  else
  {
    ET_LOGERROR1(F("sendContent_P: Error, can't allocate _sendContentBuffer, Sz ="), SENDCONTENT_P_BUFFER_SZ);

    return;
  }

  if (_chunked)
  {
    _currentClient.write(footer, 2);

    _chunked = false;
  }
}

////////////////////////////////////////

#if (defined(ESP32) || defined(ESP8266))

#include "FS.h"

////////////////////////////////////////

void EthernetWebServer::serveStatic(const char* uri, FS& fs, const char* path, const char* cache_header)
{
  _addRequestHandler(new StaticFileRequestHandler(fs, path, uri, cache_header));
}

////////////////////////////////////////

void EthernetWebServer::_streamFileCore(const size_t fileSize, const String &fileName, const String &contentType,
                                        const int code)
{
  using namespace mime;

  setContentLength(fileSize);

  if (fileName.endsWith(String(FPSTR(mimeTable[gz].endsWith))) &&
      contentType != String(FPSTR(mimeTable[gz].mimeType)) &&
      contentType != String(FPSTR(mimeTable[none].mimeType)))
  {
    sendHeader(F("Content-Encoding"), F("gzip"));
  }

  send(code, contentType, emptyString);
}
#endif

////////////////////////////////////////

String EthernetWebServer::arg(const String& name)
{
  for (int i = 0; i < _currentArgCount; ++i)
  {
    if ( _currentArgs[i].key == name )
      return _currentArgs[i].value;
  }

  return String();
}

////////////////////////////////////////

String EthernetWebServer::arg(int i)
{
  if (i < _currentArgCount)
    return _currentArgs[i].value;

  return String();
}

////////////////////////////////////////

String EthernetWebServer::argName(int i)
{
  if (i < _currentArgCount)
    return _currentArgs[i].key;

  return String();
}

////////////////////////////////////////

int EthernetWebServer::args()
{
  return _currentArgCount;
}

////////////////////////////////////////

bool EthernetWebServer::hasArg(const String& name)
{
  for (int i = 0; i < _currentArgCount; ++i)
  {
    if (_currentArgs[i].key == name)
      return true;
  }

  return false;
}

////////////////////////////////////////

String EthernetWebServer::header(const String& name)
{
  for (int i = 0; i < _headerKeysCount; ++i)
  {
    if (_currentHeaders[i].key == name)
      return _currentHeaders[i].value;
  }

  return String();
}

////////////////////////////////////////

void EthernetWebServer::collectHeaders(const char* headerKeys[], const size_t headerKeysCount)
{
  _headerKeysCount = headerKeysCount + 1;

  if (_currentHeaders)
    delete[]_currentHeaders;

  _currentHeaders = new RequestArgument[_headerKeysCount];
  _currentHeaders[0].key = ETHERNET_AUTHORIZATION_HEADER;

  for (int i = 1; i < _headerKeysCount; i++)
  {
    _currentHeaders[i].key = headerKeys[i - 1];
  }
}

////////////////////////////////////////

String EthernetWebServer::header(int i)
{
  if (i < _headerKeysCount)
    return _currentHeaders[i].value;

  return String();
}

////////////////////////////////////////

String EthernetWebServer::headerName(int i)
{
  if (i < _headerKeysCount)
    return _currentHeaders[i].key;

  return String();
}

////////////////////////////////////////

int EthernetWebServer::headers()
{
  return _headerKeysCount;
}

////////////////////////////////////////

bool EthernetWebServer::hasHeader(const String& name)
{
  for (int i = 0; i < _headerKeysCount; ++i)
  {
    if ((_currentHeaders[i].key == name) &&  (_currentHeaders[i].value.length() > 0))
      return true;
  }

  return false;
}

////////////////////////////////////////

String EthernetWebServer::hostHeader()
{
  return _hostHeader;
}

////////////////////////////////////////

void EthernetWebServer::onFileUpload(THandlerFunction fn)
{
  _fileUploadHandler = fn;
}

////////////////////////////////////////

void EthernetWebServer::onNotFound(THandlerFunction fn)
{
  _notFoundHandler = fn;
}

////////////////////////////////////////

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
  _responseHeaders = String("");
#endif
}

////////////////////////////////////////

void EthernetWebServer::_finalizeResponse()
{
  if (_chunked)
  {
    sendContent(String());
  }
}

////////////////////////////////////////

String EthernetWebServer::_responseCodeToString(int code)
{
  switch (code)
  {
    case 100:
      return F("Continue");

    case 101:
      return F("Switching Protocols");

    case 200:
      return F("OK");

    case 201:
      return F("Created");

    case 202:
      return F("Accepted");

    case 203:
      return F("Non-Authoritative Information");

    case 204:
      return F("No Content");

    case 205:
      return F("Reset Content");

    case 206:
      return F("Partial Content");

    case 300:
      return F("Multiple Choices");

    case 301:
      return F("Moved Permanently");

    case 302:
      return F("Found");

    case 303:
      return F("See Other");

    case 304:
      return F("Not Modified");

    case 305:
      return F("Use Proxy");

    case 307:
      return F("Temporary Redirect");

    case 400:
      return F("Bad Request");

    case 401:
      return F("Unauthorized");

    case 402:
      return F("Payment Required");

    case 403:
      return F("Forbidden");

    case 404:
      return F("Not Found");

    case 405:
      return F("Method Not Allowed");

    case 406:
      return F("Not Acceptable");

    case 407:
      return F("Proxy Authentication Required");

    case 408:
      return F("Request Time-out");

    case 409:
      return F("Conflict");

    case 410:
      return F("Gone");

    case 411:
      return F("Length Required");

    case 412:
      return F("Precondition Failed");

    case 413:
      return F("Request Entity Too Large");

    case 414:
      return F("Request-URI Too Large");

    case 415:
      return F("Unsupported Media Type");

    case 416:
      return F("Requested range not satisfiable");

    case 417:
      return F("Expectation Failed");

    case 500:
      return F("Internal Server Error");

    case 501:
      return F("Not Implemented");

    case 502:
      return F("Bad Gateway");

    case 503:
      return F("Service Unavailable");

    case 504:
      return F("Gateway Time-out");

    case 505:
      return F("HTTP Version not supported");

    default:
      return "";
  }
}

////////////////////////////////////////

#endif  // ETHERNET_WEBSERVER_IMPL_H

