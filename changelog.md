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


* [Changelog](#changelog)
  * [Releases v2.3.0](#releases-v230)
  * [Releases v2.2.4](#releases-v224)
  * [Releases v2.2.3](#releases-v223)
  * [Releases v2.2.2](#releases-v222)
  * [Releases v2.2.1](#releases-v221)
  * [Releases v2.2.0](#releases-v220)
  * [Releases v2.1.3](#releases-v213)
  * [Releases v2.1.2](#releases-v212)
  * [Releases v2.1.1](#releases-v211)
  * [Releases v2.1.0](#releases-v210)
  * [Releases v2.0.2](#releases-v202)
  * [Releases v2.0.1](#releases-v201)
  * [Major Releases v2.0.0](#major-releases-v200)
  * [Releases v1.8.6](#releases-v186)
  * [Releases v1.8.5](#releases-v185)
  * [Releases v1.8.4](#releases-v184)
  * [Releases v1.8.3](#releases-v183)
  * [Releases v1.8.2](#releases-v182)
  * [Releases v1.8.1](#releases-v181)
  * [Major Releases v1.8.0](#major-releases-v180)
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

### Releases v2.3.0

1. Add new features, such as `CORS`, etc.
2. Add example [EthernetWebServer_BigData](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/EthernetWebServer_BigData) to demo how to send larger data than `2/4/8/16K` buffer
3. Modify example [AdvancedWebServer](https://github.com/khoih-prog/EthernetWebServer/tree/master/examples/AdvancedWebServer) to demo how to send larger data than `2/4/8/16K` buffer
4. Update code
5. Update `Packages' Patches`

### Releases v2.2.4

1. Add support to Seeeduino nRF52840-based boards such as **Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE**, etc. using Seeed `mbed` or `nRF52` core
2. Add astyle using `allman` style. Restyle the library
3. Display warning only when `_ETHERNET_WEBSERVER_LOGLEVEL_` > 3
4. Update examples
5. Update `Packages' Patches` to add Seeeduino `nRF52` core

### Releases v2.2.3

1. Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using [DxCore](https://github.com/SpenceKonde/DxCore)
2. Update `Packages' Patches`

### Releases v2.2.2

1. Slow SPI clock for old W5100 shield or SAMD Zero
2. Use correct Debug Terminal `Serial` for so-called **SAMD21 Zero** boards from Arduino as well as Adafruit
3. Update `Packages' Patches`

### Releases v2.2.1

1. Auto-select SPI(s) `SS/CS` pins according to board package if available
2. Update `Packages' Patches`


### Releases v2.2.0

1. Add support to SPI1, SPI2 for Teensy using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
2. Add support to custom SPI for Mbed RP2040, Portenta-H7, etc. using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
3. Add examples [AdvancedWebServer_Teensy4x_SPI1](examples/AdvancedWebServer_Teensy4x_SPI1) to demo new feature
4. Add examples [AdvancedWebServer_RP2040_SPI1](examples/AdvancedWebServer_RP2040_SPI1) to demo new feature

### Releases v2.1.3

1. Change from `arduino.cc` to `arduino.tips` in examples

### Releases v2.1.2

1. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
2. Drop `EthernetWrapper`
3. Rewrite all the examples to support new features
4. Add example [multiFileProject](examples/multiFileProject) to demo how to avoid `multiple-definitions` linker error for multiple-file project
5. Update `Packages' Patches`

### Releases v2.1.1

1. Fix compiler error for Portenta_H7 using Portenta Ethernet

### Releases v2.1.0

1. Use new [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
2. Support SPI2 for ESP32
3. Add examples and rewrite all the examples to support new features
4. Update `Packages' Patches`

### Releases v2.0.2

1. Fix bug when using `QNEthernet` staticIP. Check [QNEthernet and NativeEthernet staticIP not working with WS Server #39](https://github.com/khoih-prog/WebSockets2_Generic/issues/39)
2. Simplify and add staticIP option to `NativeEthernet` examples
3. Add support to SAMD21/SAMD51 boards using [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
4. Add `Packages' Patches` for [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
5. Update `Packages' Patches`

### Releases v2.0.1

1. Fix decoding error bug when using special `&` in data fields. Check [Decoding Error. two times called urlDecode in Parsing-impl.h. #17](https://github.com/khoih-prog/WiFiWebServer/issues/17)
2. Update `Packages' Patches`

### Major Releases v2.0.0

1. Make **breaking** changes to permit coexistence with `ESP32 WebServer` and `ESP8266 ESP8266WebServer` libraries
2. Add and modified examples

### Releases v1.8.6

1. Fix bug not supporting boards. Check [Missing ESP definitions ..... #45](https://github.com/khoih-prog/EthernetWebServer/issues/45)

### Releases v1.8.5

1. Restore support to AVR Mega2560
2. Add support to megaAVR boards such as `Arduino Nano Every`, `UNO WiFi Rev 2` using `ATmega4809` MPU
3. Fix libb64 fallthrough compile warning

### Releases v1.8.4

1. Fix libb64 compile error for ESP8266. Check [multiple definition of base64 error with ver. 1.8.3 #44](https://github.com/khoih-prog/EthernetWebServer/issues/44)
2. Update `Packages' Patches`

### Releases v1.8.3

1. Fix authenticate issue caused by libb64

### Releases v1.8.2

1. Fix wrong http status header bug. Check [fix for wrong http status header #42](https://github.com/khoih-prog/EthernetWebServer/pull/42)


### Releases v1.8.1

1. Fix bug related to String in library and examples

### Major Releases v1.8.0

1. Reduce usage of Arduino String with std::string
2. Optimize library code and examples by using **reference-passing instead of value-passing**.
3. Update `Packages' Patches`

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


