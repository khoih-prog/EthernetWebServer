/****************************************************************************************************************************
  RequestHandler.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov

  Version: 1.8.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
  ...
  1.6.0   K Hoang      04/09/2021 Add support to QNEthernet Library for Teensy 4.1
  1.7.0   K Hoang      09/09/2021 Add support to Portenta H7 Ethernet
  1.7.1   K Hoang      04/10/2021 Change option for PIO `lib_compat_mode` from default `soft` to `strict`. Update Packages Patches
  1.8.0   K Hoang      19/12/2021 Reduce usage of Arduino String with std::string
  1.8.1   K Hoang      24/12/2021 Fix bug
  1.8.2   K Hoang      27/12/2021 Fix wrong http status header bug
  1.8.3   K Hoang      28/12/2021 Fix authenticate issue caused by libb64
 *************************************************************************************************************************************/

#pragma once

#ifndef ETW_UNUSED
  #define ETW_UNUSED(x) (void)(x)
#endif


class RequestHandler
{
  public:

    virtual ~RequestHandler() { }

    virtual bool canHandle(const HTTPMethod& method, const String& uri)
    {
      ETW_UNUSED(method);
      ETW_UNUSED(uri);
      
      return false;
    }

    virtual bool canUpload(const String& uri)
    {
      ETW_UNUSED(uri);
      
      return false;
    }

    virtual bool handle(EthernetWebServer& server, const HTTPMethod& requestMethod, const String& requestUri)
    {
      ETW_UNUSED(server);
      ETW_UNUSED(requestMethod);
      ETW_UNUSED(requestUri);
      
      return false;
    }

    virtual void upload(EthernetWebServer& server, const String& requestUri, const HTTPUpload& upload) 
    {
      ETW_UNUSED(server);
      ETW_UNUSED(requestUri);
      ETW_UNUSED(upload);
    }

    RequestHandler* next()
    {
      return _next;
    }

    void next(RequestHandler* r)
    {
      _next = r;
    }

  private:

    RequestHandler* _next = nullptr;
};

