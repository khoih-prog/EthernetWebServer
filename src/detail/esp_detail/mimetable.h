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
