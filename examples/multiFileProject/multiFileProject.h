/****************************************************************************************************************************
  multiFileProject.h
  EthernetWebServer is a library for the Ethernet shields to run WebServer
  
  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#define _ETHERNET_WEBSERVER_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <EthernetWebServer.hpp>      // https://github.com/khoih-prog/EthernetWebServer

#include <EthernetHttpClient.h>       // https://github.com/khoih-prog/EthernetWebServer
