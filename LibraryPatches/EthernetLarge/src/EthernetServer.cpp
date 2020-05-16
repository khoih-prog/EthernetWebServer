/****************************************************************************************************************************
   EthernetServer.cpp

   EthernetWebServer is a library for the Ethernet shields to run WebServer

   Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
   Licensed under MIT license
   Version: 1.0.9

   Copyright 2018 Paul Stoffregen
 
   Permission is hereby granted, free of charge, to any person obtaining a copy of this
   software and associated documentation files (the "Software"), to deal in the Software
   without restriction, including without limitation the rights to use, copy, modify,
   merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to the following
   conditions:
 
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
 
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
   PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
#include "utility/w5100.h"

uint16_t EthernetServer::server_port[MAX_SOCK_NUM];


void EthernetServer::begin()
{
	uint8_t sockindex = Ethernet.socketBegin(SnMR::TCP, _port);
	if (sockindex < MAX_SOCK_NUM) {
		if (Ethernet.socketListen(sockindex)) {
			server_port[sockindex] = _port;
		} else {
			Ethernet.socketDisconnect(sockindex);
		}
	}
}

EthernetClient EthernetServer::available()
{
	bool listening = false;
	uint8_t sockindex = MAX_SOCK_NUM;
	uint8_t chip, maxindex=MAX_SOCK_NUM;

	chip = W5100.getChip();
	if (!chip) return EthernetClient(MAX_SOCK_NUM);
#if MAX_SOCK_NUM > 4
	if (chip == 51) maxindex = 4; // W5100 chip never supports more than 4 sockets
#endif

	for (uint8_t i=0; i < maxindex; i++) 
	{
		if (server_port[i] == _port) 
		{
			uint8_t stat = Ethernet.socketStatus(i);
			if (stat == SnSR::ESTABLISHED || stat == SnSR::CLOSE_WAIT) 
			{
				if (Ethernet.socketRecvAvailable(i) > 0) 
				{				
					sockindex = i;
				} 
				else 
				{
					// remote host closed connection, our end still open
					if (stat == SnSR::CLOSE_WAIT) 
					{				  
						Ethernet.socketDisconnect(i);
						// status becomes LAST_ACK for short time
					}
				}
			} 
			else if (stat == SnSR::LISTEN) 
			{
				listening = true;
			} 
			else if (stat == SnSR::CLOSED) 
			{			
				server_port[i] = 0;
			}
		}
	}
	
	if (!listening)
	{				
	  begin();
	}
	  
	return EthernetClient(sockindex);
}

EthernetClient EthernetServer::accept()
{
	bool listening = false;
	uint8_t sockindex = MAX_SOCK_NUM;
	uint8_t chip, maxindex=MAX_SOCK_NUM;

	chip = W5100.getChip();
	if (!chip) return EthernetClient(MAX_SOCK_NUM);
#if MAX_SOCK_NUM > 4
	if (chip == 51) maxindex = 4; // W5100 chip never supports more than 4 sockets
#endif

	for (uint8_t i=0; i < maxindex; i++) 
	{
		if (server_port[i] == _port) 
		{
			uint8_t stat = Ethernet.socketStatus(i);
			
			if (sockindex == MAX_SOCK_NUM && (stat == SnSR::ESTABLISHED || stat == SnSR::CLOSE_WAIT)) 
			  {
				// Return the connected client even if no data received.
				// Some protocols like FTP expect the server to send the
				// first data.
				sockindex = i;
				server_port[i] = 0; // only return the client once
			} 
			else if (stat == SnSR::LISTEN) 
      {
				listening = true;
			} 
			else if (stat == SnSR::CLOSED) 
			{
				server_port[i] = 0;
			}
		}
	}
	
	if (!listening) 
	  begin();
	  
	return EthernetClient(sockindex);
}

EthernetServer::operator bool()
{
	uint8_t maxindex=MAX_SOCK_NUM;
#if MAX_SOCK_NUM > 4
	if (W5100.getChip() == 51) maxindex = 4; // W5100 chip never supports more than 4 sockets
#endif

	for (uint8_t i=0; i < maxindex; i++) 
	{
		if (server_port[i] == _port) 
		{
			if (Ethernet.socketStatus(i) == SnSR::LISTEN) 
			{
				return true; // server is listening for incoming clients
			}
		}
	}
	return false;
}

#if 0
void EthernetServer::statusreport()
{
	Serial.printf("EthernetServer, port=%d\n", _port);
	for (uint8_t i=0; i < MAX_SOCK_NUM; i++) {
		uint16_t port = server_port[i];
		uint8_t stat = Ethernet.socketStatus(i);
		const char *name;
		switch (stat) {
			case 0x00: name = "CLOSED"; break;
			case 0x13: name = "INIT"; break;
			case 0x14: name = "LISTEN"; break;
			case 0x15: name = "SYNSENT"; break;
			case 0x16: name = "SYNRECV"; break;
			case 0x17: name = "ESTABLISHED"; break;
			case 0x18: name = "FIN_WAIT"; break;
			case 0x1A: name = "CLOSING"; break;
			case 0x1B: name = "TIME_WAIT"; break;
			case 0x1C: name = "CLOSE_WAIT"; break;
			case 0x1D: name = "LAST_ACK"; break;
			case 0x22: name = "UDP"; break;
			case 0x32: name = "IPRAW"; break;
			case 0x42: name = "MACRAW"; break;
			case 0x5F: name = "PPPOE"; break;
			default: name = "???";
		}
		int avail = Ethernet.socketRecvAvailable(i);
		Serial.printf("  %d: port=%d, status=%s (0x%02X), avail=%d\n",
			i, port, name, stat, avail);
	}
}
#endif

size_t EthernetServer::write(uint8_t b)
{
	return write(&b, 1);
}

size_t EthernetServer::write(const uint8_t *buffer, size_t size)
{
	uint8_t chip, maxindex=MAX_SOCK_NUM;

	chip = W5100.getChip();
	if (!chip) return 0;
#if MAX_SOCK_NUM > 4
	if (chip == 51) maxindex = 4; // W5100 chip never supports more than 4 sockets
#endif
	available();
	
	for (uint8_t i=0; i < maxindex; i++) 
	{
		if (server_port[i] == _port) 
		{
			if (Ethernet.socketStatus(i) == SnSR::ESTABLISHED) 
			{
				Ethernet.socketSend(i, buffer, size);
			}
		}
	}
	return size;
}
