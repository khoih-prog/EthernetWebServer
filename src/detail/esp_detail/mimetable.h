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
   
   Version: 1.7.1

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
    ...
    1.6.0   K Hoang      04/09/2021 Add support to QNEthernet Library for Teensy 4.1
    1.7.0   K Hoang      09/09/2021 Add support to Portenta H7 Ethernet
    1.7.1   K Hoang      04/10/2021 Change option for PIO `lib_compat_mode` from default `soft` to `strict`. Update Packages Patches
 *************************************************************************************************************************************/

#pragma once

#ifndef __ESP_MIMETABLE_H__
#define __ESP_MIMETABLE_H__

#if (ESP32 || ESP8266)

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

#endif    // #if (ESP32 || ESP8266)
#endif    // #ifndef __ESP_MIMETABLE_H__
