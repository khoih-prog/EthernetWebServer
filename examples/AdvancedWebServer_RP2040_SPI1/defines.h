/****************************************************************************************************************************
  defines.h
  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license
 ***************************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

#define USING_SPI2                          true

// Only one if the following to be true
#define USE_ETHERNET_GENERIC  true
#define USE_ETHERNET_ESP8266  false
#define USE_ETHERNET_ENC      false
#define USE_CUSTOM_ETHERNET   false

#if ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
  #if defined(ETHERNET_USE_RPIPICO)
    #undef ETHERNET_USE_RPIPICO
  #endif
  #define ETHERNET_USE_RPIPICO      true
#else
  #error Only RP2040 supported
#endif

#include <SPI.h>

#if defined(ARDUINO_ARCH_MBED)

  #if defined(BOARD_NAME)
    #undef BOARD_NAME
  #endif

  #if defined(ARDUINO_RASPBERRY_PI_PICO)
    #define BOARD_NAME      "MBED RASPBERRY_PI_PICO"
  #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
    #define BOARD_NAME      "MBED ADAFRUIT_FEATHER_RP2040"
  #elif defined(ARDUINO_GENERIC_RP2040)
    #define BOARD_NAME      "MBED GENERIC_RP2040"
  #else
    #define BOARD_NAME      "MBED Unknown RP2040"
  #endif

  // For RPI Pico using Mbed RP2040 core
  #if (USING_SPI2)
    #define USING_CUSTOM_SPI          true

    // SCK: GPIO14,  MOSI: GPIO15, MISO: GPIO12, SS/CS: GPIO13 for SPI1
    #define CUR_PIN_MISO              12
    #define CUR_PIN_MOSI              15
    #define CUR_PIN_SCK               14
    #define CUR_PIN_SS                13

    #define SPI_NEW_INITIALIZED       true

    // Don't create the instance with CUR_PIN_SS, or Ethernet not working
    // To change for other boards' SPI libraries
    #define SPIClass      arduino::MbedSPI

    // Be careful, Mbed SPI ctor is so weird, reversing the order => MISO, MOSI, SCK
    //arduino::MbedSPI::MbedSPI(int miso, int mosi, int sck)
    SPIClass SPI_New(CUR_PIN_MISO, CUR_PIN_MOSI, CUR_PIN_SCK);

    //#warning Using USE_THIS_SS_PIN = CUR_PIN_SS = 13

    #if defined(USE_THIS_SS_PIN)
      #undef USE_THIS_SS_PIN
    #endif
    #define USE_THIS_SS_PIN       CUR_PIN_SS    //13

  #else
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17 for SPI0
    #define USE_THIS_SS_PIN       PIN_SPI_SS    //17
  #endif

#else
  // For RPI Pico using E. Philhower RP2040 core
  #if (USING_SPI2)
    // SCK: GPIO14,  MOSI: GPIO15, MISO: GPIO12, SS/CS: GPIO13 for SPI1
    #define USE_THIS_SS_PIN       PIN_SPI1_SS   //13
  #else
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17 for SPI0
    #define USE_THIS_SS_PIN       PIN_SPI0_SS   //17
  #endif

#endif

#define SS_PIN_DEFAULT        USE_THIS_SS_PIN

// For RPI Pico
#warning Use RPI-Pico RP2040 architecture with custom SPI or SPI1

///////////////////////////////////////////////////////////

// W5100 chips can have up to 4 sockets.  W5200 & W5500 can have up to 8 sockets.
// Use EthernetLarge feature, Larger buffers, but reduced number of simultaneous connections/sockets (MAX_SOCK_NUM == 2)
#define ETHERNET_LARGE_BUFFERS

//////////////////////////////////////////////////////////

#include "Ethernet_Generic.h"

#if defined(ETHERNET_LARGE_BUFFERS)
  #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library with Large Buffer"
#else
  #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library"
#endif

#include <EthernetWebServer.h>

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "Unknown Ethernet shield/library"
#endif

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 222);

// Google DNS Server IP
IPAddress myDns(8, 8, 8, 8);

#endif    //defines_h
