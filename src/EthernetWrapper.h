/****************************************************************************************************************************
   EthernetWrapper.h - Dead simple web-server.
   For Ethernet shields

   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license
   Version: 1.2.1

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
                                    Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, etc. 
                                    More Custom Ethernet libraries supported such as Ethernet2, Ethernet3, EthernetLarge
    1.0.6   K Hoang      27/04/2020 Add W5x00 support to ESP32/ESP8266 boards
    1.0.7   K Hoang      30/04/2020 Add ENC28J60 support to ESP32/ESP8266 boards  
    1.0.8   K Hoang      12/05/2020 Fix W5x00 support for ESP8266 boards.
    1.0.9   K Hoang      15/05/2020 Add EthernetWrapper.h for easier W5x00 support as well as more Ethernet libs in the future.
    1.0.10  K Hoang      21/07/2020 Fix bug not closing client and releasing socket.
    1.0.11  K Hoang      25/07/2020 Add support to Seeeduino SAMD21/SAMD51 boards. Restructure examples.
    1.0.12  K Hoang      15/09/2020 Add support to new EthernetENC library for ENC28J60. Add debug feature.
    1.0.13  K Hoang      24/09/2020 Restore support to PROGMEM-related commands, such as sendContent_P() and send_P()
    1.1.0   K Hoang      17/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
    1.2.0   K Hoang      04/12/2020 Add support to NativeEthernet Library for Teensy 4.1
    1.2.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
 *****************************************************************************************************************************/
#ifndef EthernetWrapper_h
#define EthernetWrapper_h

#include "detail/Debug.h"

#ifndef USE_UIP_ETHERNET
  // Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
  // Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)
  #define USE_UIP_ETHERNET   false
#endif  
  
#if ( defined(USE_ETHERNET_WRAPPER) && USE_ETHERNET_WRAPPER )
  #warning Use EthernetWrapper from EthernetWebServer

  // Note: To rename ESP628266 Ethernet lib files to Ethernet_ESP8266.h and Ethernet_ESP8266.cpp
  #if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )

    // Only one if the following to be true. Default to USE_ETHERNET 
    #ifndef USE_ETHERNET2
      #define USE_ETHERNET2         false
    #endif
    
    #ifndef USE_ETHERNET3
      #define USE_ETHERNET3         false
    #endif
    
    #ifndef USE_ETHERNET_LARGE
      #define USE_ETHERNET_LARGE    false
    #endif
    
    #ifndef USE_ETHERNET_ESP8266
      #define USE_ETHERNET_ESP8266  false
    #endif
    
    #ifndef USE_ETHERNET_ENC
      #define USE_ETHERNET_ENC      false
    #endif
    
    #ifndef USE_NATIVE_ETHERNET
      #define USE_NATIVE_ETHERNET      false
    #endif

    #if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET)
      #ifdef USE_CUSTOM_ETHERNET
        #undef USE_CUSTOM_ETHERNET
      #endif
      #define USE_CUSTOM_ETHERNET   false //true
    #endif
    
    #if USE_NATIVE_ETHERNET
      #include "NativeEthernet.h"
      #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
      #define SHIELD_TYPE           "Custom Ethernet using Teensy 4.1 NativeEthernet Library"
    #elif USE_ETHERNET3
      #include "Ethernet3.h"
      #warning Using Ethernet3 lib
      #define SHIELD_TYPE           "W5x00 using Ethernet3 Library"
    #elif USE_ETHERNET2
      #include "Ethernet2.h"
      #warning Using Ethernet2 lib
      #define SHIELD_TYPE           "W5x00 using Ethernet2 Library"
    #elif USE_ETHERNET_LARGE
      #include "EthernetLarge.h"
      #warning Using EthernetLarge lib
      #define SHIELD_TYPE           "W5x00 using EthernetLarge Library"
    #elif USE_ETHERNET_ESP8266
      #include "Ethernet_ESP8266.h"
      #warning Using Ethernet_ESP8266 lib 
      #define SHIELD_TYPE           "W5x00 using Ethernet_ESP8266 Library" 
    #elif USE_ETHERNET_ENC
      #include "EthernetENC.h"
      #warning Using EthernetENC lib
      #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"
    #elif USE_CUSTOM_ETHERNET
      #include "Ethernet_XYZ.h"
      #warning Using Custom Ethernet library from EthernetWrapper. You must include a library here or error.
      #define SHIELD_TYPE           "Custom Ethernet using Ethernet_XYZ Library"
    #else
      #ifdef USE_ETHERNET
        #undef USE_ETHERNET
      #endif
      #define USE_ETHERNET            true
      #include "Ethernet.h"
      #warning Using Ethernet lib
      #define SHIELD_TYPE           "W5x00 using Ethernet Library"
    #endif    //USE_ETHERNET3

    // Ethernet_Shield_W5200, EtherCard, EtherSia not supported
    // Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
    // Otherwise, standard Ethernet library will be used for W5x00
    
  #elif USE_UIP_ETHERNET
    #include "UIPEthernet.h"
    #warning Using UIPEthernet library
    #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"  
  #endif    //( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )


  void EthernetInit()
  {
#if !USE_UIP_ETHERNET
    // Just info to know how to connect correctly

    #if USE_NATIVE_ETHERNET
      ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
    #elif USE_ETHERNET
      ET_LOGWARN(F("=========== USE_ETHERNET ==========="));
    #elif USE_ETHERNET2
      ET_LOGWARN(F("=========== USE_ETHERNET2 ==========="));
    #elif USE_ETHERNET3
      ET_LOGWARN(F("=========== USE_ETHERNET3 ==========="));
    #elif USE_ETHERNET_LARGE
      ET_LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
    #elif USE_ETHERNET_ESP8266
      ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
    #elif USE_ETHERNET_ENC
      ET_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));
    #else
      ET_LOGWARN(F("========================="));
    #endif

      ET_LOGWARN(F("Default SPI pinout:"));
      ET_LOGWARN1(F("MOSI:"), MOSI);
      ET_LOGWARN1(F("MISO:"), MISO);
      ET_LOGWARN1(F("SCK:"),  SCK);
      ET_LOGWARN1(F("SS:"),   SS);
      ET_LOGWARN(F("========================="));
       
    #if defined(ESP8266)
      // For ESP8266, change for other boards if necessary
      #ifndef USE_THIS_SS_PIN
        #define USE_THIS_SS_PIN   D2    // For ESP8266
      #endif
      
      ET_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);
      
      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
        // For ESP8266
        // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
        // Ethernet           0                 X            X            X            X        0
        // Ethernet2          X                 X            X            X            X        0
        // Ethernet3          X                 X            X            X            X        0
        // EthernetLarge      X                 X            X            X            X        0
        // Ethernet_ESP8266   0                 0            0            0            0        0
        // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
        // Must use library patch for Ethernet, EthernetLarge libraries
        //Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (USE_THIS_SS_PIN);

      #elif USE_ETHERNET3
        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
        #ifndef ETHERNET3_MAX_SOCK_NUM
          #define ETHERNET3_MAX_SOCK_NUM      4
        #endif
        
        Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
        
      #elif USE_CUSTOM_ETHERNET

        // You have to add initialization for your Custom Ethernet here
        // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
        Ethernet.init(USE_THIS_SS_PIN);  

      #endif  //( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
        
    #elif defined(ESP32)

      // You can use Ethernet.init(pin) to configure the CS pin
      //Ethernet.init(10);  // Most Arduino shields
      //Ethernet.init(5);   // MKR ETH shield
      //Ethernet.init(0);   // Teensy 2.0
      //Ethernet.init(20);  // Teensy++ 2.0
      //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
      //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet
      
      #ifndef USE_THIS_SS_PIN
        #define USE_THIS_SS_PIN   22    // For ESP32
      #endif
      
      ET_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);
      
      // For other boards, to change if necessary
      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
        // Must use library patch for Ethernet, EthernetLarge libraries
        // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
        // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
           
        //Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (USE_THIS_SS_PIN);

      #elif USE_ETHERNET3
        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
        #ifndef ETHERNET3_MAX_SOCK_NUM
          #define ETHERNET3_MAX_SOCK_NUM      4
        #endif
        
        Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
        
      #elif USE_CUSTOM_ETHERNET

        // You have to add initialization for your Custom Ethernet here
        // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
        Ethernet.init(USE_THIS_SS_PIN);  
              
      #endif  //( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )

    #else   //defined(ESP8266)
      // unknown board, do nothing, use default SS = 10
      #ifndef USE_THIS_SS_PIN
        #define USE_THIS_SS_PIN   10    // For other boards
      #endif
      
      #if defined(BOARD_NAME)
        ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
      #else
        ET_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
      #endif

      // For other boards, to change if necessary
      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
        // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries

        Ethernet.init (USE_THIS_SS_PIN);

      #elif USE_ETHERNET3
        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
        #ifndef ETHERNET3_MAX_SOCK_NUM
          #define ETHERNET3_MAX_SOCK_NUM      4
        #endif
        
        Ethernet.setCsPin (USE_THIS_SS_PIN);
        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
        
      #elif USE_CUSTOM_ETHERNET

        // You have to add initialization for your Custom Ethernet here
        // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
        Ethernet.init(USE_THIS_SS_PIN);  
                        
      #endif  //( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
      
    #endif    //defined(ESP8266)
#endif  //#if !USE_UIP_ETHERNET
  }

#endif    //#if USE_ETHERNET_WRAPPER

#endif    //EthernetWrapper_h
