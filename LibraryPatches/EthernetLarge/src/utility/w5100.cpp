/****************************************************************************************************************************
   w5100.cpp - Driver for W5x00

   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license
   Version: 1.0.9

   Copyright 2018 Paul Stoffregen
   Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 
   This file is free software; you can redistribute it and/or modify
   it under the terms of either the GNU General Public License version 2
   or the GNU Lesser General Public License version 2.1, both as
   published by the Free Software Foundation.

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
    1.0.1   K Hoang      20/02/2020 Add support to lambda functions
    1.0.2   K Hoang      20/02/2020 Add support to UIPEthernet library for ENC28J60
    1.0.3   K Hoang      23/02/2020 Add support to SAM DUE / SAMD21 boards
    1.0.4   K Hoang      16/04/2020 Add support to SAMD51 boards
    1.0.5   K Hoang      24/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, 
                                    Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, etc. 
                                    More Custom Ethernet libraries supported such as Ethernet2, Ethernet3, EthernetLarge
    1.0.6   K Hoang      27/04/2020 Add support to ESP32/ESP8266 boards
    1.0.7   K Hoang      30/04/2020 Add ENC28J60 support to ESP32/ESP8266 boards    
    1.0.8   K Hoang      12/05/2020 Fix W5x00 support for ESP8266 boards.
    1.0.9   K Hoang      15/05/2020 Add EthernetWrapper.h for easier W5x00 support as well as more Ethernet libs in the future. 
 *****************************************************************************************************************************/

#include <Arduino.h>
#include "EthernetLarge.h"
#include "w5100.h"

#define W5100_DEBUG   1

/***************************************************/
/**            Default SS pin setting             **/
/***************************************************/

// If variant.h or other headers specifically define the
// default SS pin for ethernet, use it.
#if defined(PIN_SPI_SS_ETHERNET_LIB)

#define SS_PIN_DEFAULT  PIN_SPI_SS_ETHERNET_LIB
//KH
#warning w5100.cpp Use PIN_SPI_SS_ETHERNET_LIB defined, change SS_PIN_DEFAULT to PIN_SPI_SS_ETHERNET_LIB

// MKR boards default to pin 5 for MKR ETH
// Pins 8-10 are MOSI/SCK/MISO on MRK, so don't use pin 10
#elif defined(USE_ARDUINO_MKR_PIN_LAYOUT) || defined(ARDUINO_SAMD_MKRZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRWAN1300)

#define SS_PIN_DEFAULT  5
//KH
#warning w5100.cpp Use MKR, change SS_PIN_DEFAULT to 5

// For boards using AVR, assume shields with SS on pin 10
// will be used.  This allows for Arduino Mega (where
// SS is pin 53) and Arduino Leonardo (where SS is pin 17)
// to work by default with Arduino Ethernet Shield R2 & R3.
#elif defined(__AVR__)

#define SS_PIN_DEFAULT  10
//KH
#warning w5100.cpp Use __AVR__, change SS_PIN_DEFAULT to 10

// If variant.h or other headers define these names
// use them if none of the other cases match
#elif defined(PIN_SPI_SS)

#if defined(__SAMD21G18A__)
//10 - 2 (6 conflict) all not OK for Nano 33 IoT !!! SPI corrupted???
#warning w5100.cpp Use __SAMD21G18A__, change SS_PIN_DEFAULT to 10
#define SS_PIN_DEFAULT  10
#else
#define SS_PIN_DEFAULT  PIN_SPI_SS

//KH
#warning w5100.cpp Use PIN_SPI_SS defined, change SS_PIN_DEFAULT to PIN_SPI_SS
#endif

#elif defined(CORE_SS0_PIN)
#define SS_PIN_DEFAULT  CORE_SS0_PIN

//KH
#warning w5100.cpp Use CORE_SS0_PIN defined, change SS_PIN_DEFAULT to CORE_SS0_PIN

//KH for ESP32
#elif defined(ESP32)
//pin SS already defined in ESP32 as pin 5, don't use this as conflict with SPIFFS, EEPROM, etc.
// Use in GPIO22
#warning w5100.cpp Use ESP32, change SS_PIN_DEFAULT to GPIO22, MOSI(23), MISO(19), SCK(18)
#define SS_PIN_DEFAULT  22    //SS
///////

//KH for ESP8266
#elif defined(ESP8266)
//pin SS already defined in ESP8266 as pin 15. Conflict => Move to pin GPIO4 (D2)
#warning w5100.cpp Use ESP8266, change SS_PIN_DEFAULT to SS(4), MOSI(13), MISO(12), SCK(14)
#define SS_PIN_DEFAULT  D2      // GPIO4, SS

///////

// As a final fallback, use pin 10
#else
#define SS_PIN_DEFAULT  10

//KH
#warning w5100.cpp Use fallback, change SS_PIN_DEFAULT to 10

#endif

// W5100 controller instance
uint8_t  W5100Class::chip = 0;
uint8_t  W5100Class::CH_BASE_MSB;
uint8_t  W5100Class::ss_pin = SS_PIN_DEFAULT;
#ifdef ETHERNET_LARGE_BUFFERS
uint16_t W5100Class::SSIZE = 2048;
uint16_t W5100Class::SMASK = 0x07FF;
#endif
W5100Class W5100;

// pointers and bitmasks for optimized SS pin
#if defined(__AVR__)
  volatile uint8_t * W5100Class::ss_pin_reg;
  uint8_t W5100Class::ss_pin_mask;
#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK66FX1M0__) || defined(__MK64FX512__)
  volatile uint8_t * W5100Class::ss_pin_reg;
#elif defined(__IMXRT1062__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__MKL26Z64__)
  volatile uint8_t * W5100Class::ss_pin_reg;
  uint8_t W5100Class::ss_pin_mask;
#elif defined(__SAM3X8E__) || defined(__SAM3A8C__) || defined(__SAM3A4C__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__PIC32MX__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(ARDUINO_ARCH_ESP8266)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
#elif defined(__SAMD21G18A__)
  volatile uint32_t * W5100Class::ss_pin_reg;
  uint32_t W5100Class::ss_pin_mask;
  #warning w5100.cpp Use __SAMD21G18A__
#endif

// KH
uint8_t W5100Class::init(uint8_t socketNumbers, uint8_t new_ss_pin)
{
  // KH
	uint8_t i;

	if (initialized) return 1;

	// Many Ethernet shields have a CAT811 or similar reset chip
	// connected to W5100 or W5200 chips.  The W5200 will not work at
	// all, and may even drive its MISO pin, until given an active low
	// reset pulse!  The CAT811 has a 240 ms typical pulse length, and
	// a 400 ms worst case maximum pulse length.  MAX811 has a worst
	// case maximum 560 ms pulse length.  This delay is meant to wait
	// until the reset pulse is ended.  If your hardware has a shorter
	// reset time, this can be edited or removed.
	delay(560);
	
	//W5100Class::ss_pin = new_ss_pin;
	
#if ( W5100_DEBUG	> 0 )
	//KH
	Serial.print("\nW5100 init, using SS_PIN_DEFAULT = ");
	Serial.print(SS_PIN_DEFAULT);
	Serial.print(", new ss_pin = ");
	Serial.print(new_ss_pin);
	Serial.print(", W5100Class::ss_pin = ");
	Serial.println(W5100Class::ss_pin);
#endif

	SPI.begin();
	
	initSS();
	resetSS();
	
	// From #define SPI_ETHERNET_SETTINGS SPISettings(14000000, MSBFIRST, SPI_MODE0)
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);

	// Attempt W5200 detection first, because W5200 does not properly
	// reset its SPI state when CS goes high (inactive).  Communication
	// from detecting the other chips can leave the W5200 in a state
	// where it won't recover, unless given a reset pulse.
	if (isW5200()) 
	{
		CH_BASE_MSB = 0x40;
#ifdef ETHERNET_LARGE_BUFFERS
#if MAX_SOCK_NUM <= 1
		SSIZE = 16384;
#elif MAX_SOCK_NUM <= 2
		SSIZE = 8192;
#elif MAX_SOCK_NUM <= 4
		SSIZE = 4096;
#else
		SSIZE = 2048;
#endif
		SMASK = SSIZE - 1;
#endif
		for (i=0; i<MAX_SOCK_NUM; i++) 
		{
			writeSnRX_SIZE(i, SSIZE >> 10);
			writeSnTX_SIZE(i, SSIZE >> 10);
		}
		for (; i<8; i++) 
		{
			writeSnRX_SIZE(i, 0);
			writeSnTX_SIZE(i, 0);
		}
		
#if ( W5100_DEBUG	> 0 )		
		Serial.print("W5100::init: W5200, SSIZE =");
    Serial.println(SSIZE);
#endif
		
	// Try W5500 next.  Wiznet finally seems to have implemented
	// SPI well with this chip.  It appears to be very resilient,
	// so try it after the fragile W5200
	} 
	else if (isW5500()) 
	{
		CH_BASE_MSB = 0x10;
#ifdef ETHERNET_LARGE_BUFFERS
#if MAX_SOCK_NUM <= 1
		SSIZE = 16384;
#elif MAX_SOCK_NUM <= 2
		SSIZE = 8192;
#elif MAX_SOCK_NUM <= 4
		SSIZE = 4096;
#else
		SSIZE = 2048;
#endif
		SMASK = SSIZE - 1;
		for (i=0; i<MAX_SOCK_NUM; i++) 
		{
			writeSnRX_SIZE(i, SSIZE >> 10);
			writeSnTX_SIZE(i, SSIZE >> 10);
		}
		for (; i<8; i++) 
		{
			writeSnRX_SIZE(i, 0);
			writeSnTX_SIZE(i, 0);
		}
#endif
		
#if ( W5100_DEBUG	> 0 )
    Serial.print("W5100::init: W5500, SSIZE =");
    Serial.println(SSIZE);
#endif
		

	// Try W5100 last.  This simple chip uses fixed 4 byte frames
	// for every 8 bit access.  Terribly inefficient, but so simple
	// it recovers from "hearing" unsuccessful W5100 or W5200
	// communication.  W5100 is also the only chip without a VERSIONR
	// register for identification, so we check this last.
	} else if (isW5100()) 
	{
		CH_BASE_MSB = 0x04;
#ifdef ETHERNET_LARGE_BUFFERS
#if MAX_SOCK_NUM <= 1
		SSIZE = 8192;
		writeTMSR(0x03);
		writeRMSR(0x03);
#elif MAX_SOCK_NUM <= 2
		SSIZE = 4096;
		writeTMSR(0x0A);
		writeRMSR(0x0A);
#else
		SSIZE = 2048;
		writeTMSR(0x55);
		writeRMSR(0x55);
#endif
		SMASK = SSIZE - 1;
#else
		writeTMSR(0x55);
		writeRMSR(0x55);
#endif

#if ( W5100_DEBUG	> 0 )
  Serial.print("W5100::init: W5100, SSIZE =");
  Serial.println(SSIZE);
#endif

	// No hardware seems to be present.  Or it could be a W5200
	// that's heard other SPI communication if its chip select
	// pin wasn't high when a SD card or other SPI chip was used.
	} 
	else 
	{
#if ( W5100_DEBUG	> 0 )	
		Serial.println("no chip :-(");
#endif
		
		chip = 0;
		SPI.endTransaction();
		return 0; // no known chip is responding :-(
	}
	SPI.endTransaction();
	initialized = true;
	return 1; // successful init
}

// Soft reset the Wiznet chip, by writing to its MR register reset bit
uint8_t W5100Class::softReset(void)
{
	uint16_t count=0;

#if ( W5100_DEBUG	> 1 )	
	Serial.println("EthernetLarge:Wiznet soft reset");
#endif
	
	// write to reset bit
	writeMR(0x80);
	// then wait for soft reset to complete
	do 
	{
		uint8_t mr = readMR();
		
#if ( W5100_DEBUG	> 2 )	
		Serial.print("mr=");
		Serial.println(mr, HEX);
#endif
		
		if (mr == 0) 
		  return 1;
		  
		delay(1);
	} while (++count < 20);
	return 0;
}


uint8_t W5100Class::isW5100(void)
{
	chip = 51;
	
#if ( W5100_DEBUG	> 1 )	
	Serial.println("W5100.cpp: detect W5100 chip");
#endif
	
	if (!softReset()) 
	  return 0;
	  
	writeMR(0x10);
	if (readMR() != 0x10) 
	  return 0;
	  
	writeMR(0x12);
	if (readMR() != 0x12) 
	  return 0;
	  
	writeMR(0x00);
	if (readMR() != 0x00) 
	  return 0;
	  
#if ( W5100_DEBUG	> 1 )	  
	Serial.println("chip is W5100");
#endif
	
	return 1;
}

uint8_t W5100Class::isW5200(void)
{
	chip = 52;
	
#if ( W5100_DEBUG	> 1 )	
	Serial.println("W5100.cpp: detect W5200 chip");
#endif
	
	if (!softReset()) 
	  return 0;
	  
	writeMR(0x08);
	if (readMR() != 0x08) 
	  return 0;
	  
	writeMR(0x10);
	if (readMR() != 0x10) 
	  return 0;
	  
	writeMR(0x00);
	if (readMR() != 0x00) 
	  return 0;
	  
	int ver = readVERSIONR_W5200();
	
#if ( W5100_DEBUG	> 1 )	
	Serial.print("version=");
	Serial.println(ver);
#endif
	
	if (ver != 3) 
	  return 0;
	  
#if ( W5100_DEBUG	> 1 )	  
	Serial.println("chip is W5200");
#endif
	
	return 1;
}

uint8_t W5100Class::isW5500(void)
{
	chip = 55;
	
#if ( W5100_DEBUG	> 1 )	
	Serial.println("W5100.cpp: detect W5500 chip");
#endif
	
	if (!softReset()) 
	  return 0;
	  
	writeMR(0x08);
	if (readMR() != 0x08) 
	  return 0;
	  
	writeMR(0x10);
	if (readMR() != 0x10) 
	  return 0;
	  
	writeMR(0x00);
	if (readMR() != 0x00) 
	  return 0;
	  
	int ver = readVERSIONR_W5500();
	
#if ( W5100_DEBUG	> 1 )	
	Serial.print("version=");
	Serial.println(ver);
#endif
	
	if (ver != 4) 
	  return 0;
	  
#if ( W5100_DEBUG	> 1 )	  
	Serial.println("chip is W5500");
#endif

	return 1;
}

W5100Linkstatus W5100Class::getLinkStatus()
{
	uint8_t phystatus;

	// KH
	if (!initialized) return UNKNOWN;
	
	switch (chip) 
	{
	  case 52:
		SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
		phystatus = readPSTATUS_W5200();
		SPI.endTransaction();
		if (phystatus & 0x20) 
		  return LINK_ON;
		  
		return LINK_OFF;
		
	  case 55:
		SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
		phystatus = readPHYCFGR_W5500();
		SPI.endTransaction();
		if (phystatus & 0x01) 
		  return LINK_ON;
		  
		return LINK_OFF;
		
	  default:
		return UNKNOWN;
	}
}

uint16_t W5100Class::write(uint16_t addr, const uint8_t *buf, uint16_t len)
{
	uint8_t cmd[8];

	if (chip == 51) 
	{
		for (uint16_t i=0; i<len; i++) 
		{
			setSS();
			SPI.transfer(0xF0);
			SPI.transfer(addr >> 8);
			SPI.transfer(addr & 0xFF);
			addr++;
			SPI.transfer(buf[i]);
			resetSS();
		}
	} 
	else if (chip == 52) 
	{
		setSS();
		cmd[0] = addr >> 8;
		cmd[1] = addr & 0xFF;
		cmd[2] = ((len >> 8) & 0x7F) | 0x80;
		cmd[3] = len & 0xFF;
		SPI.transfer(cmd, 4);
		
#ifdef SPI_HAS_TRANSFER_BUF
		SPI.transfer(buf, NULL, len);
#else
		// TODO: copy 8 bytes at a time to cmd[] and block transfer
		for (uint16_t i=0; i < len; i++) 
		{
			SPI.transfer(buf[i]);
		}
#endif
		resetSS();
	} 
	else 
	{ 
	  // chip == 55
		setSS();
		if (addr < 0x100) 
		{
			// common registers 00nn
			cmd[0] = 0;
			cmd[1] = addr & 0xFF;
			cmd[2] = 0x04;
		} 
		else if (addr < 0x8000) 
		{
			// socket registers  10nn, 11nn, 12nn, 13nn, etc
			cmd[0] = 0;
			cmd[1] = addr & 0xFF;
			cmd[2] = ((addr >> 3) & 0xE0) | 0x0C;
		} 
		else if (addr < 0xC000) 
		{
			// transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
			//  10## #nnn nnnn nnnn
			cmd[0] = addr >> 8;
			cmd[1] = addr & 0xFF;
			#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
			cmd[2] = 0x14;                       // 16K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
			cmd[2] = ((addr >> 8) & 0x20) | 0x14; // 8K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
			cmd[2] = ((addr >> 7) & 0x60) | 0x14; // 4K buffers
			#else
			cmd[2] = ((addr >> 6) & 0xE0) | 0x14; // 2K buffers
			#endif
		} 
		else 
		{
			// receive buffers
			cmd[0] = addr >> 8;
			cmd[1] = addr & 0xFF;
			#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
			cmd[2] = 0x1C;                       // 16K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
			cmd[2] = ((addr >> 8) & 0x20) | 0x1C; // 8K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
			cmd[2] = ((addr >> 7) & 0x60) | 0x1C; // 4K buffers
			#else
			cmd[2] = ((addr >> 6) & 0xE0) | 0x1C; // 2K buffers
			#endif
		}
		
		if (len <= 5) 
		{
			for (uint8_t i=0; i < len; i++) 
			{
				cmd[i + 3] = buf[i];
			}
			
			SPI.transfer(cmd, len + 3);
		} 
		else 
		{
			SPI.transfer(cmd, 3);
#ifdef SPI_HAS_TRANSFER_BUF
			SPI.transfer(buf, NULL, len);
#else
			// TODO: copy 8 bytes at a time to cmd[] and block transfer
			for (uint16_t i=0; i < len; i++) 
			{
				SPI.transfer(buf[i]);
			}
#endif
		}
		resetSS();
	}
	return len;
}

uint16_t W5100Class::read(uint16_t addr, uint8_t *buf, uint16_t len)
{
	uint8_t cmd[4];

	if (chip == 51) 
	{
		for (uint16_t i=0; i < len; i++) 
		{
			setSS();
			#if 1
			SPI.transfer(0x0F);
			SPI.transfer(addr >> 8);
			SPI.transfer(addr & 0xFF);
			addr++;
			buf[i] = SPI.transfer(0);
			#else
			cmd[0] = 0x0F;
			cmd[1] = addr >> 8;
			cmd[2] = addr & 0xFF;
			cmd[3] = 0;
			SPI.transfer(cmd, 4); // TODO: why doesn't this work?
			buf[i] = cmd[3];
			addr++;
			#endif
			resetSS();
		}
	} 
	else if (chip == 52) 
	{
		setSS();
		cmd[0] = addr >> 8;
		cmd[1] = addr & 0xFF;
		cmd[2] = (len >> 8) & 0x7F;
		cmd[3] = len & 0xFF;
		SPI.transfer(cmd, 4);
		memset(buf, 0, len);
		SPI.transfer(buf, len);
		resetSS();
	} 
	else 
	{ 
	  // chip == 55
		setSS();
		
		if (addr < 0x100) 
		{
			// common registers 00nn
			cmd[0] = 0;
			cmd[1] = addr & 0xFF;
			cmd[2] = 0x00;
		} 
		else if (addr < 0x8000) 
		{
			// socket registers  10nn, 11nn, 12nn, 13nn, etc
			cmd[0] = 0;
			cmd[1] = addr & 0xFF;
			cmd[2] = ((addr >> 3) & 0xE0) | 0x08;
		} 
		else if (addr < 0xC000) 
		{
			// transmit buffers  8000-87FF, 8800-8FFF, 9000-97FF, etc
			//  10## #nnn nnnn nnnn
			cmd[0] = addr >> 8;
			cmd[1] = addr & 0xFF;
			#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
			cmd[2] = 0x10;                       // 16K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
			cmd[2] = ((addr >> 8) & 0x20) | 0x10; // 8K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
			cmd[2] = ((addr >> 7) & 0x60) | 0x10; // 4K buffers
			#else
			cmd[2] = ((addr >> 6) & 0xE0) | 0x10; // 2K buffers
			#endif
		} else 
		{
			// receive buffers
			cmd[0] = addr >> 8;
			cmd[1] = addr & 0xFF;
			#if defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 1
			cmd[2] = 0x18;                       // 16K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 2
			cmd[2] = ((addr >> 8) & 0x20) | 0x18; // 8K buffers
			#elif defined(ETHERNET_LARGE_BUFFERS) && MAX_SOCK_NUM <= 4
			cmd[2] = ((addr >> 7) & 0x60) | 0x18; // 4K buffers
			#else
			cmd[2] = ((addr >> 6) & 0xE0) | 0x18; // 2K buffers
			#endif
		}
		SPI.transfer(cmd, 3);
		memset(buf, 0, len);
		SPI.transfer(buf, len);
		resetSS();
	}
	return len;
}

void W5100Class::execCmdSn(SOCKET s, SockCMD _cmd)
{
	// Send command to socket
	writeSnCR(s, _cmd);
	// Wait for command to complete
	while (readSnCR(s)) ;
}
