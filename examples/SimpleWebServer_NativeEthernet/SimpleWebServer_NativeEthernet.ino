/****************************************************************************************************************************
  SimpleWebServer_NativeEthernet.ino - Dead simple web-server for Ethernet shields

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license

  Copyright (c) 2015, Majenko Technologies
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of Majenko Technologies nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************************************************/

#include <SPI.h>
#include <NativeEthernet.h>

#define LOCAL_DEBUG           1

#define USING_STATIC_IP       true

byte mac[] = { 0xFE, 0xED, 0xDE, 0xAD, 0xBE, 0xEF }; //physical mac address

#if USING_STATIC_IP
  IPAddress ip        (192, 168, 2, 222);
  IPAddress gateway   (192, 168, 2, 1);
  IPAddress subnet    (255, 255, 255, 0);
#endif

EthernetServer server(80); //server port

EthernetClient client;

String readString;

//////////////////////

#define BOARD_NAME    "Teensy 4.1 with NativeEthernet"

#define ETHERNET_SS_PIN     10

void handleRoot()
{
#define BUFFER_SIZE     512

  char temp[BUFFER_SIZE];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int day = hr / 24;

  hr = hr % 24;

  snprintf(temp, BUFFER_SIZE - 1,
           "<html>\
<head>\
<meta http-equiv='refresh' content='5'/>\
<title>AdvancedWebServer %s</title>\
<style>\
body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
</style>\
</head>\
<body>\
<h2>Hi from EthernetWebServer!</h2>\
<h3>on %s</h3>\
<p>Uptime: %d d %02d:%02d:%02d</p>\
</body>\
</html>", BOARD_NAME, BOARD_NAME, day, hr % 24, min % 60, sec % 60);

  client.println(temp);
}

#define ORIGINAL_STR_LEN        2048

void drawGraph()
{
  static String out;
  static uint16_t previousStrLen = ORIGINAL_STR_LEN;

  if (out.length() == 0)
  {
    Serial.print(F("String Len = 0, extend to"));
    Serial.println(ORIGINAL_STR_LEN);
    out.reserve(ORIGINAL_STR_LEN);
  }

  out = F( "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"310\" height=\"150\">\n" \
           "<rect width=\"310\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"3\" stroke=\"rgb(0, 0, 0)\" />\n" \
           "<g stroke=\"blue\">\n");

  char temp[70];

  int y = rand() % 130;

  for (int x = 10; x < 300; x += 10)
  {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }

  out += F("</g>\n</svg>\n");

#if (LOCAL_DEBUG > 1)
  Serial.print(F("String Len = "));
  Serial.println(out.length());
#endif

  if (out.length() > previousStrLen)
  {
#if LOCAL_DEBUG
    Serial.print(F("String Len > "));
    Serial.print(previousStrLen);
    Serial.print(F(", extend to"));
    Serial.println(out.length() + 48);
#endif

    previousStrLen = out.length() + 48;

    out.reserve(previousStrLen);
  }
  else
  {
    client.println(out);
  }
}

//////////////////////

void setup()
{
  //enable serial data print
  Serial.begin(115200);

  while (!Serial);

  Serial.print("SimpleWebServer_NativeEthernet on ");
  Serial.println(BOARD_NAME);

#if USING_STATIC_IP
  // Static IP
  //Ethernet.begin(mac, ip, gateway, subnet);
  Ethernet.begin(mac, ip);

  delay(2000);
#else
  // DHCP
  Ethernet.begin(mac);

  delay(1000);
#endif

  server.begin();

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());
}

void heartBeatPrint()
{
  static int num = 1;

  Serial.print(F("H"));

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout  = 0;

#define STATUS_CHECK_INTERVAL     10000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
#if !LOCAL_DEBUG
    heartBeatPrint();
#endif

    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void loop()
{
  // Create a client connection
  client = server.available();

  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        handleRoot();
        drawGraph();

        //stopping client
        client.stop();
      }
    }
  }

  check_status();
}
