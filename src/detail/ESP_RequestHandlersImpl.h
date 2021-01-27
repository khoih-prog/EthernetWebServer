/****************************************************************************************************************************
   ESP_RequestHandlersImpl.h - Dead simple web-server.
   For Ethernet shields on ESP8266 and ESP32
   For EthernetWebServer library by Khoi Hoang
 
   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license
   Version: 1.0.0

   Original author:
   @file       RequestHandlersImpl.h
   @author     Khoi Hoang

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   S Azari      25/01/2021 Initial coding, inheriting EthernetWebServer class and porting ESP8266 code
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

