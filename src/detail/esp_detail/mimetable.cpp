/****************************************************************************************************************************
  mimetable.cpp - Dead simple web-server.
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

#if (ESP32 || ESP8266)

#include "mimetable.h"
#include "pgmspace.h"
#include "WString.h"

namespace mime_esp
{
static const char kHtmlSuffix[]     PROGMEM = ".html";
static const char kHtmSuffix[]      PROGMEM = ".htm";
static const char kTxtSuffix[]      PROGMEM = ".txt";

#ifndef MIMETYPE_MINIMAL
  static const char kCssSuffix[]      PROGMEM = ".css";
  static const char kJsSuffix[]       PROGMEM = ".js";
  static const char kJsonSuffix[]     PROGMEM = ".json";
  static const char kPngSuffix[]      PROGMEM = ".png";
  static const char kGifSuffix[]      PROGMEM = ".gif";
  static const char kJpgSuffix[]      PROGMEM = ".jpg";
  static const char kJpegSuffix[]     PROGMEM = ".jpeg";
  static const char kIcoSuffix[]      PROGMEM = ".ico";
  static const char kSvgSuffix[]      PROGMEM = ".svg";
  static const char kTtfSuffix[]      PROGMEM =  ".ttf";
  static const char kOtfSuffix[]      PROGMEM = ".otf";
  static const char kWoffSuffix[]     PROGMEM = ".woff";
  static const char kWoff2Suffix[]    PROGMEM = ".woff2";
  static const char kEotSuffix[]      PROGMEM = ".eot";
  static const char kSfntSuffix[]     PROGMEM = ".sfnt";
  static const char kXmlSuffix[]      PROGMEM = ".xml";
  static const char kPdfSuffix[]      PROGMEM = ".pdf";
  static const char kZipSuffix[]      PROGMEM = ".zip";
  static const char kAppcacheSuffix[] PROGMEM = ".appcache";
#endif // MIMETYPE_MINIMAL

static const char kGzSuffix[]       PROGMEM = ".gz";
static const char kDefaultSuffix[]  PROGMEM = "";

static const char kHtml[]           PROGMEM = "text/html";
static const char kTxt[]            PROGMEM = "text/plain";

#ifndef MIMETYPE_MINIMAL
  static const char kCss[]            PROGMEM = "text/css";
  static const char kJs[]             PROGMEM = "application/javascript";
  static const char kJson[]           PROGMEM = "application/json";
  static const char kPng[]            PROGMEM = "image/png";
  static const char kGif[]            PROGMEM = "image/gif";
  static const char kJpg[]            PROGMEM = "image/jpeg";
  static const char kJpeg[]           PROGMEM = "image/jpeg";
  static const char kIco[]            PROGMEM = "image/x-icon";
  static const char kSvg[]            PROGMEM = "image/svg+xml";
  static const char kTtf[]            PROGMEM = "application/x-font-ttf";
  static const char kOtf[]            PROGMEM = "application/x-font-opentype";
  static const char kWoff[]           PROGMEM = "application/font-woff";
  static const char kWoff2[]          PROGMEM = "application/font-woff2";
  static const char kEot[]            PROGMEM = "application/vnd.ms-fontobject";
  static const char kSfnt[]           PROGMEM = "application/font-sfnt";
  static const char kXml[]            PROGMEM = "text/xml";
  static const char kPdf[]            PROGMEM = "application/pdf";
  static const char kZip[]            PROGMEM = "application/zip";
  static const char kAppcache[]       PROGMEM = "text/cache-manifest";
#endif // MIMETYPE_MINIMAL

static const char kGz[]             PROGMEM = "application/x-gzip";
static const char kDefault[]        PROGMEM = "application/octet-stream";

const Entry mimeTable[maxType]      PROGMEM =
{
  { kHtmlSuffix,      kHtml },
  { kHtmSuffix,       kHtml },
  { kTxtSuffix,       kTxt },
#ifndef MIMETYPE_MINIMAL
  { kCssSuffix,       kCss },
  { kJsSuffix,        kJs },
  { kJsonSuffix,      kJson },
  { kPngSuffix,       kPng },
  { kGifSuffix,       kGif },
  { kJpgSuffix,       kJpg },
  { kJpegSuffix,      kJpeg },
  { kIcoSuffix,       kIco },
  { kSvgSuffix,       kSvg },
  { kTtfSuffix,       kTtf },
  { kOtfSuffix,       kOtf },
  { kWoffSuffix,      kWoff },
  { kWoff2Suffix,     kWoff2 },
  { kEotSuffix,       kEot },
  { kSfntSuffix,      kSfnt },
  { kXmlSuffix,       kXml },
  { kPdfSuffix,       kPdf },
  { kZipSuffix,       kZip },
  { kAppcacheSuffix,  kAppcache },
#endif // MIMETYPE_MINIMAL
  { kGzSuffix,        kGz },
  { kDefaultSuffix,   kDefault }
};

String getContentType(const String& path)
{
  for (size_t i = 0; i < maxType; i++)
  {
    if (path.endsWith(FPSTR(mimeTable[i].endsWith)))
    {
      return String(FPSTR(mimeTable[i].mimeType));
    }
  }

  // Fall-through and just return default type
  return String(FPSTR(kDefault));
}

}   // namespace mime_esp

#endif
