/****************************************************************************************************************************
   Ethernet_WebSocketClient.h - Dead simple HTTP WebSockets Client.
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
 
// (c) Copyright Arduino. 2016
// Released under Apache License, version 2.0

#pragma once

#include <Arduino.h>

#include "detail/Debug.h"

#include "Ethernet_HTTPClient/Ethernet_HttpClient.h"

static const int TYPE_CONTINUATION     = 0x0;
static const int TYPE_TEXT             = 0x1;
static const int TYPE_BINARY           = 0x2;
static const int TYPE_CONNECTION_CLOSE = 0x8;
static const int TYPE_PING             = 0x9;
static const int TYPE_PONG             = 0xa;

class EthernetWebSocketClient : public EthernetHttpClient
{
  public:
    EthernetWebSocketClient(Client& aClient, const char* aServerName, uint16_t aServerPort = EthernetHttpClient::kHttpPort);
    EthernetWebSocketClient(Client& aClient, const String& aServerName, uint16_t aServerPort = EthernetHttpClient::kHttpPort);
    EthernetWebSocketClient(Client& aClient, const IPAddress& aServerAddress, uint16_t aServerPort = EthernetHttpClient::kHttpPort);

    /** Start the Web Socket connection to the specified path
      @param aURLPath     Path to use in request (optional, "/" is used by default)
      @return 0 if successful, else error
    */
    int begin(const char* aPath = "/");
    int begin(const String& aPath);

    /** Begin to send a message of type (TYPE_TEXT or TYPE_BINARY)
        Use the write or Stream API's to set message content, followed by endMessage
        to complete the message.
      @param aURLPath     Path to use in request
      @return 0 if successful, else error
    */
    int beginMessage(int aType);

    /** Completes sending of a message started by beginMessage
      @return 0 if successful, else error
    */
    int endMessage();

    /** Try to parse an incoming messages
      @return 0 if no message available, else size of parsed message
    */
    int parseMessage();

    /** Returns type of current parsed message
      @return type of current parsedMessage (TYPE_TEXT or TYPE_BINARY)
    */
    int messageType();

    /** Returns if the current message is the final chunk of a split
        message
      @return true for final message, false otherwise
    */
    bool isFinal();

    /** Read the current messages as a string
      @return current message as a string
    */
    String readString();

    /** Send a ping
      @return 0 if successful, else error
    */
    int ping();

    // Inherited from Print
    virtual size_t write(uint8_t aByte);
    virtual size_t write(const uint8_t *aBuffer, size_t aSize);
    
    // Inherited from Stream
    virtual int   available();
    /** Read the next byte from the server.
      @return Byte read or -1 if there are no bytes available.
    */
    virtual int read();
    virtual int read(uint8_t *buf, size_t size);
    virtual int peek();

  private:
    void flushRx();

  private:
    bool      iTxStarted;
    uint8_t   iTxMessageType;
    uint8_t   iTxBuffer[128];
    uint64_t  iTxSize;

    uint8_t   iRxOpCode;
    uint64_t  iRxSize;
    bool      iRxMasked;
    int       iRxMaskIndex;
    uint8_t   iRxMaskKey[4];
};

