/****************************************************************************************************************************
  CustomHeader.ino - Simple Arduino web server sample for Ethernet shield

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license

  Custom request header example for the ArduinoHttpClient
  library. This example sends a GET and a POST request with a custom header every 5 seconds.

  based on SimpleGet example by Tom Igoe
  header modifications by Todd Treece
  modified 22 Jan 2019
  by Tom Igoe

 *****************************************************************************************************************************/

#include "defines.h"

char serverAddress[] = "192.168.2.112";  // server address
int port = 8080;

EthernetClient      client;
EthernetHttpClient  httpClient(client, serverAddress, port);

void setup()
{
  SerialDebug.begin(115200);

  while (!SerialDebug && millis() < 5000);

  SerialDebug.print("\nStarting CustomHeader on ");
  SerialDebug.print(BOARD_NAME);
  SerialDebug.print(F(" with "));
  SerialDebug.println(SHIELD_TYPE);
  SerialDebug.println(ETHERNET_WEBSERVER_VERSION);

#if USE_ETHERNET_PORTENTA_H7
  ET_LOGWARN(F("======== USE_PORTENTA_H7_ETHERNET ========"));
#elif USE_NATIVE_ETHERNET
  ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_ETHERNET_GENERIC
  ET_LOGWARN(F("=========== USE_ETHERNET_GENERIC ==========="));
#elif USE_ETHERNET_ESP8266
  ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
#elif USE_ETHERNET_ENC
  ET_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));
#else
  ET_LOGWARN(F("========================="));
#endif

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)

#if (USING_SPI2)
#if defined(CUR_PIN_MISO)
  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
  ET_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
  ET_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
  ET_LOGWARN1(F("SS:"),   CUR_PIN_SS);
  ET_LOGWARN(F("========================="));
#endif
#else
  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));
#endif

#if defined(ESP8266)
  // For ESP8266, change for other boards if necessary
#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   D2    // For ESP8266
#endif

  ET_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);

#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // EthernetGeneric    X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  Ethernet.init (USE_THIS_SS_PIN);

#elif USE_CUSTOM_ETHERNET

  // You have to add initialization for your Custom Ethernet here
  // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
  Ethernet.init(USE_THIS_SS_PIN);

#endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif defined(ESP32)

  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   5   //22    // For ESP32
#endif

  ET_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
  // Must use library patch for Ethernet, EthernetLarge libraries
  // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
  // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3

  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

#elif USE_CUSTOM_ETHERNET

  // You have to add initialization for your Custom Ethernet here
  // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
  Ethernet.init(USE_THIS_SS_PIN);

#endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif ETHERNET_USE_RPIPICO

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);

  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
#ifndef USE_THIS_SS_PIN
#if defined(ARDUINO_ARCH_MBED)
#define USE_THIS_SS_PIN   5     // For Arduino Mbed core
#else
#define USE_THIS_SS_PIN   17    // For E.Philhower core
#endif
#endif

  ET_LOGWARN1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
  // Must use library patch for Ethernet, EthernetLarge libraries
  // For RPI Pico using Arduino Mbed RP2040 core
  // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
  // For RPI Pico using E. Philhower RP2040 core
  // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
  // Default pin 5/17 to SS/CS

  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

#endif    //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

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
#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
  // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries

  Ethernet.init (USE_THIS_SS_PIN);

#elif USE_CUSTOM_ETHERNET

  // You have to add initialization for your Custom Ethernet here
  // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
  Ethernet.init(USE_THIS_SS_PIN);

#endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#endif    // defined(ESP8266)

#endif    // #if !(USE_NATIVE_ETHERNET)

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

#if !(USE_NATIVE_ETHERNET || USE_ETHERNET_PORTENTA_H7)
  ET_LOGWARN(F("========================="));

#if defined( ESP32 )
  // Just info to know how to connect correctly
  // To change for other SPI
  ET_LOGWARN(F("Currently Used SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), PIN_MOSI);
  ET_LOGWARN1(F("MISO:"), PIN_MISO);
  ET_LOGWARN1(F("SCK:"),  PIN_SCK);
  ET_LOGWARN1(F("SS:"),   PIN_SS);
#else
#if defined(CUR_PIN_MISO)
  ET_LOGWARN(F("Currently Used SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
  ET_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
  ET_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
  ET_LOGWARN1(F("SS:"),   CUR_PIN_SS);
#else
  ET_LOGWARN(F("Currently Used SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
#endif
#endif

  ET_LOGWARN(F("========================="));

#elif (USE_ETHERNET_PORTENTA_H7)

  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    SerialDebug.println("No Ethernet found. Stay here forever");

    while (true)
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }

  if (Ethernet.linkStatus() == LinkOFF)
  {
    SerialDebug.println("Not connected Ethernet cable");
  }

#endif

  SerialDebug.print(F("Using mac index = "));
  SerialDebug.println(index);

  SerialDebug.print(F("Connected! IP address: "));
  SerialDebug.println(Ethernet.localIP());
}

void loop()
{
  SerialDebug.println("Making GET request");
  httpClient.beginRequest();

  httpClient.get("/");
  httpClient.sendHeader("X-CUSTOM-HEADER", "custom_value");
  httpClient.endRequest();

  // read the status code and body of the response
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  SerialDebug.print("GET Status code: ");
  SerialDebug.println(statusCode);
  SerialDebug.print("GET Response: ");
  SerialDebug.println(response);

  SerialDebug.println("Wait five seconds");
  delay(5000);

  SerialDebug.println("Making POST request");
  String postData = "name=Alice&age=12";
  httpClient.beginRequest();
  httpClient.post("/");
  httpClient.sendHeader(HTTP_HEADER_CONTENT_TYPE, "application/x-www-form-urlencoded");
  httpClient.sendHeader(HTTP_HEADER_CONTENT_LENGTH, postData.length());
  httpClient.sendHeader("X-CUSTOM-HEADER", "custom_value");
  httpClient.endRequest();
  httpClient.write((const byte*)postData.c_str(), postData.length());
  // note: the above line can also be achieved with the simpler line below:
  //httpClient.print(postData);

  // read the status code and body of the response
  statusCode = httpClient.responseStatusCode();
  response = httpClient.responseBody();

  SerialDebug.print("POST Status code: ");
  SerialDebug.println(statusCode);
  SerialDebug.print("POST Response: ");
  SerialDebug.println(response);

  SerialDebug.println("Wait five seconds");
  delay(5000);
}
