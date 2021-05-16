/****************************************************************************************************************************
   mimetable.cpp - Dead simple web-server.
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
