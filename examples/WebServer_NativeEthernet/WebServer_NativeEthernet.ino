/****************************************************************************************************************************
  WebServer_NativeEthernet.ino - Simple Arduino web server sample for Ethernet shield

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license
 *****************************************************************************************************************************/

#include "defines.h"

#define USING_STATIC_IP       false   //true

#if USING_STATIC_IP
  // Select the staticIP address according to your local network
  IPAddress ip        (192, 168, 2, 222);
  IPAddress gateway   (192, 168, 2, 1);
  IPAddress subnet    (255, 255, 255, 0);
#endif

int reqCount = 0;                // number of requests received

EthernetServer server(80);

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  Serial.print("\nStarting WebServer_NativeEthernet on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_WEBSERVER_VERSION);

  // start the ethernet connection and the server:
  // Use random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  Serial.print(F("Using mac index = "));
  Serial.println(index);

#if USING_STATIC_IP
  // Static IP
  //Ethernet.begin(mac, ip, gateway, subnet);
  Ethernet.begin(mac[index], ip);

  delay(2000);
#else
  // DHCP
  Ethernet.begin(mac[index]);

  delay(1000);
#endif

  Serial.print(F("EthernetWebServer started @ IP address: "));
  Serial.println(Ethernet.localIP());

  delay(2000);

  // start the web server on port 80
  server.begin();
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client)
  {
    Serial.println(F("New client"));
    // an http request ends with a blank line
    bool currentLineIsBlank = true;

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          Serial.println(F("Sending response"));

          // send a standard http response header
          // use \r\n instead of many println statements to speedup data send
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"  // the connection will be closed after completion of the response
            "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<h2>Hello World from ");
          client.print(BOARD_NAME);
          client.print("!</h2>\r\n");
          client.print("Requests received: ");
          client.print(++reqCount);
          client.print("<br>\r\n");
          client.print("Analog input A0: ");
          client.print(analogRead(0));
          client.print("<br>\r\n");
          client.print("</html>\r\n");
          break;
        }

        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
    Serial.println(F("Client disconnected"));
  }
}
