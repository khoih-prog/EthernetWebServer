/****************************************************************************************************************************
  base64.h - c source to a base64 encoding algorithm implementation

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov
 *************************************************************************************************************************************/

#pragma once

#ifndef BASE64_H
#define BASE64_H

int base64_encode(const unsigned char* aInput, int aInputLen, unsigned char* aOutput, int aOutputLen);

#endif    // BASE64_H
