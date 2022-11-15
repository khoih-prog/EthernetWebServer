/****************************************************************************************************************************
  ESP_RequestHandlersImpl.h - Dead simple web-server.
  For Ethernet shields on ESP8266 and ESP32
  For EthernetWebServer library by Khoi Hoang

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

#ifndef ESP_REQUEST_HANDLER_IMPL_H
#define ESP_REQUEST_HANDLER_IMPL_H

#include "RequestHandler.h"
#include "esp_detail/mimetable.h"
#include "FS.h"
#include "WString.h"
#include <MD5Builder.h>
#include <base64.h>


class ethernetFunctionRequestHandler : public ethernetRequestHandler
{
  public:

    ethernetFunctionRequestHandler(EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn,
                                   const String &uri, const HTTPMethod& method)
      : _fn(fn)
      , _ufn(ufn)
      , _uri(uri)
      , _method(method)
    {
    }

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      if (_method != HTTP_ANY && _method != requestMethod)
        return false;

      if (requestUri == _uri)
        return true;

      if (_uri.endsWith("/*"))
      {
        String _uristart = _uri;
        _uristart.replace("/*", "");

        if (requestUri.startsWith(_uristart))
          return true;
      }

      return false;
    }

    bool canUpload(const String& requestUri) override
    {
      if (!_ufn || !canHandle(HTTP_POST, requestUri))
        return false;

      return true;
    }

    bool handle(EthernetWebServer& server, const HTTPMethod& requestMethod, const String& requestUri) override
    {
      ETW_UNUSED(server);

      if (!canHandle(requestMethod, requestUri))
        return false;

      _fn();
      return true;
    }

    void upload(EthernetWebServer& server, const String& requestUri, const ethernetHTTPUpload& upload) override
    {
      ETW_UNUSED(server);
      ETW_UNUSED(upload);

      if (canUpload(requestUri))
        _ufn();
    }

  protected:
    EthernetWebServer::THandlerFunction _fn;
    EthernetWebServer::THandlerFunction _ufn;
    String _uri;
    HTTPMethod _method;
};

class StaticRequestHandler : public ethernetRequestHandler
{
    using WebServerType = EthernetWebServer;

  public:
    StaticRequestHandler(FS& fs, const char* path, const char* uri, const char* cache_header)
      : _fs(fs)
      , _uri(uri)
      , _path(path)
      , _cache_header(cache_header)
    {
      //DEBUGV("StaticRequestHandler: path=%s uri=%s, cache_header=%s\r\n", path, uri, cache_header == __null ? "" : cache_header);
      _isFile = fs.exists(path);
      _baseUriLength = _uri.length();
    }

    bool validMethod(HTTPMethod requestMethod)
    {
      return (requestMethod == HTTP_GET) || (requestMethod == HTTP_HEAD);
    }

    /* Deprecated version. Please use mime::getContentType instead */
    static String getContentType(const String& path) __attribute__((deprecated))
    {
      return mime_esp::getContentType(path);
    }

  protected:
    FS _fs;
    bool _isFile;
    String _uri;
    String _path;
    String _cache_header;
    size_t _baseUriLength;
};


class StaticFileRequestHandler
  :
  public StaticRequestHandler
{
    using SRH = StaticRequestHandler;
    using WebServerType = EthernetWebServer;

  public:
    StaticFileRequestHandler(FS& fs, const char* path, const char* uri, const char* cache_header)
      :
      StaticRequestHandler{fs, path, uri, cache_header}
    {
      File f = SRH::_fs.open(path, "r");
      MD5Builder calcMD5;
      calcMD5.begin();
      calcMD5.addStream(f, f.size());
      calcMD5.calculate();
      calcMD5.getBytes(_ETag_md5);
      f.close();
    }

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      return SRH::validMethod(requestMethod) && requestUri == SRH::_uri;
    }

    bool handle(EthernetWebServer& server, const HTTPMethod& requestMethod, const String& requestUri)
    {
      if (!canHandle(requestMethod, requestUri))
        return false;


      const String etag = "\"" + base64::encode(_ETag_md5, 16) + "\"";

      if (server.header("If-None-Match") == etag)
      {
        server.send(304);
        return true;
      }

      File f = SRH::_fs.open(SRH::_path, "r");

      if (!f)
        return false;

      if (!_isFile)
      {
        f.close();
        return false;
      }

      if (SRH::_cache_header.length() != 0)
        server.sendHeader("Cache-Control", SRH::_cache_header);

      server.sendHeader("ETag", etag);

      server.streamFile(f, mime_esp::getContentType(SRH::_path), requestMethod);
      return true;
    }

  protected:
    uint8_t _ETag_md5[16];
};

#endif  // ESP_REQUEST_HANDLER_IMPL_H
