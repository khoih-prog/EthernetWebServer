/****************************************************************************************************************************
  base64.cpp - cpp source to a base64 encoding algorithm implementation

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

#include "base64.h"

/* Simple test program
#include <stdio.h>
void main()
{
    char* in = "amcewen";
    char out[22];

    b64_encode(in, 15, out, 22);
    out[21] = '\0';

    printf(out);
}
*/

int base64_encode(const unsigned char* aInput, int aInputLen, unsigned char* aOutput, int aOutputLen)
{
    // Work out if we've got enough space to encode the input
    // Every 6 bits of input becomes a byte of output
    if (aOutputLen < (aInputLen*8)/6)
    {
        // FIXME Should we return an error here, or just the length
        return (aInputLen*8)/6;
    }

    // If we get here we've got enough space to do the encoding

    const char* b64_dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (aInputLen == 3)
    {
        aOutput[0] = b64_dictionary[aInput[0] >> 2];
        aOutput[1] = b64_dictionary[(aInput[0] & 0x3)<<4|(aInput[1]>>4)];
        aOutput[2] = b64_dictionary[(aInput[1]&0x0F)<<2|(aInput[2]>>6)];
        aOutput[3] = b64_dictionary[aInput[2]&0x3F];
    }
    else if (aInputLen == 2)
    {
        aOutput[0] = b64_dictionary[aInput[0] >> 2];
        aOutput[1] = b64_dictionary[(aInput[0] & 0x3)<<4|(aInput[1]>>4)];
        aOutput[2] = b64_dictionary[(aInput[1]&0x0F)<<2];
        aOutput[3] = '=';
    }
    else if (aInputLen == 1)
    {
        aOutput[0] = b64_dictionary[aInput[0] >> 2];
        aOutput[1] = b64_dictionary[(aInput[0] & 0x3)<<4];
        aOutput[2] = '=';
        aOutput[3] = '=';
    }
    else
    {
        // Break the input into 3-byte chunks and process each of them
        int i;
        for (i = 0; i < aInputLen/3; i++)
        {
            base64_encode(&aInput[i*3], 3, &aOutput[i*4], 4);
        }
        if (aInputLen % 3 > 0)
        {
            // It doesn't fit neatly into a 3-byte chunk, so process what's left
            base64_encode(&aInput[i*3], aInputLen % 3, &aOutput[i*4], aOutputLen - (i*4));
        }
    }

    return ((aInputLen+2)/3)*4;
}

