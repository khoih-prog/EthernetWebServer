/****************************************************************************************************************************
  FS_EthernetWebServer.ino - Dead simple FS Ethernet WebServer for ES8266 using Ethernet shields

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
   1) Upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
   2) or you can upload the contents of a folder if you CD in that folder and run the following command:
      for file in `\ls -A1`; do curl -F "file=@$PWD/$file" localIPAddress/edit; done
   3) access the sample web page at http://localIPAddress/
*****************************************************************************************************************************/

#include "defines.h"

EthernetWebServer server(80);

//holds the current upload
File fsUploadFile;

void heartBeatPrint()
{
  static int num = 1;

  Serial.print(F("H"));        // H means alive

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
  static ulong checkstatus_timeout  = 0;
  static ulong current_millis;

#define HEARTBEAT_INTERVAL    10000L

  current_millis = millis();

  // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
  if ((current_millis > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = current_millis + HEARTBEAT_INTERVAL;
  }
}

//format bytes
String formatBytes(size_t bytes)
{
  if (bytes < 1024)
  {
    return String(bytes) + "B";
  }
  else if (bytes < (1024 * 1024))
  {
    return String(bytes / 1024.0) + "KB";
  }
  else if (bytes < (1024 * 1024 * 1024))
  {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
  else
  {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

String getContentType(const String& filename)
{
  if (server.hasArg("download"))
  {
    return "application/octet-stream";
  }
  else if (filename.endsWith(".htm"))
  {
    return "text/html";
  }
  else if (filename.endsWith(".html"))
  {
    return "text/html";
  }
  else if (filename.endsWith(".css"))
  {
    return "text/css";
  }
  else if (filename.endsWith(".js"))
  {
    return "application/javascript";
  }
  else if (filename.endsWith(".png"))
  {
    return "image/png";
  }
  else if (filename.endsWith(".gif"))
  {
    return "image/gif";
  }
  else if (filename.endsWith(".jpg"))
  {
    return "image/jpeg";
  }
  else if (filename.endsWith(".ico"))
  {
    return "image/x-icon";
  }
  else if (filename.endsWith(".xml"))
  {
    return "text/xml";
  }
  else if (filename.endsWith(".pdf"))
  {
    return "application/x-pdf";
  }
  else if (filename.endsWith(".zip"))
  {
    return "application/x-zip";
  }
  else if (filename.endsWith(".gz"))
  {
    return "application/x-gzip";
  }

  return "text/plain";
}

bool handleFileRead(String path)
{
  Serial.println("handleFileRead: " + path);

  if (path.endsWith("/"))
  {
    path += "index.htm";
  }

  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";

  if (filesystem->exists(pathWithGz) || filesystem->exists(path))
  {
    if (filesystem->exists(pathWithGz))
    {
      path += ".gz";
    }

    File file = filesystem->open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }

  return false;
}

void handleFileDelete()
{
  if (server.args() == 0)
  {
    return server.send(500, "text/plain", "BAD ARGS");
  }

  String path = server.arg(0);
  Serial.println("handleFileDelete: " + path);

  if (path == "/")
  {
    return server.send(500, "text/plain", "BAD PATH");
  }

  if (!filesystem->exists(path))
  {
    return server.send(404, "text/plain", "FileNotFound");
  }

  filesystem->remove(path);
  server.send(200, "text/plain", "");
  path.clear();
}

void handleFileCreate()
{
  if (server.args() == 0)
  {
    return server.send(500, "text/plain", "BAD ARGS");
  }

  String path = server.arg(0);
  Serial.println("handleFileCreate: " + path);

  if (path == "/")
  {
    return server.send(500, "text/plain", "BAD PATH");
  }

  if (filesystem->exists(path))
  {
    return server.send(500, "text/plain", "FILE EXISTS");
  }

  File file = filesystem->open(path, "w");

  if (file)
  {
    file.close();
  }
  else
  {
    return server.send(500, "text/plain", "CREATE FAILED");
  }

  server.send(200, "text/plain", "");
  path.clear();
}

void handleFileUpload()
{
  if (server.uri() != "/edit")
  {
    return;
  }

  ethernetHTTPUpload& upload = server.upload();

  if (upload.status == UPLOAD_FILE_START)
  {
    String filename = upload.filename;

    if (!filename.startsWith("/"))
    {
      filename = "/" + filename;
    }

    Serial.print(F("handleFileUpload Name: "));
    Serial.println(filename);
    fsUploadFile = filesystem->open(filename, "w");
    filename.clear();
  }
  else if (upload.status == UPLOAD_FILE_WRITE)
  {
    //Serial.print(F("handleFileUpload Data: ")); Serial.println(upload.currentSize);

    if (fsUploadFile)
    {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    if (fsUploadFile)
    {
      fsUploadFile.close();
    }

    Serial.print(F("handleFileUpload Size: "));
    Serial.println(upload.totalSize);
  }
}

void handleFileList()
{
  if (!server.hasArg("dir"))
  {
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }

  String path = server.arg("dir");
  Serial.println("handleFileList: " + path);
  Dir dir = filesystem->openDir(path);
  path.clear();

  String output = "[";

  while (dir.next())
  {
    File entry = dir.openFile("r");

    if (output != "[")
    {
      output += ',';
    }

    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir) ? "dir" : "file";
    output += "\",\"name\":\"";

    if (entry.name()[0] == '/')
    {
      output += &(entry.name()[1]);
    }
    else
    {
      output += entry.name();
    }

    output += "\"}";
    entry.close();
  }

  output += "]";
  server.send(200, "text/json", output);
}

void initFS()
{
  // Initialize LittleFS/SPIFFS file-system
  if (!FileFS.begin())
  {
    FileFS.format();

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

void listDir()
{
  Dir dir = filesystem->openDir("/");
  Serial.println(F("Opening / directory"));

  while (dir.next())
  {
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();
    Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
  }

  Serial.println();
}

void initWebserver()
{
  //SERVER INIT
  //list directory
  server.on("/list", HTTP_GET, handleFileList);

  //load editor
  server.on("/edit", HTTP_GET, []()
  {
    if (!handleFileRead("/edit.htm"))
    {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  //create file
  server.on("/edit", HTTP_PUT, handleFileCreate);

  //delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);

  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, []()
  {
    server.send(200, "text/plain", "");
  }, handleFileUpload);

  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([]()
  {
    if (!handleFileRead(server.uri()))
    {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, []()
  {
    String json('{');
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ", \"analog\":" + String(analogRead(A0));
    json += ", \"gpio\":" + String((uint32_t)(((GPI | GPO) & 0xFFFF) | ((GP16I & 0x01) << 16)));
    json += "}";
    server.send(200, "text/json", json);
    json.clear();
  });

  // Web Page handlers
  server.serveStatic("/", FileFS, "/page1.html");
  server.serveStatic("/page2", FileFS, "/page2.html");
  server.serveStatic("/page3", FileFS, "/page3.html");

  //server.serveStatic("/", SPIFFS, "/page1.html");
  //server.serveStatic("/page2", SPIFFS, "/page2.html");
  //server.serveStatic("/page3", SPIFFS, "/page3.html");

  // Other usage with various web site assets:
  // server.serveStatic("/assets/css/test.css", SPIFFS, "/assets/css/test.css"); // Style sheet
  // server.serveStatic("/assets/js/test_script.js", SPIFFS,"/assets/js/test_script.js"); // Javascript
  // server.serveStatic("/assets/font/fonticons.ttf", SPIFFS,"/assets/font/fonticons.ttf"); // font
  // server.serveStatic("/assets/picture.png", SPIFFS,"/assets/picture.png"); // Picture

  server.begin();
}

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  delay(200);

  Serial.print("\nStarting FS_EthernetWebServer on " + String(BOARD_TYPE));
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

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

  initFS();
  listDir();
  initWebserver();

  Serial.print("HTTP server started @");
  Serial.println(Ethernet.localIP());

  Serial.print(F("Open http://"));
  Serial.print(Ethernet.localIP());
  Serial.println(F("/edit to see the file browser"));
}

void loop()
{
  server.handleClient();
}
