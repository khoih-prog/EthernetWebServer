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

  Version: 2.4.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
  ...
  2.2.0   K Hoang      05/05/2022 Add support to custom SPI for Teensy, Mbed RP2040, Portenta_H7, etc.
  2.2.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  2.2.2   K Hoang      06/09/2022 Slow SPI clock for old W5100 shield or SAMD Zero. Improve support for SAMD21
  2.2.3   K Hoang      17/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.2.4   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.3.0   K Hoang      15/11/2022 Add new features, such as CORS. Update code and examples to send big data
  2.4.0   K Hoang      22/12/2022 Fix compile errors for new ESP32 core v2.0.6
  2.4.1   K Hoang      06/01/2023 Add support to `WIZNet W6100` using IPv4
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
