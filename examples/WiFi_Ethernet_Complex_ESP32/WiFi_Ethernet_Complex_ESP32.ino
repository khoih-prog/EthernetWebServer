/****************************************************************************************************************************
  WiFi_Ethernet_Complex_ESP32.ino
  EthernetWebServer is a library for the Ethernet shields to run WebServer
  
  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license
 ***************************************************************************************************************************************/

// To demonstrate the coexistence of this EthernetWebServer and ESP32 WebServer library

#include "defines.h"

#include <WiFi.h>
#include <WebServer.h>

#include <SPI.h>
#include <EthernetWebServer.h>

const char* ssid     = "your_ssid";
const char* password = "your_password";

EthernetWebServer ethernetServer(80);
WebServer wifiServer(80);

const int led = 13;

void handleEthernetRoot() 
{
  ethernetServer.send(200, "text/plain", "Hello from ESP32 Ethernet!");
}

void handleWiFiRoot() 
{
  wifiServer.send(200, "text/plain", "Hello from ESP32 WiFi!");
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStarting WiFi_Ethernet_Complex_ESP32 on " + String(ARDUINO_BOARD));

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

#if defined(ESP32)

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
  
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
#endif

  // Just info to know how to connect correctly
  Serial.println("=========================");
  Serial.println("Currently Used SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("SS:");
  Serial.println(SS);
#if USE_ETHERNET3
  Serial.print("SPI_CS:");
  Serial.println(SPI_CS);
#endif

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  
  // start the ethernet connection and the server:
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

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
