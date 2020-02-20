/****************************************************************************************************************************
 * HTTPBasicAuth.h - Dead simple web-server for Ethernet shields
 *
 * EthernetWebServer is a library for the Ethernet shields to run WebServer
 *
 * Forked and modified from ESP8266 https://github.com/esp8266/Arduino/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
 * Licensed under MIT license
 * Version: 1.0.1
 *
 * Original author:
 * @file       Esp8266WebServer.h
 * @author     Ivan Grokhotkov
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
 *  1.0.1   K Hoang      20/02/2020 Add support to lambda functions
 *  1.0.2   K Hoang      20/02/2020 Add support to UIPEthernet library for ENC28J60
 *****************************************************************************************************************************/
/*
  * The Arduino board communicates with the shield using the SPI bus. This is on digital pins 11, 12, and 13 on the Uno 
  * and pins 50, 51, and 52 on the Mega. On both boards, pin 10 is used as SS. On the Mega, the hardware SS pin, 53, 
  * is not used to select the Ethernet controller chip, but it must be kept as an output or the SPI interface won't work.
  */

#include <SPI.h>

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)
#define USE_UIP_ETHERNET   true

#include <EthernetWebServer.h>

#ifdef CORE_TEENSY
  // For Teensy 4.0
  #if defined(__IMXRT1062__)
  #define BOARD_TYPE      "TEENSY 4.0"
  #elif ( defined(__MKL26Z64__) || defined(ARDUINO_ARCH_AVR) )
  #define BOARD_TYPE      "TEENSY LC or 2.0"
  #else
  #define BOARD_TYPE      "TEENSY 3.X"
  #endif
#else
// For Mega
#define BOARD_TYPE      "AVR Mega"
#endif

// Enter a MAC address and IP address for your controller below.

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 100);

EthernetWebServer server(80);

const char* www_username = "admin";
const char* www_password = "ethernet";

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStarting HTTPBasicAuth on " + String(BOARD_TYPE));

  // start the ethernet connection and the server:
  Ethernet.begin(mac, ip);

  server.on("/", []() 
  {
    if (!server.authenticate(www_username, www_password)) 
    {
      return server.requestAuthentication();
    }
    server.send(200, "text/plain", "Login OK");
  });
  
  server.begin();

  Serial.print(F("HTTP EthernetWebServer started @ IP : "));
  Serial.println(Ethernet.localIP());

  Serial.print(F("Open http://"));
  Serial.print(Ethernet.localIP());
  Serial.println(F("/ in your browser to see it working"));
}

void loop() 
{
   server.handleClient();
}
