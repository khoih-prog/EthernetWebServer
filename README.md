## EthernetWebServer

[![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/EthernetWebServer.svg)](https://github.com/khoih-prog/EthernetWebServer/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/EthernetWebServer/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/EthernetWebServer.svg)](http://github.com/khoih-prog/EthernetWebServer/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-EthernetWebServer/count.svg" title="EthernetWebServer Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-EthernetWebServer/count.svg" style="height: 30px;width: 200px;"></a>

---
---

## Table of Contents

* [Important Note from v2.3.0](#Important-Note-from-v230)
* [Important Note from v2.2.2](#Important-Note-from-v222)
* [Important Breaking Change from v2.0.0](#Important-Breaking-Change-from-v200)
* [Why do we need this EthernetWebServer library](#why-do-we-need-this-ethernetwebserver-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Changelog](changelog.md) 
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
  * [13. For Seeeduino nRF52840 boards](#13-For-Seeeduino-nRF52840-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
  * [8. For fixing ESP8266 compile error](#8-for-fixing-esp8266-compile-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Configuration Notes](#configuration-notes)
  * [1. How to select which built-in Ethernet or shield to use](#1-how-to-select-which-built-in-ethernet-or-shield-to-use)
  * [Important](#important)
  * [2. How to select another CS/SS pin to use](#2-how-to-select-another-csss-pin-to-use)
  * [3. How to use W5x00 with ESP8266](#3-how-to-use-w5x00-with-esp8266)
  * [4. How to increase W5x00 TX/RX buffer](#4-how-to-increase-w5x00-txrx-buffer)
  * [5. How to adjust sendContent_P() and send_P() buffer size](#5-how-to-adjust-sendcontent_p-and-send_p-buffer-size)
  * [6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library](#6-How-to-use-SPI2-for-ESP32-using-W5x00-and-Ethernet_Generic-Library)
  * [7. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library](#7-How-to-use-SPI1-for-RP2040-using-W5x00-and-Ethernet_Generic-Library)
  * [8. How to use SPI1/SPI2 for Teensy 4.x using W5x00 and Ethernet_Generic Library](#8-How-to-use-SPI1SPI2-for-Teensy-4x-using-W5x00-and-Ethernet_Generic-Library)
  * [9. Important Note for AVRDx using Arduino IDE](#9-Important-Note-for-AVRDx-using-Arduino-IDE) **New**
* [Usage](#usage)
  * [Init the CS/SS pin if use EthernetWrapper](#init-the-csss-pin-if-use-ethernetwrapper) 
  * [Class Constructor](#class-constructor)
  * [Basic Operation](#basic-operations)
  * [Advanced Options](#advanced-options)
  * [Other Function Calls](#other-function-calls)
* [Examples](#examples)
  * [Original Examples](#original-examples)
    * [ 1. AdvancedWebServer](examples/AdvancedWebServer)
    * [ 2. **SimpleWebServer_NativeEthernet**](examples/SimpleWebServer_NativeEthernet)
    * [ 3. HelloServer](examples/HelloServer)
    * [ 4. HelloServer2](examples/HelloServer2)
    * [ 5. HttpBasicAuth](examples/HttpBasicAuth)
    * [ 6. **MQTTClient_Auth**](examples/MQTTClient_Auth)
    * [ 7. **MQTTClient_Basic**](examples/MQTTClient_Basic)
    * [ 8. **MQTT_ThingStream**](examples/MQTT_ThingStream)
    * [ 9. PostServer](examples/PostServer)
    * [10. SimpleAuthentication](examples/SimpleAuthentication)
    * [11. UdpNTPClient](examples/UdpNTPClient)
    * [12. UdpSendReceive](examples/UdpSendReceive)
    * [13. WebClient](examples/WebClient)
    * [14. WebClient_ESP](examples/WebClient_ESP)
    * [15. WebClientRepeating](examples/WebClientRepeating)
    * [16. WebClientRepeating_ESP](examples/WebClientRepeating_ESP)
    * [17. WebServer](examples/WebServer)
    * [18. **WebServer_NativeEthernet**](examples/WebServer_NativeEthernet)
    * [19. **ESP32_FS_EthernetWebServer**](examples/ESP32_FS_EthernetWebServer)
    * [20. **FS_EthernetWebServer**](examples/FS_EthernetWebServer)
    * [21. **serveStatic**](examples/serveStatic)
    * [22. **serveStaticLoadFile**](examples/serveStaticLoadFile)
    * [23. **AdvancedWebServer_Ptr**](examples/AdvancedWebServer_Ptr)
    * [24. multiFileProject](examples/multiFileProject) **New**
    * [25. EthernetWebServer_BigData](examples/EthernetWebServer_BigData) **New** 
  * [HTTP and WebSocket Client New Examples](#http-and-websocket-client-new-examples)
    * [ 1. BasicAuthGet](examples/HTTPClient/BasicAuthGet)
    * [ 2. CustomHeader](examples/HTTPClient/CustomHeader)
    * [ 3. DweetGet](examples/HTTPClient/DweetGet)
    * [ 4. DweetPost](examples/HTTPClient/DweetPost)
    * [ 5. HueBlink](examples/HTTPClient/HueBlink)
    * [ 6. node_test_server](examples/HTTPClient/node_test_server)
    * [ 7. PostWithHeaders](examples/HTTPClient/PostWithHeaders)
    * [ 8. SimpleDelete](examples/HTTPClient/SimpleDelete)
    * [ 9. SimpleGet](examples/HTTPClient/SimpleGet)
    * [10. SimpleHTTPExample](examples/HTTPClient/SimpleHTTPExample)
    * [11. SimplePost](examples/HTTPClient/SimplePost)
    * [12. SimplePut](examples/HTTPClient/SimplePut)
    * [13. SimpleWebSocket](examples/HTTPClient/SimpleWebSocket)
  * [New Examples for Teensy 4.1 QNEthernet](#new-examples-for-teensy-41-qnethernet)
    * [ 1. **AdvancedWebServer**](examples/QNEthernet/AdvancedWebServer)
    * [ 2. **MQTTClient_Auth**](examples/QNEthernet/MQTTClient_Auth)
    * [ 3. **MQTTClient_Basic**](examples/QNEthernet/MQTTClient_Basic) 
    * [ 4. **MQTT_ThingStream**](examples/QNEthernet/MQTT_ThingStream) 
  * [New Examples for ESP32 and ESP8266 using with WebServer or ESP8266WebServer](#New-Examples-for-ESP32-and-ESP8266-using-with-WebServer-or-ESP8266WebServer)
    * [ 1. **WiFi_Ethernet_Complex_ESP32**](examples/WiFi_Ethernet_Complex_ESP32)
    * [ 2. **WiFi_Ethernet_Complex_ESP8266**](examples/WiFi_Ethernet_Complex_ESP8266)
  * [New Examples for ESP32 using SPI2](#New-Examples-for-ESP32-using-SPI2)
    * [ 1. **AdvancedWebServer_ESP32_SPI2**](examples/AdvancedWebServer_ESP32_SPI2) **New**
  * [New Examples for SPI1/SPI2](#New-Examples-for-SPI1SPI2)
    * [ 1. **AdvancedWebServer_RP2040_SPI1**](examples/AdvancedWebServer_RP2040_SPI1) **New**
    * [ 2. **AdvancedWebServer_Teensy4x_SPI1**](examples/AdvancedWebServer_Teensy4x_SPI1) **New**
* [Example AdvancedWebServer](#example-advancedwebserver)
  * [1. File AdvancedWebServer.ino](#1-file-advancedwebserverino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. AdvancedWebServer on NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library](#1-advancedwebserver-on-nrf52840_feather_express-with-enc28j60-using-ethernetenc-library)
  * [ 2. ENC28J60_WM_Config on ESP32 with ENC28J60 using UIPEthernet Library](#2-enc28j60_wm_config-on-esp32-with-enc28j60-using-uipethernet-library)
  * [ 3. SimpleWebSocket on SAM DUE with W5x00 using Ethernet_Generic Library](#3-simplewebsocket-on-sam-due-with-w5x00-using-Ethernet_Generic-Library)
  * [ 4. DweetPost on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library](#4-dweetpost-on-nrf52840_feather-with-w5x00-using-Ethernet_Generic-Library)
  * [ 5. ESP32_FS_EthernetWebServer on ESP32 using LittleFS with W5x00 using Ethernet_Generic Library](#5-esp32_fs_ethernetwebserver-on-esp32-using-littlefs-with-w5x00-using-Ethernet_Generic-Library)
  * [ 6. FS_EthernetWebServer on ESP8266 using LittleFS with W5x00 using Ethernet_Generic Library](#6-fs_ethernetwebserver-on-esp8266-using-littlefs-with-w5x00-using-Ethernet_Generic-Library)
  * [ 7. serveStatic on ESP8266 using LittleFS with W5x00 using Ethernet_Generic Library](#7-servestatic-on-esp8266-using-littlefs-with-w5x00-using-Ethernet_Generic-Library)
  * [ 8. SimpleWebServer_NativeEthernet on Teensy 4.1 with NativeEthernet library](#8-simplewebserver_nativeethernet-on-teensy-41-with-nativeethernet-library)
  * [ 9. AdvancedWebServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#9-advancedwebserver-on-mbed-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-Library)
  * [10. MQTTClient_Auth on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#10-mqttclient_auth-on-mbed-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-Library)
  * [11. AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#11-advancedwebserver-on-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-Library)
  * [12. UdpNTPClient on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#12-udpntpclient-on-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-Library)
  * [13. AdvancedWebServer on Teensy 4.1 using NativeEthernet Library](#13-advancedwebserver-on-teensy-41-using-nativeethernet-library)
  * [14. AdvancedWebServer on Teensy 4.1 using QNEthernet Library](#14-advancedwebserver-on-teensy-41-using-qnethernet-library)
  * [15. MQTTClient_Auth on Teensy 4.1 using QNEthernet Library](#15-mqttclient_auth-on-teensy-41-using-qnethernet-library)
  * [16. AdvancedWebServer on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library](#16-advancedwebserver-on-portenta_h7_m7-with-ethernet-using-portenta_ethernet-library)
  * [17. SimpleWebSocket on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library](#17-simplewebsocket-on-portenta_h7_m7-with-ethernet-using-portenta_ethernet-library)
  * [18. MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library](#18-mqttclient_auth-on-portenta_h7_m7-with-ethernet-using-portenta_ethernet-library)
  * [19. WiFi_Ethernet_Complex_ESP32 on ESP32_DEV](#19-WiFi_Ethernet_Complex_ESP32-on-ESP32_DEV)
  * [20. WiFi_Ethernet_Complex_ESP8266 on ESP8266_NODEMCU_ESP12E](#20-WiFi_Ethernet_Complex_ESP8266-on-ESP8266_NODEMCU_ESP12E)
  * [21. AdvancedWebServer_ESP32_SPI2 on ESP32_DEV with W5x00 using Ethernet_Generic Library on SPI2](#21-AdvancedWebServer_ESP32_SPI2-on-ESP32_DEV-with-W5x00-using-Ethernet_Generic-Library-on-SPI2)
  * [22. AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI1](#22-AdvancedWebServer-on-RASPBERRY_PI_PICO-with-W5x00-using-Ethernet_Generic-Library-on-SPI1)
  * [23. AdvancedWebServer_RP2040_SPI1 on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI1](#23-AdvancedWebServer_RP2040_SPI1-on-MBED-RASPBERRY_PI_PICO-with-W5x00-using-Ethernet_Generic-Library-on-SPI1)
  * [24. AdvancedWebServer_Teensy4x_SPI1 on TEENSY 4.1 with W5x00 using Ethernet_Generic Library on SPI1](#24-AdvancedWebServer_Teensy4x_SPI1-on-TEENSY-41-with-W5x00-using-Ethernet_Generic-Library-on-SPI1)
  * [25. AdvancedWebServer on Curiosity AVR_AVR128DA48 with W5x00 using Ethernet_Generic Library on SPI](#25-AdvancedWebServer-on-Curiosity-AVR_AVR128DA48-with-W5x00-using-Ethernet_Generic-Library-on-SPI)
  * [26. EthernetWebServer_BigData on NRF52840_FEATHER](#26-EthernetWebServer_BigData-on-NRF52840_FEATHER)
  * [27. EthernetWebServer_BigData on RASPBERRY_PI_PICO](#27-EthernetWebServer_BigData-on-RASPBERRY_PI_PICO)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Important Note from v2.3.0

The new [EthernetWebServer v2.3.0+](https://github.com/khoih-prog/EthernetWebServer/releases/tag/v2.3.0) combined with the new [Ethernet_Generic v2.7.0+](https://github.com/khoih-prog/Ethernet_Generic/releases/tag/v2.7.0) fixes severe limitation to permit sending much larger data than total than **2/4/8/16K** buffer of **W5x00 Ethernet**.

---

### Important Note from v2.2.2


To be safe for systems using old `W5100` shields, the **examples** are using `optional` conservative values for SPI clock speed of 14MHz and `SPI_MODE0`

For `SAMD21 M0`, such as `SAMD Zero`, SPI clock speed of 8MHz and `SPI_MODE0` are used.


```
// Default to use W5100. Must change to false for W5500, W5100S, for faster SPI clock
// Must use true for SAMD21, such as Zero, SAMD_FEATHER_M0_EXPRESS, etc.
#define USE_W5100                           true
```

To use with shields different from `W5100`, such as `W5200, W5500, W5100S`, change to 

```
// Default to use W5100. Must change to false for W5500, W5100S, for faster SPI clock
#define USE_W5100                           false
```

For Arduino SAMD21 Zero, in order to print to Terminal, use `SERIAL_PORT_USBVIRTUAL` == `SerialUSB`

```
// Use this for ARDUINO_SAMD_ZERO, etc. if can't print to terminal with Serial.print
#if defined(SERIAL_PORT_USBVIRTUAL)
  #define Serial          SERIAL_PORT_USBVIRTUAL
  #warning Using SAMD Zero SerialUSB
#endif
```

---

### Important Breaking Change from v2.0.0

From v2.0.0, **breaking** changes were made to permit coexistence with `ESP32 WebServer` and `ESP8266 ESP8266WebServer` libraries.

The changes will affect only ESP32 and ESP8266 code.

#### Using `ethernetHTTPUpload` instead of `HTTPUpload`

If `server` using `EthernetWebServer`, then use `ethernetHTTPUpload` instead of `HTTPUpload`. `HTTPUpload` can be used only with `server` using WiFi `WebServer` or `ESP8266WebServer`

For example, in these examples, `server` is using `EthernetWebServer`

- [ESP32_FS_EthernetWebServer.ino#L238](https://github.com/khoih-prog/EthernetWebServer/blob/master/examples/ESP32_FS_EthernetWebServer/ESP32_FS_EthernetWebServer.ino#L238)
- [FS_EthernetWebServer.ino#L235](https://github.com/khoih-prog/EthernetWebServer/blob/master/examples/FS_EthernetWebServer/FS_EthernetWebServer.ino#L235)

just change from

```
HTTPUpload& upload = server.upload();
```

to

```
ethernetHTTPUpload& upload = server.upload();
```

---


Please check these new examples to see how to use the new features

1. [WiFi_Ethernet_Complex_ESP32](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/WiFi_Ethernet_Complex_ESP32)
2. [WiFi_Ethernet_Complex_ESP8266](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/WiFi_Ethernet_Complex_ESP8266)

---

### Why do we need this [EthernetWebServer library](https://github.com/khoih-prog/EthernetWebServer)

#### Features

This [**EthernetWebServer library**](https://github.com/khoih-prog/EthernetWebServer) is a simple yet complete WebServer library for **AVR, Portenta_H7, Teensy, SAM DUE, Arduino SAMD21, Adafruit SAMD21/SAMD51, Adafruit nRF52, ESP32/ESP8266, STM32, RP2040-based, etc.** boards using Ethernet shields. The functions are similar and compatible to those of [`ESP32 WebServer`](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer) and [`ESP8266WebServer`](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer) libraries to make life much easier to port sketches from ESP8266/ESP32.

The **RP2040-based boards, such as RASPBERRY_PI_PICO**, are currently supported using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).

This [**EthernetWebServer library**](https://github.com/khoih-prog/EthernetWebServer), from v1.1.0, also provides high-level **HTTP and WebSocket Client** with the functions are similar and compatible to those of [**ArduinoHttpClient Library**](https://github.com/arduino-libraries/ArduinoHttpClient)

The library provides these features:

1. TCP Server and Client
2. UDP Server and Client
3. HTTP Server and Client
4. HTTP GET and POST requests, provides argument parsing, handles one client at a time.
5. **High-level HTTP (GET, POST, PUT, PATCH, DELETE) and WebSocket Client**. From v1.1.0.

Library is based on and modified from:

1. [Ivan Grokhotkov's ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)
2. [Ivan Grokhotkov's ESP32 WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
3. [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient)


The EthernetWebServer class, found in `EthernetWebServer.h` header, is a simple WebServer class, knowing how to handle HTTP requests such as GET and POST and can only support one simultaneous client.

#### Currently supported Boards

This [**EthernetWebServer** library](https://github.com/khoih-prog/EthernetWebServer) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 2. **SAM DUE**
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) with SPI, SPI1, SPI2**
 6. **AVR Mega1280, 2560, ADK.**
 7. ESP32
 8. ESP8266
 
 9. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico) with **SPI, SPI1**
 
 10. **Portenta_H7**
 
 11. **Arduino UNO WiFi Rev2, AVR_NANO_EVERY, etc.**
 
 12. **Arduino AVR_Dx boards using DxCore**

- **AVRDA-based boards (AVR128DA, AVR64DA, AVR32DA, etc.)**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/blob/main/pics/Curiosity_AVR128DA48.png">
</p>


- **AVRDB-based boards (AVR128DB, AVR64DB, AVR32DB, etc.)**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_TimerInterrupt/blob/main/pics/Curiosity_AVR128DB48.png">
</p>

 13. **Seeeduino nRF52840-based boards such as XIAO_NRF52840 and XIAO_NRF52840_SENSE**, etc. using Seeed `mbed` or `nRF52` core


#### Currently supported Ethernet shields/modules

1. W5x00 using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) library
2. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
3. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
4. Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
5. Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
6. Portenta_H7 Ethernet using [`Portenta_Ethernet`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/Ethernet) library

---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino AVR core 1.8.6+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Teensy core v1.57+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 5. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.11+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.3+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 9. [`ESP32 Core 2.0.5+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
10. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS.
11. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 3.4.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
12. [`Earle Philhower's arduino-pico core v2.6.3+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
13. [`Arduino megaAVR core 1.8.7+`](https://github.com/arduino/ArduinoCore-megaavr/releases) for Arduino megaAVR boards such as **Arduino UNO WiFi Rev2, AVR_NANO_EVERY, etc.**
14. [`SpenceKonde DxCore core 1.4.10+`](https://github.com/SpenceKonde/DxCore) for Arduino AVRDx boards.  [![GitHub release](https://img.shields.io/github/release/SpenceKonde/DxCore.svg)](https://github.com/SpenceKonde/DxCore/releases/latest). Follow [**DxCore Installation**](https://github.com/SpenceKonde/DxCore/blob/master/Installation.md).
15. [`Seeeduino nRF52 core 1.0.0+`](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino) for Seeed nRF52840-based boards such as **Seeed_XIAO_NRF52840 and Seeed_XIAO_NRF52840_SENSE**. [![GitHub release](https://img.shields.io/github/release/Seeed-Studio/Adafruit_nRF52_Arduino.svg)](https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino/releases/latest)
16. `Seeeduino mbed core 2.7.2+` for Seeed nRF52840-based boards such as **SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**
17. [`Functional-Vlpp library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
18. Depending on which Ethernet card you're using:
   - [`Ethernet_Generic library v2.7.0+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
   - [`EthernetENC library v2.0.3+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.12+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
   - [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1 built-in Ethernet.
   - [`QNEthernet Library version v0.16.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet. **New**

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `EthernetWebServer`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer) for more detailed instructions.

### Manual Install

1. Navigate to [EthernetWebServer](https://github.com/khoih-prog/EthernetWebServer) page.
2. Download the latest release `EthernetWebServer-master.zip`.
3. Extract the zip file to `EthernetWebServer-master` directory 
4. Copy the whole `EthernetWebServer-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**EthernetWebServer** library](https://registry.platformio.org/libraries/khoih-prog/EthernetWebServer) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/EthernetWebServer/installation). Search for EthernetWebServer in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.11) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.11). 

Supposing the Adafruit SAMD core version is 1.7.11. These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.3) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3). 

Supposing the Seeeduino SAMD core version is 1.8.3. These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.4. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/ambd/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.9.0. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino RP2040 core version is 2.7.2. These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---

#### 13. For Seeeduino nRF52840 boards

**To be able to compile and run on Xiao nRF52840 boards**, you have to copy the whole [nRF52 1.0.0](Packages_Patches/Seeeduino/hardware/nrf52/1.0.0) directory into Seeeduino nRF52 directory (~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0). 

Supposing the Seeeduino nRF52 version is 1.0.0. These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/platform.txt`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/platform.txt`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**


---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

You can also use the forked and modified library at [Patched Ethernet](https://github.com/khoih-prog/Ethernet)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

You can also use the forked and modified library at [Patched EthernetLarge](https://github.com/khoih-prog/EthernetLarge)

#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

You can also use the forked and modified library at [Patched Ethernet2](https://github.com/khoih-prog/Ethernet2)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

You can also use the forked and modified library at [Patched Ethernet3](https://github.com/khoih-prog/Ethernet3)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.19/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

#### 8. For fixing ESP8266 compile error

To fix `ESP8266 compile error` such as

```
error: 'class EthernetClass' has no member named 'init'
Ethernet.init (USE_THIS_SS_PIN);
```

just rename the following file in ./arduino-1.8.19/hardware/esp8266com/esp8266/libraries/Ethernet directory

- From `Ethernet.h` to `Ethernet_ESP8266.h`

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).


---
---

### Configuration Notes

#### 1. How to select which built-in Ethernet or shield to use

The easiest way is to use 

```cpp
#define USE_ETHERNET_WRAPPER    true
```

then select **one and only one** Ethernet library to use as follows:

- Standard W5x00 Ethernet_Generic library is used by default, in the sketch, just be sure to comment out or leave these #defines to be false :

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

To use W5x00 Ethernet, for example using Ethernet_Generic library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      true
#define USE_ETHERNET_ESP8266      false
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false
#define USE_ETHERNET_ENC          true
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using UIPEthernet library:

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          true
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```


- To use another Ethernet library
For example, EthernetLarge library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       true

//Must be placed before #include <EthernetWebServer.h>
#include <EthernetLarge.h>
...

#include <EthernetWebServer.h>
```

- Only for Teensy 4.1, to use NativeEthernet library

```cpp
#if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #if defined(ARDUINO_TEENSY41)
      #define BOARD_TYPE      "TEENSY 4.1"
      // Use true for NativeEthernet Library, false if using other Ethernet libraries
      #define USE_NATIVE_ETHERNET     true
      #define USE_QN_ETHERNET         false
    #elif defined(ARDUINO_TEENSY40)
      #define BOARD_TYPE      "TEENSY 4.0"
    #else
      #define BOARD_TYPE      "TEENSY 4.x"
    #endif      
  #elif defined(__MK66FX1M0__)
  ....
```

- Only for Teensy 4.1, to use another Ethernet library, for example Ethernet_Generic library

```cpp
#if defined(__IMXRT1062__)
  // For Teensy 4.1/4.0
  #if defined(ARDUINO_TEENSY41)
    #define BOARD_TYPE      "TEENSY 4.1"
    // Use true for NativeEthernet Library, false if using other Ethernet libraries
    #define USE_NATIVE_ETHERNET     false
    #define USE_QN_ETHERNET         false
  #elif defined(ARDUINO_TEENSY40)
    #define BOARD_TYPE      "TEENSY 4.0"
  #else
    #define BOARD_TYPE      "TEENSY 4.x"
  #endif      
#elif defined(__MK66FX1M0__)
  ....
  
#define USE_UIP_ETHERNET        false

// Only one if the following to be true
#define USE_ETHERNET_GENERIC    true
#define USE_ETHERNET_ESP8266    false
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false  
```

- Only for Teensy 4.1, to use QNEthernet library

```cpp
#if ( defined(CORE_TEENSY) && defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41) ) 
  // For Teensy 4.1
  #define BOARD_TYPE      "TEENSY 4.1"
  // Use true for NativeEthernet Library, false if using other Ethernet libraries
  #define USE_NATIVE_ETHERNET     false
  #define USE_QN_ETHERNET         true
#else
  #error Only Teensy 4.1 supported
#endif

#define USE_ETHERNET_WRAPPER    false

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

#define USE_UIP_ETHERNET        false
#define USE_ETHERNET_GENERIC    false
#define USE_ETHERNET_ESP8266    false 
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false

#if USE_NATIVE_ETHERNET
  #include "NativeEthernet.h"
  #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using NativeEthernet"
#elif USE_QN_ETHERNET
  #include "QNEthernet.h"
  using namespace qindesign::network;
  #warning Using QNEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using QNEthernet"  
#endif 
```

---

#### Important:

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.

---

#### 2. How to select another CS/SS pin to use

The default CS/SS pin is GPIO4(D2) for ESP8266, GPIO22 for ESP32, 10 for all other boards.

If the default pin is not correct, the easiest way is to select the CS/SS pin (e.g. 22) to use as follows:

```cpp
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
#define USE_THIS_SS_PIN   22
```

#### 3. How to use W5x00 with ESP8266

To avoid using the default but not-working Ethernet library of ESP8266, rename the Ethernet.h/cpp to Ethernet_ESP8266.h/cpp to avoid library conflict if you're using the Arduino Ethernet library. The Ethernet_Generic, Ethernet2, Ethernet3, EthernetLarge library can be used without conflict.

These pins are tested OK with ESP8266 and W5x00

```cpp
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet           0                 X            X            X            X        0
  // Ethernet2          X                 X            X            X            X        0
  // Ethernet3          X                 X            X            X            X        0
  // EthernetLarge      X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

```

#### 4. How to increase W5x00 TX/RX buffer

- For **Ethernet_Generic** library only,  simply use as follows to have large buffer similar to EthernetLarge library

```cpp
#define ETHERNET_LARGE_BUFFERS
```

- For **Ethernet3** library only,  use as follows

```cpp
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```

### 5. How to adjust sendContent_P() and send_P() buffer size

sendContent_P() and send_P() buffer size is set default at 4 Kbytes, and minimum is 256 bytes. If you need to change, just add a definition, e.g.:

```cpp
#define SENDCONTENT_P_BUFFER_SZ     2048
```

Note that the buffer size must be larger than 256 bytes. See [Sending GZIP HTML ~ 120kb+ (suggested enhancement)](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/3).


### 6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI2` for ESP32

```cpp
#define USING_SPI2                          true
```

Pin to use for `SPI2`

```
MOSI:  13
MISO:  12
SCK:   14
SS:    5
```

### 7. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI1` for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico) or [ArduinoCore-mbed](https://github.com/arduino/ArduinoCore-mbed)

```cpp
#define USING_SPI2                          true
```

Pin to use for `SPI1`

```
MOSI:  15
MISO:  12
SCK:   14
SS:    13
```

### 8. How to use SPI1/SPI2 for Teensy 4.x using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI1/SPI2` for Teensy 4.x

```cpp
#include <SPI.h>

  // For RPI Pico using Mbed RP2040 core
#if (USING_SPI2)
  #define USING_CUSTOM_SPI          true

  // Teensy4.1
  // SCK1: 27,  MOSI1: 26, MISO1:  1, SS1/CS1:  0 for SPI1
  // SCK2: 45,  MOSI2: 43, MISO2: 32, SS2/CS2: 44 for SPI2
  // Teensy4.0, in the back, untested
  // SCK1: 27,  MOSI1: 26, MISO1: 1, SS1/CS1: 0 for SPI1
  #define CUR_PIN_MISO              1
  #define CUR_PIN_MOSI              26
  #define CUR_PIN_SCK               27
  #define CUR_PIN_SS                0

  #define SPI_NEW_INITIALIZED       true

  // SPI1
  SPIClass SPI_New((uintptr_t)&IMXRT_LPSPI3_S, (uintptr_t)&SPIClass::spiclass_lpspi3_hardware);
  // SPI2
  //SPIClass SPI_New((uintptr_t)&IMXRT_LPSPI1_S, (uintptr_t)&SPIClass::spiclass_lpspi1_hardware);
  
  #warning Using USE_THIS_SS_PIN = CUR_PIN_SS = 38

  #if defined(USE_THIS_SS_PIN)
    #undef USE_THIS_SS_PIN
  #endif   
  #define USE_THIS_SS_PIN       CUR_PIN_SS

#endif  
```

Pin to use for `SPI1`

```
MOSI:  26
MISO:   1
SCK:   27
SS:     0
```

Pin to use for `SPI2`

```
MOSI:  43
MISO:  32
SCK:   45
SS:    44
```

#### 9. Important Note for AVRDx using Arduino IDE

With some Arduino IDE versions, such as v1.8.19, upload directly via USB to some boards, such as `Curiosity_AVR128DA48` or `Curiosity_AVR128DB48` can't be done without unknown-to-me fix. We'll get the following error when uploading

```
avrdude: Version 6.3-20201216
     Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
     Copyright (c) 2007-2014 Joerg Wunsch

     System wide configuration file is "/home/kh/.arduino15/packages/DxCore/hardware/megaavr/1.4.10/avrdude.conf"
     User configuration file is "/home/kh/.avrduderc"
     User configuration file does not exist or is not a regular file, skipping

     Using Port                    : usb
     Using Programmer              : curiosity_updi
avrdude: usbdev_open(): Found nEDBG CMSIS-DAP, serno: MCHP3280041800002682
avrdude: usbdev_open(): WARNING: failed to set configuration 1: Device or resource busy
avrdude: Found CMSIS-DAP compliant device, using EDBG protocol
avrdude: usbdev_send(): wrote -5 out of 912 bytes, err = Input/output error
avrdude: jtag3_edbg_prepare(): failed to send command to serial port

avrdude done.  Thank you.

the selected serial port 
 does not exist or your board is not connected
```

We can use drag-and-drop method to `drag-and-drop` the compiled **hex** file to `CURIOSITY` virtual drive. 

If `success`, The LED blinks **slowly** for 2 sec. The LED will blinks **rapidly** for 2 sec if `failure`


For example, to run [Change_Interval example](https://github.com/khoih-prog/Ethernet_Generic/tree/main/examples/Change_Interval), use Arduino IDE to compile, and get the `Change_Interval.ino.hex` file. For Ubuntu Linux, the file is stored in directory `/tmp/arduino_build_xxxxxx`


<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/Change_Interval.png">
</p>


After drag-and-drop the `Change_Interval.ino.hex` into `CURIOSITY` virtual drive, the code will run immidiately if successfully loaded (LED blinks **slowly**)


<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/CURIOSITY_drive.png">
</p>

##### How to connect W5x00 to AVDDx

This is example to demo how to connect W5x00 to Curiosity `AVR128DA48` or `AVR128DB48`

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/Curiosity_Dx48_pinout.png">
</p>

|W5x00|<--->|AVRDx|
|:-:|:-:|:-:|
|MOSI|<--->|PA_4 = 4|
|MISO|<--->|PA_5 = 5|
|SCK|<--->|PA_6 = 6|
|SS|<--->|PA_7 = 7|
|GND|<--->|GND = 52|
|3.3V|<--->|VCC = 51|

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/Curiosity_Dx48_wiring.png">
</p>


---
---

#### Usage

#### Init the CS/SS pin if use EthernetWrapper

```cpp
EthernetInit();
```

#### Class Constructor

```cpp
  EthernetWebServer server(80);
```

Creates the EthernetWebServer class object.

*Parameters:* 
 
host port number: ``int port`` (default is the standard HTTP port 80)

#### Basic Operations

**Starting the server**

```cpp
  void begin();
```

**Handling incoming client requests**

```cpp
  void handleClient();
```

**Disabling the server**

```cpp
  void close();
  void stop();
```

Both methods function the same

**Client request handlers**

```cpp
  void on();
  void addHandler();
  void onNotFound();
  void onFileUpload();	
```

Example:

```cpp
  server.on("/", handlerFunction);
  server.onNotFound(handlerFunction);   // called when handler is not assigned
  server.onFileUpload(handlerFunction); // handle file uploads
```

**Sending responses to the client**

```cpp
  void send();
  void send_P();
```

`Parameters:`

`code` - HTTP response code, can be `200` or `404`, etc.

`content_type` - HTTP content type, like `"text/plain"` or `"image/png"`, etc.

`content` - actual content body

#### Advanced Options

**Getting information about request arguments**

```cpp
  const String & arg();
  const String & argName();
  int args();
  bool hasArg();
```

`Function usage:`

`arg` - get request argument value, use `arg("plain")` to get POST body
	
`argName` - get request argument name
	
`args` - get arguments count
	
`hasArg` - check if argument exist


**Getting information about request headers**

```cpp
  const String & header();
  const String & headerName();
  const String & hostHeader();
  int headers();
  bool hasHeader();
``` 
`Function usage:`

`header` - get request header value

`headerName` - get request header name

`hostHeader` - get request host header if available, else empty string
  
`headers` - get header count
	
`hasHeader` - check if header exist


**Authentication**

```cpp
  bool authenticate();
  void requestAuthentication();
```

`Function usage:`

`authenticate` - server authentication, returns true if client is authenticated else false

`requestAuthentication` - sends authentication failure response to the client

`Example Usage:`

```cpp

  if(!server.authenticate(username, password)){
    server.requestAuthentication();
  }
```

#### Other Function Calls

```cpp
  const String & uri(); // get the current uri
  HTTPMethod  method(); // get the current method 
  WiFiClient client(); // get the current client
  HTTPUpload & upload(); // get the current upload
  void setContentLength(); // set content length
  void sendHeader(); // send HTTP header
  void sendContent(); // send content
  void sendContent_P(); 
  void collectHeaders(); // set the request headers to collect
  void serveStatic();
  size_t streamFile();
```
---
---

### Examples:

#### Original Examples

 1. [AdvancedWebServer](examples/AdvancedWebServer)
 2. [**SimpleWebServer_NativeEthernet**](examples/SimpleWebServer_NativeEthernet)
 3. [HelloServer](examples/HelloServer)
 4. [HelloServer2](examples/HelloServer2)
 5. [HttpBasicAuth](examples/HttpBasicAuth)
 6. [**MQTTClient_Auth**](examples/MQTTClient_Auth)
 7. [**MQTTClient_Basic**](examples/MQTTClient_Basic)
 8. [**MQTT_ThingStream**](examples/MQTT_ThingStream)
 9. [PostServer](examples/PostServer)
10. [SimpleAuthentication](examples/SimpleAuthentication)
11. [UdpNTPClient](examples/UdpNTPClient)
12. [UdpSendReceive](examples/UdpSendReceive)
13. [WebClient](examples/WebClient)
14. [WebClient_ESP](examples/WebClient_ESP)
15. [WebClientRepeating](examples/WebClientRepeating)
16. [WebClientRepeating_ESP](examples/WebClientRepeating_ESP)
17. [WebServer](examples/WebServer)
18. [**WebServer_NativeEthernet**](examples/WebServer_NativeEthernet)
19. [**ESP32_FS_EthernetWebServer**](examples/ESP32_FS_EthernetWebServer).
20. [**FS_EthernetWebServer**](examples/FS_EthernetWebServer).
21. [**serveStatic**](examples/serveStatic).
22. [**serveStaticLoadFile**](examples/serveStaticLoadFile).
23. [**AdvancedWebServer_Ptr**](examples/AdvancedWebServer_Ptr). **New**
24. [**multiFileProject**](examples/multiFileProject). **New**
25. [**EthernetWebServer_BigData**](examples/EthernetWebServer_BigData). **New**



#### HTTP and WebSocket Client New Examples

 1. [BasicAuthGet](examples/HTTPClient/BasicAuthGet)
 2. [CustomHeader](examples/HTTPClient/CustomHeader)
 3. [DweetGet](examples/HTTPClient/DweetGet)
 4. [DweetPost](examples/HTTPClient/DweetPost)
 5. [HueBlink](examples/HTTPClient/HueBlink)
 6. [node_test_server](examples/HTTPClient/node_test_server)
 7. [PostWithHeaders](examples/HTTPClient/PostWithHeaders)
 8. [SimpleDelete](examples/HTTPClient/SimpleDelete)
 9. [SimpleGet](examples/HTTPClient/SimpleGet)
10. [SimpleHTTPExample](examples/HTTPClient/SimpleHTTPExample)
11. [SimplePost](examples/HTTPClient/SimplePost)
12. [SimplePut](examples/HTTPClient/SimplePut)
13. [SimpleWebSocket](examples/HTTPClient/SimpleWebSocket)

#### New Examples for Teensy 4.1 QNEthernet

 1. [AdvancedWebServer](examples/QNEthernet/AdvancedWebServer)
 2. [**MQTTClient_Auth**](examples/QNEthernet/MQTTClient_Auth)
 3. [**MQTTClient_Basic**](examples/QNEthernet/MQTTClient_Basic)
 4. [**MQTT_ThingStream**](examples/QNEthernet/MQTT_ThingStream)

#### New Examples for ESP32 and ESP8266 using with WebServer or ESP8266WebServer

 1. [**WiFi_Ethernet_Complex_ESP32**](examples/WiFi_Ethernet_Complex_ESP32)
 2. [**WiFi_Ethernet_Complex_ESP8266**](examples/WiFi_Ethernet_Complex_ESP8266)
 
#### New Examples for ESP32 using SPI2

 1. [**AdvancedWebServer_ESP32_SPI2**](examples/AdvancedWebServer_ESP32_SPI2) **New**
 
#### New Examples for SPI1/SPI2

 1. [**AdvancedWebServer_RP2040_SPI1**](examples/AdvancedWebServer_RP2040_SPI1) **New** 
 2. [**AdvancedWebServer_Teensy4x_SPI1**](examples/AdvancedWebServer_Teensy4x_SPI1) **New** 
  
---
---

### Example [AdvancedWebServer](examples/AdvancedWebServer)

#### 1. File [AdvancedWebServer.ino](examples/AdvancedWebServer/AdvancedWebServer.ino)

https://github.com/khoih-prog/EthernetWebServer/blob/537e3d08f3b002cb3953ae609ee8c4f94c36a89a/examples/AdvancedWebServer/AdvancedWebServer.ino#L44-L455


---

#### 2. File [defines.h](examples/AdvancedWebServer/defines.h)

https://github.com/khoih-prog/EthernetWebServer/blob/537e3d08f3b002cb3953ae609ee8c4f94c36a89a/examples/AdvancedWebServer/defines.h#L10-L580

---
---

### Debug Terminal Output Samples

#### 1. AdvancedWebServer on NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer.png">
</p>

```
Starting AdvancedWebServer on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
EthernetWebServer v2.3.0
[EWS] =========================
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 11
Connected! IP address: 192.168.2.96
HTTP EthernetWebServer is @ IP : 192.168.2.96
EthernetWebServer::handleClient: New Client
method:  GET
url:  /
search:
headerName: Host
headerValue: 192.168.2.113
headerName: Connection
headerValue: keep-alive
headerName: DNT
headerValue: 1
headerName: Upgrade-Insecure-Requests
headerValue: 1
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: Accept
headerValue: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
args:
args count:  0
args:
args count:  0
Request: /
Arguments: 
Final list of key/value pairs:
EthernetWebServer::_handleRequest handle
EthernetWebServer::send1: len =  347
content =  <html><head><meta http-equiv='refresh' content='5'/><title>NRF52840_FEATHER</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h2>Hello from NRF52840_FEATHER</h2><h3>running EthernetWebServer</h3><p>Uptime: 0 d 00:00:11</p><img src="/test.svg" /></body></html>
EthernetWebServer::_prepareHeader sendHeader Conn close
EthernetWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 347
Connection: close


EthernetWebServer::sendContent: Client.write content:  <html><head><meta http-equiv='refresh' content='5'/><title>AdvancedWebServer NRF52840_FEATHER</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h2>Hi from EthernetWebServer!</h2><h3>on NRF52840_FEATHER</h3><p>Uptime: 0 d 00:00:11</p><img src="/test.svg" /></body></html>
EthernetWebServer::_handleRequest OK
EthernetWebServer::handleClient: Client disconnected
EthernetWebServer::handleClient: Don't keepCurrentClient
EthernetWebServer::handleClient: Client disconnected
EthernetWebServer::handleClient: New Client
method:  GET
url:  /test.svg
search:
headerName: Host
headerValue: 192.168.2.113
headerName: Connection
headerValue: keep-alive
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: DNT
headerValue: 1
headerName: Accept
headerValue: image/webp,image/apng,image/*,*/*;q=0.8
headerName: Referer
headerValue: http://192.168.2.113/
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
args:
args count:  0
args:
args count:  0
Request: /test.svg
Arguments: 
Final list of key/value pairs:
EthernetWebServer::_handleRequest handle
EthernetWebServer::send1: len =  1950
content =  <svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="310" height="150">
<rect width="310" height="150" fill="rgb(250, 230, 210)" stroke-width="3" stroke="rgb(0, 0, 0)" />
<g stroke="blue">
<line x1="10" y1="98" x2="20" y2="111" stroke-width="2" />
<line x1="20" y1="111" x2="30" y2="90" stroke-width="2" />
<line x1="30" y1="90" x2="40" y2="22" stroke-width="2" />
<line x1="40" y1="22" x2="50" y2="98" stroke-width="2" />
<line x1="50" y1="98" x2="60" y2="64" stroke-width="2" />
<line x1="60" y1="64" x2="70" y2="104" stroke-width="2" />
<line x1="70" y1="104" x2="80" y2="31" stroke-width="2" />
<line x1="80" y1="31" x2="90" y2="59" stroke-width="2" />
<line x1="90" y1="59" x2="100" y2="139" stroke-width="2" />
<line x1="100" y1="139" x2="110" y2="117" stroke-width="2" />
<line x1="110" y1="117" x2="120" y2="75" stroke-width="2" />
<line x1="120" y1="75" x2="130" y2="72" stroke-width="2" />
<line x1="130" y1="72" x2="140" y2="137" stroke-width="2" />
<line x1="140" y1="137" x2="150" y2="20" stroke-width="2" />
<line x1="150" y1="20" x2="160" y2="94" stroke-width="2" />
<line x1="160" y1="94" x2="170" y2="81" stroke-width="2" />
<line x1="170" y1="81" x2="180" y2="38" stroke-width="2" />
<line x1="180" y1="38" x2="190" y2="33" stroke-width="2" />
<line x1="190" y1="33" x2="200" y2="53" stroke-width="2" />
<line x1="200" y1="53" x2="210" y2="88" stroke-width="2" />
<line x1="210" y1="88" x2="220" y2="32" stroke-width="2" />
<line x1="220" y1="32" x2="230" y2="110" stroke-width="2" />
<line x1="230" y1="110" x2="240" y2="87" stroke-width="2" />
<line x1="240" y1="87" x2="250" y2="11" stroke-width="2" />
<line x1="250" y1="11" x2="260" y2="98" stroke-width="2" />
<line x1="260" y1="98" x2="270" y2="76" stroke-width="2" />
<line x1="270" y1="76" x2="280" y2="121" stroke-width="2" />
<line x1="280" y1="121" x2="290" y2="139" stroke-width="2" />
<line x1="290" y1="139" x2="300" y2="103" stroke-width="2" />
</g>
</svg>

EthernetWebServer::_prepareHeader sendHeader Conn close
EthernetWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: image/svg+xml
Content-Length: 1950
Connection: close
```

---

#### 2. ENC28J60_WM_Config on ESP32 with ENC28J60 using UIPEthernet Library

The terminal output of ESP32 running a [ENC28J60_WM_Config example](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/ENC28J60_WM_Config) of [BlynkEthernet_WM Library](https://github.com/khoih-prog/BlynkEthernet_WM)

```cpp
Start ENC28J60_WM_Config on ESP32
[38] EEPROMsz:1024
[38] CCSum=0x29f2,RCSum=0x29f2
[38] CrCCsum=0,CrRCsum=0
[38] Hdr=ENC28J60,BName=ESP32-ENC28J60-WM
[38] Svr=account.duckdns.org,Tok=token
[45] Svr1=account.ddns.net,Tok1=token1
[51] Prt=8080,SIP=blank
[53] MAC:FE-80-D6-B4-FC-EE
ENC28J60_CONTROL_CS =13
SS =5
SPI_MOSI =23
SPI_MISO =19
SPI_SCK =18
[5332] IP:192.168.2.103
[5332] bg:ECon.TryB
[5332] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on ESP32

[5343] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[6454] Ready (ping: 37ms).
[6522] Connected to Blynk Server = account.duckdns.org, Token = token
[6522] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token, IP = 192.168.2.103
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
```


---

#### 3. SimpleWebSocket on SAM DUE with W5x00 using Ethernet_Generic Library

The terminal output of **SAM DUE with W5x00 using Ethernet_Generic Library** running [SimpleWebSocket example](examples/HTTPClient/SimpleWebSocket) to demonstrate newly-added WebSocket Client feature.


```
Starting SimpleWebSocket on SAM DUE with W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 75
[EWS] MISO: 74
[EWS] SCK: 76
[EWS] SS: 10
[EWS] =========================
[EWS] Board : SAM DUE , setCsPin: 10
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
=========================
Currently Used SPI pinout:
MOSI:75
MISO:74
SCK:76
SS:10
=========================
Using mac index = 5
Connected! IP address: 192.168.2.81
starting WebSocket client
Connection failed
disconnected
starting WebSocket client
Connected
Sending Hello 0
Sending Hello 1
Received a message:
0 => Hello from SimpleWebSocket on SAM DUE, millis = 6906
Sending Hello 2
Received a message:
1 => Hello from SimpleWebSocket on SAM DUE, millis = 11907
Sending Hello 3
Received a message:
2 => Hello from SimpleWebSocket on SAM DUE, millis = 16909
Sending Hello 4
Received a message:
3 => Hello from SimpleWebSocket on SAM DUE, millis = 21911
Sending Hello 5
Received a message:
4 => Hello from SimpleWebSocket on SAM DUE, millis = 26913
Sending Hello 6
Received a message:
5 => Hello from SimpleWebSocket on SAM DUE, millis = 31915
Sending Hello 7
Received a message:
6 => Hello from SimpleWebSocket on SAM DUE, millis = 36917
Sending Hello 8
Received a message:
7 => Hello from SimpleWebSocket on SAM DUE, millis = 41919
Sending Hello 9
Received a message:
8 => Hello from SimpleWebSocket on SAM DUE, millis = 46921
Sending Hello 10
Received a message:
9 => Hello from SimpleWebSocket on SAM DUE, millis = 51923
Sending Hello 11
Received a message:
10 => Hello from SimpleWebSocket on SAM DUE, millis = 56925
Sending Hello 12
Received a message:
11 => Hello from SimpleWebSocket on SAM DUE, millis = 61927
Sending Hello 13
Received a message:
12 => Hello from SimpleWebSocket on SAM DUE, millis = 66929
Sending Hello 14
Received a message:
13 => Hello from SimpleWebSocket on SAM DUE, millis = 71931
Sending Hello 15
Received a message:
14 => Hello from SimpleWebSocket on SAM DUE, millis = 76933
Sending Hello 16
Received a message:
15 => Hello from SimpleWebSocket on SAM DUE, millis = 81935
Sending Hello 17
Received a message:
16 => Hello from SimpleWebSocket on SAM DUE, millis = 86937
Sending Hello 18
Received a message:
17 => Hello from SimpleWebSocket on SAM DUE, millis = 91939
```

---

#### 4. DweetPost on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library

The terminal output of **NRF52840_FEATHER with W5x00 using Ethernet_Generic Library** running [DweetPost example](examples/HTTPClient/DweetPost) to demonstrate newly-added high-level HTTP Client feature.

```
Starting DweetPost on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
SPI_CS:10
=========================
Using mac index = 17
Connected! IP address: 192.168.2.80
making POST request
Status code: 200
Response: {"this":"succeeded","by":"dweeting","the":"dweet","with":{"thing":"scandalous-cheese-hoarder","created":"2020-11-17T05:10:59.175Z","content":{"sensorValue":40},"transaction":"08ae7c04-f1e5-4411-ad05-eb4afe77a6b4"}}
Wait ten seconds
```

---

#### 5. ESP32_FS_EthernetWebServer on ESP32 using LittleFS with W5x00 using Ethernet_Generic Library

The terminal output of **ESP32 with W5x00 using Ethernet_Generic Library** running [ESP32_FS_EthernetWebServer example](examples/HTTPClient/FS_EthernetWebServer) to demonstrate newly-added WebServer serving from LittleFS/SPIFFS

```
Starting ESP32_FS_EthernetWebServer on ESP32 using LittleFS
With W5x00 using Ethernet_Generic Library on SPI
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 23
[EWS] MISO: 19
[EWS] SCK: 18
[EWS] SS: 5
[EWS] =========================
[EWS] ESP32 setCsPin: 5
=========================
Currently Used SPI pinout:
MOSI:23
MISO:19
SCK:18
SS:5
=========================
Connected! IP address: 192.168.2.139
FS File: /CanadaFlag_1.png, size: 40.25KB
FS File: /CanadaFlag_2.png, size: 8.12KB
FS File: /CanadaFlag_3.jpg, size: 10.89KB
FS File: /edit.htm.gz, size: 4.02KB
FS File: /favicon.ico, size: 1.12KB
FS File: /graphs.js.gz, size: 1.92KB
FS File: /index.htm, size: 3.63KB

HTTP server started @192.168.2.139
Open http://192.168.2.139/edit to see the file browser
handleFileRead: /edit.htm
handleFileRead: /index.htm
handleFileRead: /favicon.ico
```

and the screen shot of the WebServer

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/ESP32_FS_EthernetWebServer.png">
</p>

---


#### 6. FS_EthernetWebServer on ESP8266 using LittleFS with W5x00 using Ethernet_Generic Library

The terminal output of **ESP8266 with W5x00 using Ethernet_Generic Library** running [FS_EthernetWebServer example](examples/HTTPClient/FS_EthernetWebServer) to demonstrate newly-added WebServer serving from LittleFS/SPIFFS

```
Starting FS_EthernetWebServer on ESP8266 using LittleFS
With W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 13
[EWS] MISO: 12
[EWS] SCK: 14
[EWS] SS: 15
[EWS] =========================
[EWS] ESP8266 setCsPin: 4
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:15
=========================
Connected! IP address: 192.168.2.139
Opening / directory
FS File: CanadaFlag_1.png, size: 40.25KB
FS File: CanadaFlag_2.png, size: 8.12KB
FS File: CanadaFlag_3.jpg, size: 10.89KB
FS File: edit.htm.gz, size: 4.02KB
FS File: favicon.ico, size: 1.12KB
FS File: graphs.js.gz, size: 1.92KB
FS File: index.htm, size: 3.63KB
FS File: page1.html, size: 1.16KB
FS File: page1.htm, size: 1.16KB
FS File: page2.html, size: 1.16KB
FS File: page3.html, size: 1.16KB


HTTP server started @192.168.2.139
Open http://192.168.2.139/edit to see the file browser
handleFileRead: /edit.htm
handleFileRead: /index.htm
handleFileRead: /favicon.ico
```

and the screen shot of the WebServer

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/FS_EthernetWebServer.png">
</p>

---

#### 7. serveStatic on ESP8266 using LittleFS with W5x00 using Ethernet_Generic Library

The terminal output of **ESP8266 with W5x00 using Ethernet_Generic Library** running [serveStatic example](examples/HTTPClient/serveStatic) to demonstrate newly-added WebServer serving from LittleFS/SPIFFS

```
Starting serveStatic demoing 'serveStatic' function on ESP8266 using LittleFS
With W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 13
[EWS] MISO: 12
[EWS] SCK: 14
[EWS] SS: 15
[EWS] =========================
[EWS] ESP8266 setCsPin: 4
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:15
=========================
Connected! IP address: 192.168.2.133
HTTP server started
```

and the screen shot of the WebServer

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/serveStatic.png">
</p>

---

#### 8. SimpleWebServer_NativeEthernet on Teensy 4.1 with NativeEthernet library


The following are debug terminal output and screen shot when running example [SimpleWebServer_NativeEthernet](examples/SimpleWebServer_NativeEthernet) on **Teensy 4.1 with NativeEthernet library**

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/SimpleWebServer_NativeEthernet.png">
</p>


```
SimpleWebServer_NativeEthernet on Teensy 4.1 with NativeEthernet
EthernetWebServer v2.3.0
Debug Level = 3
Connected! IP address: 192.168.2.127
[EWS] <html><head><meta http-equiv='refresh' content='5'/><title>AdvancedWebServer Teensy 4.1 with NativeEthernet</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h2>Hi from EthernetWebServer!</h2><h3>on Teensy 4.1 with NativeEthernet</h3><p>Uptime: 0 d 00:00:05</p></body></html>
========================================
[EWS] <svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="310" height="150">
<rect width="310" height="150" fill="rgb(250, 230, 210)" stroke-width="1" stroke="rgb(0, 0, 0)" />
<g stroke="black">
<line x1="10" y1="77" x2="20" y2="67" stroke-width="1" />
<line x1="20" y1="67" x2="30" y2="98" stroke-width="1" />
<line x1="30" y1="98" x2="40" y2="111" stroke-width="1" />
<line x1="40" y1="111" x2="50" y2="90" stroke-width="1" />
<line x1="50" y1="90" x2="60" y2="22" stroke-width="1" />
<line x1="60" y1="22" x2="70" y2="98" stroke-width="1" />
<line x1="70" y1="98" x2="80" y2="64" stroke-width="1" />
<line x1="80" y1="64" x2="90" y2="104" stroke-width="1" />
<line x1="90" y1="104" x2="100" y2="31" stroke-width="1" />
<line x1="100" y1="31" x2="110" y2="59" stroke-width="1" />
<line x1="110" y1="59" x2="120" y2="139" stroke-width="1" />
<line x1="120" y1="139" x2="130" y2="117" stroke-width="1" />
<line x1="130" y1="117" x2="140" y2="75" stroke-width="1" />
<line x1="140" y1="75" x2="150" y2="72" stroke-width="1" />
<line x1="150" y1="72" x2="160" y2="137" stroke-width="1" />
<line x1="160" y1="137" x2="170" y2="20" stroke-width="1" />
<line x1="170" y1="20" x2="180" y2="94" stroke-width="1" />
<line x1="180" y1="94" x2="190" y2="81" stroke-width="1" />
<line x1="190" y1="81" x2="200" y2="38" stroke-width="1" />
<line x1="200" y1="38" x2="210" y2="33" stroke-width="1" />
<line x1="210" y1="33" x2="220" y2="53" stroke-width="1" />
<line x1="220" y1="53" x2="230" y2="88" stroke-width="1" />
<line x1="230" y1="88" x2="240" y2="32" stroke-width="1" />
<line x1="240" y1="32" x2="250" y2="110" stroke-width="1" />
<line x1="250" y1="110" x2="260" y2="87" stroke-width="1" />
<line x1="260" y1="87" x2="270" y2="11" stroke-width="1" />
<line x1="270" y1="11" x2="280" y2="98" stroke-width="1" />
<line x1="280" y1="98" x2="290" y2="76" stroke-width="1" />
<line x1="290" y1="76" x2="300" y2="121" stroke-width="1" />
</g>
</svg>

========================================
```

---


#### 9. AdvancedWebServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on **RASPBERRY_PI_PICO** with W5x00 using Ethernet_Generic Library and [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_Mbed_RPi_Pico.png">
</p>

```
Starting AdvancedWebServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 19
Connected! IP address: 192.168.2.95
HTTP EthernetWebServer is @ IP : 192.168.2.95
.[EWS] String Len = 0, extend to 2048
..
```

---

#### 10. MQTTClient_Auth on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The following are debug terminal output when running example [MQTTClient_Auth](examples/MQTTClient_Auth) on **RASPBERRY_PI_PICO** with W5x00 using Ethernet_Generic Library and [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)


```
Start MQTTClient_Auth on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 10
Connected! IP address: 192.168.2.94
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
```

---

#### 11. AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on **RASPBERRY_PI_PICO** with W5x00 using Ethernet_Generic Library and [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico)

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_RPi_Pico.png">
</p>

```
Starting AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 7
Connected! IP address: 192.168.2.117
HTTP EthernetWebServer is @ IP : 192.168.2.117
.......... .......... .......... .......... .......... ..
```

---

#### 12. UdpNTPClient on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The following are debug terminal output and screen shot when running example [UdpNTPClient](examples/UdpNTPClient) on **RASPBERRY_PI_PICO** with W5x00 using Ethernet_Generic Library and [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico)


```
Start UdpNTPClient on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 18
You're connected to the network, IP = 192.168.2.106
UDP Packet received, size 48
From 128.138.140.44, port 123
Seconds since Jan 1 1900 = 3830118654
Unix time = 1621129854
The UTC time is 1:50:54
UDP Packet received, size 48
From 128.138.140.44, port 123
Seconds since Jan 1 1900 = 3830118666
Unix time = 1621129866
The UTC time is 1:51:06
```

---

#### 13. AdvancedWebServer on Teensy 4.1 using NativeEthernet Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/QNEthernet/AdvancedWebServer) on **Teensy 4.1** using NativeEthernet Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_NativeEthernet.png">
</p>

```
Starting AdvancedWebServer on TEENSY 4.1 using QNEthernet
EthernetWebServer v2.3.0
[EWS] =========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => IP Address = 192.168.2.222
HTTP EthernetWebServer is @ IP : 192.168.2.222
.[EWS] String Len = 0, extend to 2048
..........
```


---


#### 14. AdvancedWebServer on Teensy 4.1 using QNEthernet Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/QNEthernet/AdvancedWebServer) on **Teensy 4.1** using QNEthernet Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_QNEthernet.png">
</p>

```
Starting AdvancedWebServer on TEENSY 4.1 using QNEthernet
EthernetWebServer v2.3.0
[EWS] =========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => IP Address = 192.168.2.222
HTTP EthernetWebServer is @ IP : 192.168.2.222
.[EWS] String Len = 0, extend to 2048
......... .......... .......... .......... .......... .......... .......... ..........
.......... .......... ......
```

---

#### 15. MQTTClient_Auth on TEENSY 4.1 using QNEthernet Library

The following is the debug terminal output when running example [MQTTClient_Auth](examples/QNEthernet/MQTTClient_Auth) on **Teensy 4.1** using QNEthernet Library


```
Start MQTTClient_Auth on TEENSY 4.1 using QNEthernet
EthernetWebServer v2.3.0
[EWS] =========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => IP Address = 192.168.2.222
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on TEENSY 4.1 using QNEthernet
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on TEENSY 4.1 using QNEthernet
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on TEENSY 4.1 using QNEthernet
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on TEENSY 4.1 using QNEthernet
```


---

#### 16. AdvancedWebServer on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on **PORTENTA_H7_M7** with Ethernet using Portenta_Ethernet Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_Portenta_H7.png">
</p>

```
Starting AdvancedWebServer on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
EthernetWebServer v2.3.0
[EWS] ======== USE_PORTENTA_H7_ETHERNET ========
Using mac index = 6
Connected! IP address: 192.168.2.222
HTTP EthernetWebServer is @ IP : 192.168.2.222
.[EWS] String Len = 0, extend to 2048
.......... .......... .......... .......... .......... ..
```

---

#### 17. SimpleWebSocket on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library

The following is the debug terminal output when running example [MQTTClient_Auth](examples/SimpleWebSocket) on **PORTENTA_H7_M7** with Ethernet using Portenta_Ethernet Library

##### 17.1 Client

```
Starting SimpleWebSocket on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
EthernetWebServer v2.3.0
[EWS] ======== USE_PORTENTA_H7_ETHERNET ========
Using mac index = 4
Connected! IP address: 192.168.2.132
starting WebSocket client
Sending Hello 0
Sending Hello 1
Received a message:
0 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 5022
Sending Hello 2
Received a message:
1 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 10075
Sending Hello 3
Received a message:
2 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 15132
Sending Hello 4
Received a message:
3 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 20145
Sending Hello 5
Received a message:
4 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 25152
```

##### 17.2 Server

```
kh@kh-Inspiron-3593:~/Downloads/Nodejs/simple-websocket-server$ ./WS_server.sh 
Wed Sep 08 2021 21:30:46 GMT-0400 (Eastern Daylight Time) Server is listening on port 8080
Wed Sep 08 2021 21:31:08 GMT-0400 (Eastern Daylight Time) Connection accepted.
Received Message: 0 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 5022
Received Message: 1 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 10075
Received Message: 2 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 15132
Received Message: 3 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 20145
Received Message: 4 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 25152
Received Message: 5 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 30248
Received Message: 6 => Hello from SimpleWebSocket on PORTENTA_H7_M7, millis = 35256
```

---


#### 18. MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library

The following is the debug terminal output when running example [MQTTClient_Auth](examples/MQTTClient_Auth) on **PORTENTA_H7_M7** with Ethernet using Portenta_Ethernet Library


```
Start MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
EthernetWebServer v2.3.0
[EWS] ======== USE_PORTENTA_H7_ETHERNET ========
Using mac index = 7
Connected! IP address: 192.168.2.132
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
```

---


#### 19. WiFi_Ethernet_Complex_ESP32 on ESP32_DEV

The following are debug terminal output when running example [WiFi_Ethernet_Complex_ESP32](examples/WiFi_Ethernet_Complex_ESP32) on **ESP32_DEV** using both EthernetWebServer and WebServer Library simultaneously.


```
Starting WiFi_Ethernet_Complex_ESP32 on ESP32_DEV
Connecting to HueNet1
.......
WiFi connected
IP address: 
192.168.2.105
[EWS] ESP32 setCsPin: 22
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 22, new ss_pin = 10, W5100Class::ss_pin = 22
W5100::init: W5500, SSIZE =8192
HTTP EthernetWebServer is @ IP : 192.168.2.114
HTTP WiFiWebServer is @ IP : 192.168.2.105
```

---


#### 20. WiFi_Ethernet_Complex_ESP8266 on ESP8266_NODEMCU_ESP12E

The following are debug terminal output when running example [WiFi_Ethernet_Complex_ESP8266](examples/WiFi_Ethernet_Complex_ESP8266) on **ESP8266_NODEMCU_ESP12E** using both EthernetWebServer and WebServer Library simultaneously.


```
Starting WiFi_Ethernet_Complex_ESP8266 on ESP8266_NODEMCU_ESP12E
Connecting to HueNet1
...........
WiFi connected
IP address: 
192.168.2.109
[EWS] ESP8266 setCsPin: 4
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:15
HTTP EthernetWebServer is @ IP : 192.168.2.111
HTTP WiFiWebServer is @ IP : 192.168.2.109
```

---

#### 21. AdvancedWebServer_ESP32_SPI2 on ESP32_DEV with W5x00 using Ethernet_Generic Library on SPI2

The following are debug terminal output and screen shot when running example [AdvancedWebServer_ESP32_SPI2](examples/AdvancedWebServer_ESP32_SPI2) on ESP32_DEV with W5500 using Ethernet_Generic Library on SPI2

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_ESP32_SPI2.png">
</p>

```
Starting AdvancedWebServer_ESP32_SPI2 on ESP32_DEV with W5x00 using Ethernet_Generic Library on SPI2
EthernetWebServer v2.3.0
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:5
=========================
Using mac index = 0
Connected! IP address: 192.168.2.102
Speed: 100 MB, Duplex: FULL DUPLEX, Link status: LINK
HTTP EthernetWebServer is @ IP : 192.168.2.102
.
[EWS] String Len = 0, extend to 2048
```

---

#### 22. AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI1

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on RASPBERRY_PI_PICO with W5500 using Ethernet_Generic Library on SPI1 and [arduino-pico core](https://github.com/earlephilhower/arduino-pico)

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_RPi_Pico_SPI1.png">
</p>


```
Starting AdvancedWebServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI1
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 15
[EWS] MISO: 12
[EWS] SCK: 14
[EWS] SS: 13
[EWS] =========================
[EWS] RPIPICO setCsPin: 13
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 15
[EWS] MISO: 12
[EWS] SCK: 14
[EWS] SS: 13
[EWS] =========================
Using mac index = 13
Connected! IP address: 192.168.2.104
HTTP EthernetWebServer is @ IP : 192.168.2.104
.[EWS] String Len = 0, extend to 2048
......... .......... ..........
```


---

#### 23. AdvancedWebServer_RP2040_SPI1 on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI1

The following are debug terminal output and screen shot when running example [AdvancedWebServer_RP2040_SPI1](examples/AdvancedWebServer_RP2040_SPI1) on **MBED RASPBERRY_PI_PICO** with W5500 using Ethernet_Generic Library on `SPI1` and [ArduinoCore-mbed](https://github.com/arduino/ArduinoCore-mbed)

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_Mbed_RPi_Pico_SPI1.png">
</p>


```
Starting AdvancedWebServer_RP2040_SPI1 on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library with Large Buffer
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 15
[EWS] MISO: 12
[EWS] SCK: 14
[EWS] SS: 13
[EWS] =========================
[EWS] RPIPICO setCsPin: 13
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 15
[EWS] MISO: 12
[EWS] SCK: 14
[EWS] SS: 13
[EWS] =========================
Using mac index = 6
Connected! IP address: 192.168.2.97
HTTP EthernetWebServer is @ IP : 192.168.2.97
...
```

---

#### 24. AdvancedWebServer_Teensy4x_SPI1 on TEENSY 4.1 with W5x00 using Ethernet_Generic Library on SPI1

The following are debug terminal output and screen shot when running example [AdvancedWebServer_Teensy4x_SPI1](examples/AdvancedWebServer_Teensy4x_SPI1) on **Teensy 4.1** with W5500 using Ethernet_Generic Library on SPI1

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_Teensy41_SPI1.png">
</p>

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/Teensy41_pinout.png">
</p>

```
Starting AdvancedWebServer_Teensy4x_SPI1 on TEENSY 4.1 with W5x00 using Ethernet_Generic Library with Large Buffer
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 26
[EWS] MISO: 1
[EWS] SCK: 27
[EWS] SS: 0
[EWS] =========================
[EWS] Board : TEENSY 4.1 , setCsPin: 0
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 26
[EWS] MISO: 1
[EWS] SCK: 27
[EWS] SS: 0
[EWS] =========================
Using mac index = 15
Connected! IP address: 192.168.2.101
HTTP EthernetWebServer is @ IP : 192.168.2.101
.[EWS] String Len = 0, extend to 2048
......... .......... ..........
```


---

#### 25. AdvancedWebServer on Curiosity AVR_AVR128DA48 with W5x00 using Ethernet_Generic Library on SPI

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on **Curiosity AVR_AVR128DA48** with W5500 using Ethernet_Generic Library on SPI

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer/raw/master/pics/AdvancedWebServer_AVRDx.png">
</p>


```
Starting AdvancedWebServer on Curiosity AVR_AVR128DA48 with W5x00 using Ethernet_Generic Library on SPI0/SPI
EthernetWebServer v2.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 4
[EWS] MISO: 5
[EWS] SCK: 6
[EWS] SS: 7
[EWS] =========================
[EWS] Board : Curiosity AVR_AVR128DA48 , setCsPin: 7
[ETG] W5100 init, using W5100Class::ss_pin =  7 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 4
[EWS] MISO: 5
[EWS] SCK: 6
[EWS] SS: 7
[EWS] =========================
Using mac index = 6
Connected! IP address: 192.168.2.105
HTTP EthernetWebServer is @ IP : 192.168.2.105
..[EWS] String Len = 0, extend to 2048
........ .......... .......... .......... ...
```


---

#### 26. [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on NRF52840_FEATHER

The following is debug terminal output when running example [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on `NRF52840_FEATHER` board, using W5500 Ethernet with [Ethernet_Generic Library](https://github.com/khoih-prog/Ethernet_Generic), to demo how to send much larger data than total 8K

##### MULTIPLY_FACTOR = 3.0f

```
Start EthernetWebServer_BigData on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library on SPI0/SPI
EthernetWebServer v2.3.0
[ETG] W5100 init, using W5100Class::ss_pin =  5 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
Using mac index = 14
Connected! IP address: 192.168.2.135
String Len = 23712
[ETG] EthernetClient::write: To write, size =  86
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: To write, size =  23712
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 15520
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 7328
[ETG] EthernetClient::write: written =  7328 , totalBytesSent = 23712
[ETG] EthernetClient::write: Done, written =  7328 , totalBytesSent = 23712
[ETG] EthernetClient::write: To write, size =  91
[ETG] EthernetClient::write: written =  91 , totalBytesSent = 91
[ETG] EthernetClient::write: Done, written =  91 , totalBytesSent = 91
[ETG] EthernetClient::write: To write, size =  59
[ETG] EthernetClient::write: written =  59 , totalBytesSent = 59
[ETG] EthernetClient::write: Done, written =  59 , totalBytesSent = 59
String Len = 23712
[ETG] EthernetClient::write: To write, size =  86
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: To write, size =  23712
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 15520
[ETG] EthernetClient::write: written =  8192 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  8192 , bytesRemaining = 7328
[ETG] EthernetClient::write: written =  7328 , totalBytesSent = 23712
[ETG] EthernetClient::write: Done, written =  7328 , totalBytesSent = 23712
```

---

#### 27. [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on RASPBERRY_PI_PICO

The following is debug terminal output when running example [EthernetWebServer_BigData](examples/EthernetWebServer_BigData) on `RASPBERRY_PI_PICO` board, using W5500 Ethernet with [Ethernet_Generic Library](https://github.com/khoih-prog/Ethernet_Generic), to demo how to send much larger data than total 8K

##### MULTIPLY_FACTOR = 3.0f


```
Start EthernetWebServer_BigData on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI0/SPI
EthernetWebServer v2.3.0
[ETG] W5100 init, using W5100Class::ss_pin =  17 , whereas new ss_pin =  10 , SS_PIN_DEFAULT = 17
[ETG] Chip is W5100S
[ETG] W5100::init: W5100S, SSIZE = 4096
Using mac index = 7
Connected! IP address: 192.168.2.111
String Len = 23714
[ETG] EthernetClient::write: To write, size =  86
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: To write, size =  23714
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 4096
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 19618
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 15522
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 12288
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 11426
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 7330
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 20480
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 3234
[ETG] EthernetClient::write: written =  3234 , totalBytesSent = 23714
[ETG] EthernetClient::write: Done, written =  3234 , totalBytesSent = 23714
String Len = 23714
[ETG] EthernetClient::write: To write, size =  86
[ETG] EthernetClient::write: written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: Done, written =  86 , totalBytesSent = 86
[ETG] EthernetClient::write: To write, size =  23714
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 4096
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 19618
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 8192
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 15522
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 12288
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 11426
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 16384
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 7330
[ETG] EthernetClient::write: written =  4096 , totalBytesSent = 20480
[ETG] EthernetClient::write: Partially Done, written =  4096 , bytesRemaining = 3234
[ETG] EthernetClient::write: written =  3234 , totalBytesSent = 23714
[ETG] EthernetClient::write: Done, written =  3234 , totalBytesSent = 23714
```


---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _ETHERNET_WEBSERVER_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to Serial
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial
// Use this to disable all output debug msgs
// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Libraries' Patches, Packages' Patches or this library latest version.

---
---

### Issues ###

Submit issues to: [EthernetWebServer issues](https://github.com/khoih-prog/EthernetWebServer/issues)

---

### TO DO

1. Bug Searching and Killing
2. Add Server support
3. Support more types of boards using Ethernet shields.
4. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia
5. Add mDNS features.

### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 4. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**.
 5. Add support to SAM DUE.
 6. Add support to Ethernet W5x00, using either [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`Ethernet2`](https://github.com/adafruit/Ethernet2), [`Ethernet3`](https://github.com/sstaub/Ethernet3) or [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) library
 7. Add support to Ethernet ENC28J60, using [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
 8. Add support to ESP32 and ESP8266
 9. Add support to Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless
10. Add support to [`EthernetENC`](https://github.com/jandrassy/EthernetENC)
11. Add support to PROGMEM-related commands, such as sendContent_P() and send_P()
12. Add **High-level HTTP (GET, POST, PUT, PATCH, DELETE) and WebSocket Client**
13. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
14. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Earle Philhower's arduino-pico** core v1.3.1+](https://github.com/earlephilhower/arduino-pico)
15. Add support to Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
16. Add support to Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
17. Add support to **Portenta_H7 boards**, using [**Arduino-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed).
18. Reduce usage of Arduino String with std::string
19. Optimize library code and examples by using **reference-passing instead of value-passing**.
20. Make **breaking** changes in v2.0.0 to permit coexistence with `ESP32 WebServer` and `ESP8266 ESP8266WebServer` libraries
21. Add support to SAMD21/SAMD51 boards using [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
22. Fix bug when using `QNEthernet` staticIP. 
23. Add staticIP option to `NativeEthernet` examples
24. Use new [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
25. Support **SPI2 for ESP32**
26. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
27. Drop `EthernetWrapper`
28. Add example [multiFileProject](examples/multiFileProject) to demo how to avoid `multiple-definitions` linker error for multiple-file project
29. Change from `arduino.cc` to `arduino.tips` in examples
30. Add support to SPI1, SPI2 for Teensy using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
31. Add support to custom SPI for Mbed RP2040, Portenta-H7, etc. using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
32. Add examples [AdvancedWebServer_Teensy4x_SPI1](examples/AdvancedWebServer_Teensy4x_SPI1) and [AdvancedWebServer_RP2040_SPI1](examples/AdvancedWebServer_RP2040_SPI1) to demo new features
33. Auto-select SPI(s) `SS/CS` pins according to board package if available
34. Slow SPI clock for old W5100 shield or SAMD Zero
35. Use correct Debug Terminal `Serial` for so-called **SAMD21 Zero** boards from Arduino as well as Adafruit
36. Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using [DxCore](https://github.com/SpenceKonde/DxCore)
37. Add support to Seeeduino nRF52840-based boards such as **SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**, etc. using Seeed `mbed` or `nRF52` core
38. Add astyle using `allman` style. Restyle the library
39. Update `Packages' Patches` to add Seeeduino `nRF52` core
40. Add examples [EthernetWebServer_BigData](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/EthernetWebServer_BigData) to demo how to send larger data than **2/4/8/16K** buffer
41. Modify example [AdvancedWebServer](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/AdvancedWebServer) to demo how to send larger data than `2/4/8/16K` buffer



---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Based on and modified from the good [Ivan Grokhotkov's ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer) and [ESP32 WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer) libraries.
2. [jandrassy](https://github.com/jandrassy) for [EthernetENC](https://github.com/jandrassy/EthernetENC) and [UIPEthernet library](https://github.com/UIPEthernet/UIPEthernet)
3. Thanks to good work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially **U-Blox B302 running as nRF52840 and U-Blox B112 running as nRF52832**, has never been started and finished. Also see [ESP32-based U-BLOX NINA W102 running ENC28J60](https://u-blox-ethernet-ninaw.blogspot.com/).
4. Thanks to [Vladimir](https://github.com/workpage2) to initiate the work on ESP32 and ESP8266 in [Spiffs not work Issue #2](https://github.com/khoih-prog/EthernetWebServer/issues/2)
5. [Adrian McEwen](https://github.com/amcewen) for [HttpClient Library](https://github.com/amcewen/HttpClient) on which the [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient) and this [EthernetWebServer library](https://github.com/khoih-prog/EthernetWebServer) are relied.
6. Thanks to [jimmie11](https://github.com/jimmie11) to report and suggest a fix in [Compile Error on Teensy 4.1 #14](https://github.com/khoih-prog/EthernetWebServer/issues/14) leading to the new version v1.2.0 to provide support to **Teensy 4.1** using [**NativeEthernet Library**](https://github.com/vjmuzik/NativeEthernet)
7. Thanks to [Sardar Azari](https://github.com/gagulik) to make PR in [streamFile and serveStatic for ESP8266/ESP32 boards #22](https://github.com/khoih-prog/EthernetWebServer/pull/22) leading to the new version v1.3.0 to add WebServer feature to serve static from LittleFS/SPIFFS for ESP32/ESP8266. The example [**serveStatic**](examples/serveStatic) and [**serveStaticLoadFile**](examples/serveStaticLoadFile) are also contributed by [Sardar Azari](https://github.com/gagulik).
8. Thanks to [neardreams](https://github.com/neardreams) to report issue [Something wrong in http response header #41](https://github.com/khoih-prog/EthernetWebServer/issues/41), then make PR in [fix for wrong http status header #42](https://github.com/khoih-prog/EthernetWebServer/pull/42) leading to the new version v1.8.2 to fix wrong http status header bug.
9. Thanks to [dirkdickler](https://github.com/dirkdickler) to report issue [server.authenticate problem #43](https://github.com/khoih-prog/EthernetWebServer/issues/43) which was fixed in v1.8.2
10. Thanks to [Shahram](https://github.com/Nourbakhsh-Rad) to report issues
- [multiple definition of base64 error with ver. 1.8.3 #44](https://github.com/khoih-prog/EthernetWebServer/issues/44) leading to v1.8.4
- [Missing ESP definitions ..... #45](https://github.com/khoih-prog/EthernetWebServer/issues/45) leading to v1.8.6
11. [RQnet](https://github.com/RQnet) to report issue [Decoding Error. two times called urlDecode in Parsing-impl.h. #17](https://github.com/khoih-prog/WiFiWebServer/issues/17) leading to version v2.0.1 to fix the decoding error bug when using special `&` in data fields.

<table>
  <tr>
    <td align="center"><a href="https://github.com/igrr"><img src="https://github.com/igrr.png" width="100px;" alt="igrr"/><br /><sub><b>⭐️ Ivan Grokhotkov</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/amcewen"><img src="https://github.com/amcewen.png" width="100px;" alt="amcewen"/><br /><sub><b>⭐️ Adrian McEwen</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/jandrassy"><img src="https://github.com/jandrassy.png" width="100px;" alt="jandrassy"/><br /><sub><b>⭐️ Juraj Andrássy</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Vladimir"><img src="https://github.com/Vladimir.png" width="100px;" alt="Vladimir"/><br /><sub><b>Vladimir</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/jimmie11"><img src="https://github.com/jimmie11.png" width="100px;" alt="jimmie11"/><br /><sub><b>jimmie11</b></sub></a><br /></td>
  </tr> 
  <tr>
    <td align="center"><a href="https://github.com/gagulik"><img src="https://github.com/gagulik.png" width="100px;" alt="gagulik"/><br /><sub><b>
Sardar Azari</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/neardreams"><img src="https://github.com/neardreams.png" width="100px;" alt="neardreams"/><br /><sub><b>neardreams</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/dirkdickler"><img src="https://github.com/dirkdickler.png" width="100px;" alt="dirkdickler"/><br /><sub><b>dirkdickler</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Nourbakhsh-Rad"><img src="https://github.com/Nourbakhsh-Rad.png" width="100px;" alt="Nourbakhsh-Rad"/><br /><sub><b>Shahram</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/RQnet"><img src="https://github.com/RQnet.png" width="100px;" alt="RQnet"/><br /><sub><b>RQnet</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/EthernetWebServer/blob/master/LICENSE)

---

## Copyright

Copyright (C) 2020- Khoi Hoang


