/****************************************************************************************************************************
   Ethernet_WebSocketClient.cpp - Dead simple HTTP WebSockets Client.
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

#define _ETHERNET_WEBSERVER_LOGLEVEL_     0

#include "libb64/base64.h"

#include "detail/Debug.h"
#include "Ethernet_HTTPClient/Ethernet_WebSocketClient.h"

EthernetWebSocketClient::EthernetWebSocketClient(Client& aClient, const char* aServerName, uint16_t aServerPort)
  : EthernetHttpClient(aClient, aServerName, aServerPort),
    iTxStarted(false),
    iRxSize(0)
{
}

EthernetWebSocketClient::EthernetWebSocketClient(Client& aClient, const String& aServerName, uint16_t aServerPort)
  : EthernetHttpClient(aClient, aServerName, aServerPort),
    iTxStarted(false),
    iRxSize(0)
{
}

EthernetWebSocketClient::EthernetWebSocketClient(Client& aClient, const IPAddress& aServerAddress, uint16_t aServerPort)
  : EthernetHttpClient(aClient, aServerAddress, aServerPort),
    iTxStarted(false),
    iRxSize(0)
{
}

int EthernetWebSocketClient::begin(const char* aPath)
{
  // start the GET request
  beginRequest();
  connectionKeepAlive();
  
  int status = get(aPath);

  if (status == 0)
  {
    uint8_t randomKey[16];
    char base64RandomKey[25];

    // create a random key for the connection upgrade
    for (int i = 0; i < (int)sizeof(randomKey); i++)
    {
      randomKey[i] = random(0x01, 0xff);
    }
    
    memset(base64RandomKey, 0x00, sizeof(base64RandomKey));
    base64_encode(randomKey, sizeof(randomKey), (unsigned char*)base64RandomKey, sizeof(base64RandomKey));

    // start the connection upgrade sequence
    sendHeader("Upgrade", "websocket");
    sendHeader("Connection", "Upgrade");
    sendHeader("Sec-WebSocket-Key", base64RandomKey);
    sendHeader("Sec-WebSocket-Version", "13");
    endRequest();

    status = responseStatusCode();

    if (status > 0)
    {
      skipResponseHeaders();
    }
  }

  iRxSize = 0;

  // status code of 101 means success
  return (status == 101) ? 0 : status;
}

int EthernetWebSocketClient::begin(const String& aPath)
{
  return begin(aPath.c_str());
}

int EthernetWebSocketClient::beginMessage(int aType)
{
  if (iTxStarted)
  {
    // fail TX already started
    return 1;
  }

  iTxStarted = true;
  iTxMessageType = (aType & 0xf);
  iTxSize = 0;

  return 0;
}

int EthernetWebSocketClient::endMessage()
{
  if (!iTxStarted)
  {
    // fail TX not started
    return 1;
  }

  // send FIN + the message type (opcode)
  EthernetHttpClient::write(0x80 | iTxMessageType);

  // the message is masked (0x80)
  // send the length
  if (iTxSize < 126)
  {
    EthernetHttpClient::write(0x80 | (uint8_t)iTxSize);
  }
  else if (iTxSize < 0xffff)
  {
    EthernetHttpClient::write(0x80 | 126);
    EthernetHttpClient::write((iTxSize >> 8) & 0xff);
    EthernetHttpClient::write((iTxSize >> 0) & 0xff);
  }
  else
  {
    EthernetHttpClient::write(0x80 | 127);
    EthernetHttpClient::write((iTxSize >> 56) & 0xff);
    EthernetHttpClient::write((iTxSize >> 48) & 0xff);
    EthernetHttpClient::write((iTxSize >> 40) & 0xff);
    EthernetHttpClient::write((iTxSize >> 32) & 0xff);
    EthernetHttpClient::write((iTxSize >> 24) & 0xff);
    EthernetHttpClient::write((iTxSize >> 16) & 0xff);
    EthernetHttpClient::write((iTxSize >>  8) & 0xff);
    EthernetHttpClient::write((iTxSize >>  0) & 0xff);
  }

  uint8_t maskKey[4];

  // create a random mask for the data and send
  for (int i = 0; i < (int)sizeof(maskKey); i++)
  {
    maskKey[i] = random(0xff);
  }
  
  EthernetHttpClient::write(maskKey, sizeof(maskKey));

  // mask the data and send
  for (int i = 0; i < (int)iTxSize; i++) 
  {
    iTxBuffer[i] ^= maskKey[i % sizeof(maskKey)];
  }

  size_t txSize = iTxSize;

  iTxStarted = false;
  iTxSize = 0;

  return (EthernetHttpClient::write(iTxBuffer, txSize) == txSize) ? 0 : 1;
}

size_t EthernetWebSocketClient::write(uint8_t aByte)
{
  return write(&aByte, sizeof(aByte));
}

size_t EthernetWebSocketClient::write(const uint8_t *aBuffer, size_t aSize)
{
  if (iState < eReadingBody)
  {
    // have not upgraded the connection yet
    return EthernetHttpClient::write(aBuffer, aSize);
  }

  if (!iTxStarted)
  {
    // fail TX not   started
    return 0;
  }

  // check if the write size, fits in the buffer
  if ((iTxSize + aSize) > sizeof(iTxBuffer))
  {
    aSize = sizeof(iTxSize) - iTxSize;
  }

  // copy data into the buffer
  memcpy(iTxBuffer + iTxSize, aBuffer, aSize);

  iTxSize += aSize;

  return aSize;
}

int EthernetWebSocketClient::parseMessage()
{
  flushRx();

  // make sure 2 bytes (opcode + length)
  // are available
  if (EthernetHttpClient::available() < 2)
  {
    return 0;
  }

  // read open code and length
  uint8_t opcode = EthernetHttpClient::read();
  int length = EthernetHttpClient::read();

  if ((opcode & 0x0f) == 0)
  {
    // continuation, use previous opcode and update flags
    iRxOpCode |= opcode;
  }
  else
  {
    iRxOpCode = opcode;
  }

  iRxMasked = (length & 0x80);
  length   &= 0x7f;

  // read the RX size
  if (length < 126)
  {
    iRxSize = length;
  }
  else if (length == 126)
  {
    iRxSize = (EthernetHttpClient::read() << 8) | EthernetHttpClient::read();
  }
  else
  {
    iRxSize =   ((uint64_t)EthernetHttpClient::read() << 56) |
                ((uint64_t)EthernetHttpClient::read() << 48) |
                ((uint64_t)EthernetHttpClient::read() << 40) |
                ((uint64_t)EthernetHttpClient::read() << 32) |
                ((uint64_t)EthernetHttpClient::read() << 24) |
                ((uint64_t)EthernetHttpClient::read() << 16) |
                ((uint64_t)EthernetHttpClient::read() << 8)  |
                (uint64_t)EthernetHttpClient::read();
  }

  // read in the mask, if present
  if (iRxMasked)
  {
    for (int i = 0; i < (int)sizeof(iRxMaskKey); i++)
    {
      iRxMaskKey[i] = EthernetHttpClient::read();
    }
  }

  iRxMaskIndex = 0;

  if (TYPE_CONNECTION_CLOSE == messageType())
  {
    flushRx();
    stop();
    iRxSize = 0;
  }
  else if (TYPE_PING == messageType())
  {
    beginMessage(TYPE_PONG);
    
    while (available())
    {
      write(read());
    }
    
    endMessage();

    iRxSize = 0;
  }
  else if (TYPE_PONG == messageType())
  {
    flushRx();
    iRxSize = 0;
  }

  return iRxSize;
}

int EthernetWebSocketClient::messageType()
{
  return (iRxOpCode & 0x0f);
}

bool EthernetWebSocketClient::isFinal()
{
  return ((iRxOpCode & 0x80) != 0);
}

String EthernetWebSocketClient::readString()
{
  int avail = available();
  String s;

  if (avail > 0)
  {
    s.reserve(avail);

    for (int i = 0; i < avail; i++)
    {
      s += (char)read();
    }
  }

  return s;
}

int EthernetWebSocketClient::ping()
{
  uint8_t pingData[16];

  // create random data for the ping
  for (int i = 0; i < (int)sizeof(pingData); i++)
  {
    pingData[i] = random(0xff);
  }

  beginMessage(TYPE_PING);
  write(pingData, sizeof(pingData));
  
  return endMessage();
}

int EthernetWebSocketClient::available()
{
  if (iState < eReadingBody)
  {
    return EthernetHttpClient::available();
  }

  return iRxSize;
}

int EthernetWebSocketClient::read()
{
  byte b;

  if (read(&b, sizeof(b)))
  {
    return b;
  }

  return -1;
}

int EthernetWebSocketClient::read(uint8_t *aBuffer, size_t aSize)
{
  int readCount = EthernetHttpClient::read(aBuffer, aSize);

  if (readCount > 0)
  {
    iRxSize -= readCount;

    // unmask the RX data if needed
    if (iRxMasked)
    {
      for (int i = 0; i < (int)aSize; i++, iRxMaskIndex++)
      {
        aBuffer[i] ^= iRxMaskKey[iRxMaskIndex % sizeof(iRxMaskKey)];
      }
    }
  }

  return readCount;
}

int EthernetWebSocketClient::peek()
{
  int p = EthernetHttpClient::peek();

  if (p != -1 && iRxMasked)
  {
    // unmask the RX data if needed
    p = (uint8_t)p ^ iRxMaskKey[iRxMaskIndex % sizeof(iRxMaskKey)];
  }

  return p;
}

void EthernetWebSocketClient::flushRx()
{
  while (available())
  {
    read();
  }
}
