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

#if ( defined(CORE_TEENSY) )
  // Default pin 10 to SS/CS
  #define USE_THIS_SS_PIN       SS    //10

  #if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #if defined(ARDUINO_TEENSY41)
      #define BOARD_TYPE      "TEENSY 4.1"
      // Use true for NativeEthernet Library, false if using other Ethernet libraries
      #define USE_NATIVE_ETHERNET     false
      #define USE_QN_ETHERNET         false
    #elif defined(ARDUINO_TEENSY40)
      #define BOARD_TYPE      "TEENSY 4.0"
    #else
      #define BOARD_TYPE      "TEENSY 4.x"
    #endif
  #elif defined(__MK66FX1M0__)
    #define BOARD_TYPE "Teensy 3.6"
  #elif defined(__MK64FX512__)
    #define BOARD_TYPE "Teensy 3.5"
  #elif defined(__MKL26Z64__)
    #define BOARD_TYPE "Teensy LC"
  #elif defined(__MK20DX256__)
    #define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
  #elif defined(__MK20DX128__)
    #define BOARD_TYPE "Teensy 3.0"
  #elif defined(__AVR_AT90USB1286__)
    #error Teensy 2.0++ not supported yet
  #elif defined(__AVR_ATmega32U4__)
    #error Teensy 2.0 not supported yet
  #else
    // For Other Boards
    #define BOARD_TYPE      "Unknown Teensy Board"
  #endif

  ///////////////////////////////////////////////////////

  #include <SPI.h>

  // For RPI Pico using Mbed RP2040 core
  #if (USING_SPI2)
    #define USING_CUSTOM_SPI          true

    // Teensy4.1
    // SCK1: 27,  MOSI1: 26, MISO1:  1, SS1/CS1:  0 for SPI1
    // SCK2: 45,  MOSI2: 43, MISO2: 32, SS2/CS2: 44 for SPI2
    // Teensy4.0, in the back, untested
    // SCK1: 27,  MOSI1: 26, MISO1: 1, SS1/CS1: 0 for SPI1
    #define CUR_PIN_MISO              1
    #define CUR_PIN_MOSI              26
    #define CUR_PIN_SCK               27
    #define CUR_PIN_SS                0

    #define SPI_NEW_INITIALIZED       true

    // SPI1
    SPIClass SPI_New((uintptr_t)&IMXRT_LPSPI3_S, (uintptr_t)&SPIClass::spiclass_lpspi3_hardware);
    // SPI2
    //SPIClass SPI_New((uintptr_t)&IMXRT_LPSPI1_S, (uintptr_t)&SPIClass::spiclass_lpspi1_hardware);

    #warning Using USE_THIS_SS_PIN = CUR_PIN_SS = 38

    #if defined(USE_THIS_SS_PIN)
      #undef USE_THIS_SS_PIN
    #endif
    #define USE_THIS_SS_PIN       CUR_PIN_SS

  #endif

#endif

///////////////////////////////////////////////////////

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#define SS_PIN_DEFAULT        USE_THIS_SS_PIN

// For RPI Pico
#warning Use Teensy architecture with custom SPI or SPI1/SPI2

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

//////////////////////////////////////////////////////////

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
