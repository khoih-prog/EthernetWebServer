/****************************************************************************************************************************
   ESP_RequestHandlersImpl.h - Dead simple web-server.
   For Ethernet shields on ESP8266 and ESP32
   For EthernetWebServer library by Khoi Hoang
 
   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license
   
   Version: 1.5.0

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
                                    Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, etc. 
                                    More Custom Ethernet libraries supported such as Ethernet2, Ethernet3, EthernetLarge
    1.0.6   K Hoang      27/04/2020 Add W5x00 support to ESP32/ESP8266 boards
    1.0.7   K Hoang      30/04/2020 Add ENC28J60 support to ESP32/ESP8266 boards  
    1.0.8   K Hoang      12/05/2020 Fix W5x00 support for ESP8266 boards.
    1.0.9   K Hoang      15/05/2020 Add EthernetWrapper.h for easier W5x00 support as well as more Ethernet libs in the future.
    1.0.10  K Hoang      21/07/2020 Fix bug not closing client and releasing socket.
    1.0.11  K Hoang      25/07/2020 Add support to Seeeduino SAMD21/SAMD51 boards. Restructure examples.
    1.0.12  K Hoang      15/09/2020 Add support to new EthernetENC library for ENC28J60. Add debug feature.
    1.0.13  K Hoang      24/09/2020 Restore support to PROGMEM-related commands, such as sendContent_P() and send_P()
    1.1.0   K Hoang      17/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
    1.2.0   K Hoang      04/12/2020 Add support to NativeEthernet Library for Teensy 4.1
    1.2.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
    1.3.0   K Hoang      27/01/2021 Add WebServer feature to serve from LittleFS/SPIFFS for ESP32/ESP8266 with examples
    1.3.1   K Hoang      29/04/2021 Add SimpleWebServer_NativeEthernet and delete AdvancedWebServer_NativeEthernet example
    1.4.0   K Hoang      13/05/2021 Add support to RP2040-based boards using Arduino mbed_rp2040 core
    1.5.0   K Hoang      15/05/2021 Add support to RP2040-based boards using Arduino-pico rp2040 core
 *****************************************************************************************************************************/

#pragma once

#include "RequestHandler.h"
#include "esp_detail/mimetable.h"
#include "FS.h"
#include "WString.h"
#include <MD5Builder.h>
#include <base64.h>

class FunctionRequestHandler : public RequestHandler
{
  public:

    FunctionRequestHandler(EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn, const String &uri, HTTPMethod method)
      : _fn(fn)
      , _ufn(ufn)
      , _uri(uri)
      , _method(method)
    {
    }

    bool canHandle(HTTPMethod requestMethod, String requestUri) override
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

    bool canUpload(String requestUri) override
    {
      if (!_ufn || !canHandle(HTTP_POST, requestUri))
        return false;

      return true;
    }

    bool handle(EthernetWebServer& server, HTTPMethod requestMethod, String requestUri) override
    {
      ETW_UNUSED(server);
      
      if (!canHandle(requestMethod, requestUri))
        return false;

      _fn();
      return true;
    }

    void upload(EthernetWebServer& server, String requestUri, HTTPUpload& upload) override
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

class StaticRequestHandler : public RequestHandler {
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

    bool validMethod(HTTPMethod requestMethod){
        return (requestMethod == HTTP_GET) || (requestMethod == HTTP_HEAD);
    }

    /* Deprecated version. Please use mime::getContentType instead */
    static String getContentType(const String& path) __attribute__((deprecated)) {
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
public StaticRequestHandler {

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

    bool canHandle(HTTPMethod requestMethod, const String requestUri) override  {
        return SRH::validMethod(requestMethod) && requestUri == SRH::_uri;
    }

    bool handle(EthernetWebServer& server, HTTPMethod requestMethod, const String requestUri) {

        if (!canHandle(requestMethod, requestUri))
            return false;

        
        const String etag = "\"" + base64::encode(_ETag_md5, 16) + "\"";

        if(server.header("If-None-Match") == etag){
            server.send(304);
            return true;
        }

        File f = SRH::_fs.open(SRH::_path, "r");

        if (!f)
            return false;

        if (!_isFile) {
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

