## EthernetWebServer

[![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/EthernetWebServer.svg)](https://github.com/khoih-prog/EthernetWebServer/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/EthernetWebServer/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/EthernetWebServer.svg)](http://github.com/khoih-prog/EthernetWebServer/issues)

---
---

## Table of Contents


* [Changelog](#changelog)
  * [Releases v1.7.1](#releases-v171)
  * [Major Releases v1.7.0](#major-releases-v170)
  * [Major Releases v1.6.0](#major-releases-v160)
  * [Major Releases v1.5.0](#major-releases-v150)
  * [Major Releases v1.4.0](#major-releases-v140)
  * [Releases v1.3.1](#releases-v131)
  * [Major Releases v1.3.0](#major-releases-v130)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.13](#releases-v1013)
  * [Releases v1.0.12](#releases-v1012)
  * [Releases v1.0.11](#releases-v1011)
  * [Releases v1.0.10](#releases-v1010)
  * [Releases v1.0.9](#releases-v109)
  * [Releases v1.0.8](#releases-v108)
  * [Releases v1.0.7](#releases-v107)
  * [Releases v1.0.6](#releases-v106)
  * [Releases v1.0.5](#releases-v105)
  * [Releases v1.0.4](#releases-v104)

---
---

## Changelog

### Releases v1.7.1

1. Change option for PIO `lib_compat_mode` from default `soft` to `strict` to minimize compile error in crosss-platform
2. Update `Packages' Patches` for many boards

### Major Releases v1.7.0

1. Add support to **Portenta_H7** using [**Arduino mbed_portenta core**](https://github.com/arduino/ArduinoCore-mbed).
2. Update `Packages' Patches` for **Portenta_H7**

### Major Releases v1.6.0

1. Add support to [QNEthernet Library](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet
2. Update examples with new features

### Major Releases v1.5.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core** v1.3.1+](https://github.com/earlephilhower/arduino-pico).
2. Update examples with new features

### Major Releases v1.4.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
2. Update examples with new features

### Releases v1.3.1

1. Add working example [SimpleWebServer_NativeEthernet](examples/SimpleWebServer_NativeEthernet) for Teensy 4.1 NativeEthernet. Check [EthernetWebServer-on-Teensy4-1-with-MagJack](https://forum.pjrc.com/threads/67060-Khoi-Hoang-s-EthernetWebServer-on-Teensy4-1-with-MagJack-anyone-successful)
2. Delete not working example **AdvancedWebServer_NativeEthernet**
3. Enhance Debugging code

### Major Releases v1.3.0

1. Add WebServer feature to serve from LittleFS/SPIFFS for ESP32/ESP8266 with examples. Check [**streamFile and serveStatic for ESP8266/ESP32 boards #22**](https://github.com/khoih-prog/EthernetWebServer/pull/22)
2. Add examples [**serveStatic**](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/serveStatic) and [**serveStaticLoadFile**](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/serveStaticLoadFile) to use new `serveStatic()`feature
3. Add examples [**ESP32_FS_EthernetWebServer**](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/ESP32_FS_EthernetWebServer) and [**FS_EthernetWebServer**](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/FS_EthernetWebServer) to use new `serveStatic()`feature

### Releases v1.2.1

1. Clean-up all compiler warnings possible.
2. Add Table of Contents
3. Add examples
4. Modify Version String 

### Releases v1.2.0

1. Add support to [NativeEthernet Library](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1
2. Add Version String.

### Major Releases v1.1.0

1. Add high-level **HTTP and WebSockets Client** by merging [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient)
2. Add many more examples for HTTP and WebSockets Client.

### Releases v1.0.13

1. Add support to **PROGMEM-related commands, such as sendContent_P() and send_P()**
2. Update Platform.ini to support PlatformIO 5.x owner-based dependency declaration.
3. Clean up code. 
4. Update examples.

#### Releases v1.0.12

1. Add support to new [**`EthernetENC library`**](https://github.com/jandrassy/EthernetENC) for ENC28J60.
2. Add debug feature. Clean up code.

#### Releases v1.0.11

1. Add support to **Seeeduino SAMD21/SAMD51 boards** (LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.)
2. Add and restructure examples.

#### Releases v1.0.10

1. Fix bug not closing client and releasing socket.
2. Merge new features from latest [ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)
3. Add and enhance examples.

#### Releases v1.0.9

1. Add EthernetWrapper.h for easier W5x00 support as well as more Ethernet libs in the future.
2. Add default SS/CS pin for ESP8266 and ESP32
3. Increase default clock speed for W5x00 in [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), and [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) libraries to 25MHz from 14MHz. Tested OK on W5100 as well as W5500.

#### Releases v1.0.8

1. Fix W5x00 support for ESP8266 and many more boards.

#### Releases v1.0.7

1. Add ENC28J60 support to **ESP32 and ESP8266** boards.

#### Releases v1.0.6

1. Add W5x00 nsupport to **ESP32 and ESP8266** boards.

#### Releases v1.0.5

1. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, etc.**
2. Support any future custom Ethernet library that meets the no-compiling-error requirements. Currently [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) and [`Ethernet3`](https://github.com/sstaub/Ethernet3) libraries are supported. **Ethernet_Shield_W5200, EtherCard, EtherSia** libraries are not supported now.

#### Releases v1.0.4

1. Add support to **SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.

From v1.0.3+, the library supports more Arduino boards ( SAM DUE, SAMD21: ZERO, MKR, **NANO_33_IOT**, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)

From v1.0.2+, the library supports many more Arduino boards (Atmel AVR-s, Atmel SAM3X8E ARM Cortex-M3, STM32F series, ESP8266, Intel ARC32(Genuino101), Nordic nRF51(RFduino), Teensy boards, Realtek Ameba(RTL8195A,RTL8710)) using Wiznet W5x00 or ENC28J60 Ethernet shields by using [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library besides standard [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet) library.


