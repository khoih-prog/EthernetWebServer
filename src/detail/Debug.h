/****************************************************************************************************************************
 * Debug.h - Dead simple Ethernet web-server.
 * For Ethernet shields
 *
 * EthernetWebServer is a library for the Ethernet shields to run WebServer
 *
 * Forked and modified from ESP8266 https://github.com/esp8266/Arduino/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
 * Licensed under MIT license
 * Version: 1.0.2
 *
 * Original author:
 * @file       Esp8266WebServer.h
 * @author     Ivan Grokhotkov
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
 *  1.0.1   K Hoang      20/02/2020 Add support to lambda functions
 *  1.0.2   K Hoang      20/02/2020 Add support to UIPEthernet library for ENC28J60
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
#define _ETHERNET_WEBSERVER_LOGLEVEL_       1
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
