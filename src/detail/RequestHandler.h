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

  Version: 2.4.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
  ...
  2.2.0   K Hoang      05/05/2022 Add support to custom SPI for Teensy, Mbed RP2040, Portenta_H7, etc.
  2.2.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  2.2.2   K Hoang      06/09/2022 Slow SPI clock for old W5100 shield or SAMD Zero. Improve support for SAMD21
  2.2.3   K Hoang      17/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.2.4   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.3.0   K Hoang      15/11/2022 Add new features, such as CORS. Update code and examples to send big data
  2.4.0   K Hoang      22/12/2022 Fix compile errors for new ESP32 core v2.0.6
  2.4.1   K Hoang      06/01/2023 Add support to `WIZNet W6100` using IPv4
 *************************************************************************************************************************************/

#pragma once

#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#ifndef ETW_UNUSED
  #define ETW_UNUSED(x) (void)(x)
#endif

class ethernetRequestHandler
{
  public:

    virtual ~ethernetRequestHandler() { }

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

    virtual void upload(EthernetWebServer& server, const String& requestUri, const ethernetHTTPUpload& upload)
    {
      ETW_UNUSED(server);
      ETW_UNUSED(requestUri);
      ETW_UNUSED(upload);
    }

    ethernetRequestHandler* next()
    {
      return _next;
    }

    void next(ethernetRequestHandler* r)
    {
      _next = r;
    }

  private:

    ethernetRequestHandler* _next = nullptr;
};

#endif  // REQUEST_HANDLER_H
