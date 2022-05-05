/****************************************************************************************************************************
  Ethernet_URLEncoder.cpp - Dead simple HTTP WebClient.
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

// Library to simplify HTTP fetching on Arduino
// (c) Copyright Arduino. 2019
// Released under Apache License, version 2.0

#define _ETHERNET_WEBSERVER_LOGLEVEL_     0

#include "detail/Debug.h"
#include "Ethernet_HTTPClient/Ethernet_URLEncoder.h"

EthernetURLEncoderClass::EthernetURLEncoderClass()
{
}

EthernetURLEncoderClass::~EthernetURLEncoderClass()
{
}

String EthernetURLEncoderClass::encode(const char* str)
{
  return encode(str, strlen(str));
}

String EthernetURLEncoderClass::encode(const String& str)
{
  return encode(str.c_str(), str.length());
}

String EthernetURLEncoderClass::encode(const char* str, int length)
{
  String encoded;

  encoded.reserve(length);

  for (int i = 0; i < length; i++) 
  {
    char c = str[i];

    const char HEX_DIGIT_MAPPER[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    if (isAlphaNumeric(c) || (c == '-') || (c == '.') || (c == '_') || (c == '~')) 
    {
      encoded += c;
    } 
    else 
    {
      char s[4];

      s[0] = '%';
      s[1] = HEX_DIGIT_MAPPER[(c >> 4) & 0xf];
      s[2] = HEX_DIGIT_MAPPER[(c & 0x0f)];
      s[3] = 0;

      encoded += s;
    }
  }

  return encoded;
}

EthernetURLEncoderClass EthernetURLEncoder;
