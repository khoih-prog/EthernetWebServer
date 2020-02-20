/****************************************************************************************************************************
 * HelloServer2.h - Dead simple web-server for Ethernet shields
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

const int led = 13;

void handleRoot() 
{
  //digitalWrite(led, 1);
  server.send(200, "text/plain", "Hello from EthernetWebServer");
  //digitalWrite(led, 0);
}

void handleNotFound() 
{
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) 
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  delay(1000);
  Serial.println("\nStarting HelloServer2 on " + String(BOARD_TYPE));

  // start the ethernet connection and the server:
  Ethernet.begin(mac, ip);
  
  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "This works as well");
  });

  server.on("/gif", []() {
    #ifdef CORE_TEENSY
    static const uint8_t gif[] = {
    #else
    static const uint8_t gif[] PROGMEM = {
    #endif
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];

    #ifdef CORE_TEENSY
    memcpy(gif_colored, gif, sizeof(gif));
    #else
    memcpy_P(gif_colored, gif, sizeof(gif));
    #endif
    
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;

    #ifdef CORE_TEENSY
    server.send(200, (char *) "image/gif", gif_colored, sizeof(gif_colored));
    #else
    server.send_P(200, "image/gif", gif_colored, sizeof(gif_colored));
    #endif
  });

  server.onNotFound(handleNotFound);

  server.begin();
    
  Serial.print(F("HTTP EthernetWebServer started @ IP : "));
  Serial.println(Ethernet.localIP());
}

void loop(void) 
{
  server.handleClient();
}
