/****************************************************************************************************************************
  multiFileProject.ino
  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#define ETHERNET_WEBSERVER_VERSION_MIN_TARGET      "EthernetWebServer v2.2.4"
#define ETHERNET_WEBSERVER_VERSION_MIN             2002004

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <EthernetWebServer.h>      // https://github.com/khoih-prog/EthernetWebServer

void setup()
{
  SerialDebug.begin(115200);

  while (!SerialDebug && millis() < 5000);

  delay(500);

  SerialDebug.println("\nStart multiFileProject");
  SerialDebug.println(ETHERNET_WEBSERVER_VERSION);

#if defined(ETHERNET_WEBSERVER_VERSION_MIN)

  if (ETHERNET_WEBSERVER_VERSION_INT < ETHERNET_WEBSERVER_VERSION_MIN)
  {
    SerialDebug.print("Warning. Must use this example on Version equal or later than : ");
    SerialDebug.println(ETHERNET_WEBSERVER_VERSION_MIN_TARGET);
  }

#endif

  SerialDebug.print("You're OK now");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
