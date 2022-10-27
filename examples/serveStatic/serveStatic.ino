/****************************************************************************************************************************
  serveStatic.ino - Dead simple web-server for Ethernet shields
                     demoing the usage of serveStatic class method
  v. 1.0
  Copyright (C) 2021 Sardar Azari
  https://www.qrz.com/db/ac8l

  Prior to the usage - use ESP8266/ESP32 Sketch data upoad tool to save the content of web-site to the SPIFFS flash memory.

  This example sketch is based on HTML templates from Robert Ulbricht: https://www.arduinoslovakia.eu
  https://github.com/RoboUlbricht/arduinoslovakia/tree/master/esp8266/simple_http_server_multiplepages_responsive_spiffs

  This code's core is based on HelloServer.ino example of this library by Khoi Hoang

  Some great examples of commercial use of serveStatic function can be seen and learned at uStepper's WiFiGUI project:
  https://github.com/uStepper/uStepperSWiFiGUI

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license
 *****************************************************************************************************************************/
/*****************************************************************************************************************************
   The Arduino board communicates with the shield using the SPI bus. This is on digital pins 11, 12, and 13 on the Uno
   and pins 50, 51, and 52 on the Mega. On both boards, pin 10 is used as SS. On the Mega, the hardware SS pin, 53,
   is not used to select the Ethernet controller chip, but it must be kept as an output or the SPI interface won't work.
*****************************************************************************************************************************/
/*****************************************************************************************************************************
   How To Use:
   1) Run the serveStaticLoadFile.ino
   2) Upload the contents of a folder if you changedir in that folder and run the following command:
      for file in `\ls -A1`; do curl -F "file=@$PWD/$file" localIPAddress/edit; done
   3) access the sample web page at http://localIPAddress/
*****************************************************************************************************************************/

// Important: For ESP32, check https://github.com/khoih-prog/EthernetWebServer#7-for-fixing-esp32-compile-error
// and replace cores/esp32/Server.h to avoid compile error

#include "defines.h"

EthernetWebServer server(80);

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  delay(200);

  Serial.print("\nStarting serveStatic demoing 'serveStatic' function on " + String(BOARD_TYPE));
  Serial.print(" using ");
  Serial.println(FS_Name);
  Serial.println("With " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_WEBSERVER_VERSION);

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

#if defined(ESP8266)
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

#endif    //defined(ESP8266)

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

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

  initFS();
  initWebserver();

  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}

void initFS()
{
  // Initialize LittleFS/SPIFFS file-system
#if (ESP32)
  // Format SPIFFS if not yet
  if (!FileFS.begin(true))
  {
    Serial.println(F("SPIFFS/LittleFS failed! Formatting."));
#else

  if (!FileFS.begin())
  {
    FileFS.format();
#endif

    if (!FileFS.begin())
    {
      while (true)
      {
#if USE_LITTLEFS
        Serial.println(F("LittleFS failed!. Please use SPIFFS."));
#else
        Serial.println(F("SPIFFS failed!. Please use LittleFS."));
#endif
        // Stay forever here as useless to go further
        delay(5000);
      }
    }
  }
}

void initWebserver()
{
  // Web Page handlers
  server.serveStatic("/", FileFS, "/page1.html");
  server.serveStatic("/page2", FileFS, "/page2.html");
  server.serveStatic("/page3", FileFS, "/page3.html");

  // Other usage with various web site assets:
  // server.serveStatic("/assets/css/test.css", SPIFFS, "/assets/css/test.css"); // Style sheet
  // server.serveStatic("/assets/js/test_script.js", SPIFFS,"/assets/js/test_script.js"); // Javascript
  // server.serveStatic("/assets/font/fonticons.ttf", SPIFFS,"/assets/font/fonticons.ttf"); // font
  // server.serveStatic("/assets/picture.png", SPIFFS,"/assets/picture.png"); // Picture

  server.begin();
}
