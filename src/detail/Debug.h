/****************************************************************************************************************************
   Debug.h - Dead simple Ethernet web-server.
   For Ethernet shields

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

#include <stdio.h>

#ifdef DEBUG_ETHERNET_WEBSERVER_PORT
#define ET_DEBUG_OUTPUT DEBUG_ETHERNET_WEBSERVER_PORT
#else
#define ET_DEBUG_OUTPUT Serial
#endif

// Change _ETHERNET_WEBSERVER_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ETHERNET_WEBSERVER_LOGLEVEL_
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#endif

const char EWS_MARK[]  = "[EWS] ";
const char EWS_SPACE[] = " ";
const char EWS_LINE[]  = "========================================\n";

#define EWS_PRINT_MARK   EWS_PRINT(EWS_MARK)
#define EWS_PRINT_SP     EWS_PRINT(EWS_SPACE)
#define EWS_PRINT_LINE   EWS_PRINT(EWS_LINE)

#define EWS_PRINT        ET_DEBUG_OUTPUT.print
#define EWS_PRINTLN      ET_DEBUG_OUTPUT.println

///////////////////////////////////////

#define ET_LOGERROR(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGERROR_LINE(x)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGERROR0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT(x); }
#define ET_LOGERROR1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGERROR2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGERROR3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGWARN(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGWARN_LINE(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGWARN0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT(x); }
#define ET_LOGWARN1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGWARN2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGWARN3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGINFO(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGINFO_LINE(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGINFO0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT(x); }
#define ET_LOGINFO1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGINFO2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGINFO3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGDEBUG(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGDEBUG_LINE(x)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGDEBUG0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT(x); }
#define ET_LOGDEBUG1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGDEBUG2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGDEBUG3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

