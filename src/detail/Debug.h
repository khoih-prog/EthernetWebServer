/****************************************************************************************************************************
   Debug.h - Dead simple Ethernet web-server.
   For Ethernet shields

   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license
   Version: 1.0.9

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
                                    Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, etc. 
                                    More Custom Ethernet libraries supported such as Ethernet2, Ethernet3, EthernetLarge
    1.0.6   K Hoang      27/04/2020 Add W5x00 support to ESP32/ESP8266 boards
    1.0.7   K Hoang      30/04/2020 Add ENC28J60 support to ESP32/ESP8266 boards  
    1.0.8   K Hoang      12/05/2020 Fix W5x00 support for ESP8266 boards.
    1.0.9   K Hoang      15/05/2020 Add EthernetWrapper.h for easier W5x00 support as well as more Ethernet libs in the future.    
 *****************************************************************************************************************************/

#ifndef EthernetWebServer_Debug_H
#define EthernetWebServer_Debug_H

#include <stdio.h>

#ifdef DEBUG_ETHERNET_WEBSERVER_PORT
#define DEBUG_OUTPUT DEBUG_ETHERNET_WEBSERVER_PORT
#else
#define DEBUG_OUTPUT Serial
#endif

// Change _ETHERNET_WEBSERVER_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ETHERNET_WEBSERVER_LOGLEVEL_
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2
#endif


#define LOGERROR(x)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); DEBUG_OUTPUT.println(x); }
#define LOGERROR1(x,y) if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); DEBUG_OUTPUT.print(x); DEBUG_OUTPUT.print(" "); DEBUG_OUTPUT.println(y); }
#define LOGWARN(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); DEBUG_OUTPUT.println(x); }
#define LOGWARN1(x,y)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); DEBUG_OUTPUT.print(x); DEBUG_OUTPUT.print(" "); DEBUG_OUTPUT.println(y); }
#define LOGINFO(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); DEBUG_OUTPUT.println(x); }
#define LOGINFO1(x,y)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); DEBUG_OUTPUT.print(x); DEBUG_OUTPUT.print(" "); DEBUG_OUTPUT.println(y); }

#define LOGDEBUG(x)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { DEBUG_OUTPUT.println(x); }
#define LOGDEBUG0(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { DEBUG_OUTPUT.print(x); }
#define LOGDEBUG1(x,y)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { DEBUG_OUTPUT.print(x); DEBUG_OUTPUT.print(" "); DEBUG_OUTPUT.println(y); }
#define LOGDEBUG2(x,y,z) if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { DEBUG_OUTPUT.print(x); DEBUG_OUTPUT.print(" "); DEBUG_OUTPUT.print(y); DEBUG_OUTPUT.print(" "); DEBUG_OUTPUT.println(z); }


#endif
