/****************************************************************************************************************************
  WiFi_Ethernet_Complex_ESP8266.ino
  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license
 ***************************************************************************************************************************************/

// To demonstrate the coexistence of this EthernetWebServer and ESP8266 ESP8266WebServer library

#include "defines.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <SPI.h>
#include <EthernetWebServer.h>

const char* ssid     = "your_ssid";
const char* password = "your_password";

EthernetWebServer ethernetServer(80);

ESP8266WebServer wifiServer(80);

const int led = 13;

void handleEthernetRoot()
{
  ethernetServer.send(200, "text/plain", "Hello from ESP8266 Ethernet!");
}

void handleWiFiRoot()
{
  wifiServer.send(200, "text/plain", "Hello from ESP8266 WiFi!");
}

void setup(void)
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStarting WiFi_Ethernet_Complex_ESP8266 on " + String(ARDUINO_BOARD));

  //////////////////////////////////////////////

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /////////////////////////////////////////////

#if USE_ETHERNET_GENERIC
  ET_LOGWARN(F("=========== USE_ETHERNET_GENERIC ==========="));
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

  // For ESP8266, change for other boards if necessary
#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   D2    // For ESP8266
#endif

  ET_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);

#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet           0                 X            X            X            X        0
  // Ethernet2          X                 X            X            X            X        0
  // Ethernet3          X                 X            X            X            X        0
  // EthernetLarge      X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  Ethernet.init (USE_THIS_SS_PIN);

#elif USE_CUSTOM_ETHERNET

  // You have to add initialization for your Custom Ethernet here
  // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
  Ethernet.init(USE_THIS_SS_PIN);

#endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  // Just info to know how to connect correctly
  Serial.println("=========================");
  Serial.println("Currently Used SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("CS/SS:");
  Serial.println(USE_THIS_SS_PIN);
  Serial.println(F("========================="));

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  ethernetServer.on("/", handleEthernetRoot);

  ethernetServer.begin();

  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(Ethernet.localIP());

  //////////////////////////////////

  wifiServer.on("/", handleWiFiRoot);

  wifiServer.begin();

  Serial.print(F("HTTP WiFiWebServer is @ IP : "));
  Serial.println(WiFi.localIP());
}

void loop()
{
  // listen for incoming clients
  ethernetServer.handleClient();

  wifiServer.handleClient();
}
