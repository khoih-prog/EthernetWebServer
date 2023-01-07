/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For Ethernet shields on ESP8266 and ESP32
  For EthernetWebServer library by Khoi Hoang

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

#ifndef __ESP_MIMETABLE_H__
#define __ESP_MIMETABLE_H__

#if (defined(ESP32) || defined(ESP8266))

#include "WString.h"

namespace mime_esp
{
enum type
{
  html,
  htm,
  txt,
#ifndef MIMETYPE_MINIMAL    // allow to compile with only the strict minimum of mime-types
  css,
  js,
  json,
  png,
  gif,
  jpg,
  jpeg,
  ico,
  svg,
  ttf,
  otf,
  woff,
  woff2,
  eot,
  sfnt,
  xml,
  pdf,
  zip,
  appcache,
#endif // MIMETYPE_MINIMAL
  gz,
  none,
  maxType
};

struct Entry
{
  const char * endsWith;
  const char * mimeType;
};

extern const Entry mimeTable[maxType];

String getContentType(const String& path);
}

#endif    // #if (defined(ESP32) || defined(ESP8266))
#endif    // #ifndef __ESP_MIMETABLE_H__
