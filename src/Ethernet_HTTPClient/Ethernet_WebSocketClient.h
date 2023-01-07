/****************************************************************************************************************************
  Ethernet_WebSocketClient.h - Dead simple HTTP WebSockets Client.
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

// (c) Copyright Arduino. 2016
// Released under Apache License, version 2.0

#pragma once

#ifndef ETHERNET_WEBSOCKET_CLIENT_H
#define ETHERNET_WEBSOCKET_CLIENT_H

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
    EthernetWebSocketClient(Client& aClient, const String& aServerName,
                            uint16_t aServerPort = EthernetHttpClient::kHttpPort);
    EthernetWebSocketClient(Client& aClient, const IPAddress& aServerAddress,
                            uint16_t aServerPort = EthernetHttpClient::kHttpPort);

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

#endif  // ETHERNET_WEBSOCKET_CLIENT_H
