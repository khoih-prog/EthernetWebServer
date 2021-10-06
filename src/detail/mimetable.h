/****************************************************************************************************************************
   mimetable.h - Dead simple web-server.
   For Ethernet shields

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

#ifndef __MIMETABLE_H__
#define __MIMETABLE_H__

namespace mime
{

  enum type
  {
    html,
    htm,
    css,
    txt,
    js,
    json,
    png,
    gif,
    jpg,
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
    gz,
    appcache,
    none,
    maxType
  };

  struct Entry
  {
    const char endsWith[16]; 
    const char mimeType[32];
  };

  // Table of extension->MIME strings stored in PROGMEM, needs to be global due to GCC section typing rules
  const Entry mimeTable[maxType] = 
  {
      { ".html",      "text/html" },
      { ".htm",       "text/html" },
      { ".css",       "text/css" },
      { ".txt",       "text/plain" },
      { ".js",        "application/javascript" },
      { ".json",      "application/json" },
      { ".png",       "image/png" },
      { ".gif",       "image/gif" },
      { ".jpg",       "image/jpeg" },
      { ".ico",       "image/x-icon" },
      { ".svg",       "image/svg+xml" },
      { ".ttf",       "application/x-font-ttf" },
      { ".otf",       "application/x-font-opentype" },
      { ".woff",      "application/font-woff" },
      { ".woff2",     "application/font-woff2" },
      { ".eot",       "application/vnd.ms-fontobject" },
      { ".sfnt",      "application/font-sfnt" },
      { ".xml",       "text/xml" },
      { ".pdf",       "application/pdf" },
      { ".zip",       "application/zip" },
      { ".gz",        "application/x-gzip" },
      { ".appcache",  "text/cache-manifest" },
      { "",           "application/octet-stream" } 
  };
  //extern const Entry mimeTable[maxType];
} // namespace mime

#endif    // #ifndef __MIMETABLE_H__

