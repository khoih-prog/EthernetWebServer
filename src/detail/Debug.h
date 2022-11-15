/****************************************************************************************************************************
  Debug.h - Dead simple Ethernet web-server.
  For Ethernet shields

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

#ifndef ETHERNET_WEBSERVER_DEBUG_H
#define ETHERNET_WEBSERVER_DEBUG_H

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

///////////////////////////////////////

#endif  // ETHERNET_WEBSERVER_DEBUG_H
