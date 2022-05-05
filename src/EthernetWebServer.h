/****************************************************************************************************************************
  EthernetWebServer.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov

  Version: 2.2.0

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
 *************************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_WEBSERVER_H
#define ETHERNET_WEBSERVER_H

/////////////////////////////////////////////////////////////////////////

#define ETHERNET_WEBSERVER_VERSION          "EthernetWebServer v2.2.0"

#define ETHERNET_WEBSERVER_VERSION_MAJOR    2
#define ETHERNET_WEBSERVER_VERSION_MINOR    2
#define ETHERNET_WEBSERVER_VERSION_PATCH    0

#define ETHERNET_WEBSERVER_VERSION_INT      2002000

/////////////////////////////////////////////////////////////////////////

#if USE_UIP_ETHERNET
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Using UIPEthernet library from EthernetWebServer
  #endif
#elif USE_CUSTOM_ETHERNET
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Using Custom Ethernet library from EthernetWebServer. You must include a library or error
  #endif
#elif !( ETHERNET_USE_PORTENTA_H7 || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC || \
         USE_NATIVE_ETHERNET || USE_QN_ETHERNET)
  #include <Ethernet_Generic.h>
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Using Ethernet_Generic library from EthernetWebServer
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#include "EthernetWebServer.hpp"
#include "EthernetWebServer-impl.h"
#include "Parsing-impl.h"

#endif  // ETHERNET_WEBSERVER_H
