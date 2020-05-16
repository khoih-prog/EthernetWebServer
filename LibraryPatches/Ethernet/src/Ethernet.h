/****************************************************************************************************************************
   Ethernet.h

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
 
#ifndef ethernet_h_
#define ethernet_h_

// All symbols exposed to Arduino sketches are contained in this header file
//
// Older versions had much of this stuff in EthernetClient.h, EthernetServer.h,
// and socket.h.  Including headers in different order could cause trouble, so
// these "friend" classes are now defined in the same header file.  socket.h
// was removed to avoid possible conflict with the C library header files.


// Configure the maximum number of sockets to support.  W5100 chips can have
// up to 4 sockets.  W5200 & W5500 can have up to 8 sockets.  Several bytes
// of RAM are used for each socket.  Reducing the maximum can save RAM, but
// you are limited to fewer simultaneous connections.
#if defined(RAMEND) && defined(RAMSTART) && ((RAMEND - RAMSTART) <= 2048)
#define MAX_SOCK_NUM 2      //Reduce MAX_SOCK_NUM to 2 from 4, to increase buffer from 2k to 4K
#else
#define MAX_SOCK_NUM 4      //Reduce MAX_SOCK_NUM to 4 from 8, to increase buffer from 2k to 4K
#endif

// By default, each socket uses 2K buffers inside the Wiznet chip.  If
// MAX_SOCK_NUM is set to fewer than the chip's maximum, uncommenting
// this will use larger buffers within the Wiznet chip.  Large buffers
// can really help with UDP protocols like Artnet.  In theory larger
// buffers should allow faster TCP over high-latency links, but this
// does not always seem to work in practice (maybe Wiznet bugs?)
//
//KH, to increase buffer size for W5x00 to min 4K
#define ETHERNET_LARGE_BUFFERS


#include <Arduino.h>
#include "Client.h"
#include "Server.h"
#include "Udp.h"

enum EthernetLinkStatus {
	Unknown,
	LinkON,
	LinkOFF
};

enum EthernetHardwareStatus {
	EthernetNoHardware,
	EthernetW5100,
	EthernetW5200,
	EthernetW5500
};

class EthernetUDP;
class EthernetClient;
class EthernetServer;
class DhcpClass;

class EthernetClass {
private:
	static IPAddress _dnsServerAddress;
	static DhcpClass* _dhcp;
public:
  // KH
  uint8_t _maxSockNum;
  uint8_t _pinCS;
  uint8_t _pinRST;
  
  void setRstPin(uint8_t pinRST = 9); // for WIZ550io or USR-ES1, must set befor Ethernet.begin
  void setCsPin(uint8_t pinCS = 10); // must set befor Ethernet.begin

  // Initialize with less sockets but more RX/TX Buffer
  // maxSockNum = 1 Socket 0 -> RX/TX Buffer 16k
  // maxSockNum = 2 Socket 0, 1 -> RX/TX Buffer 8k
  // maxSockNum = 4 Socket 0...3 -> RX/TX Buffer 4k
  // maxSockNum = 8 (Standard) all sockets -> RX/TX Buffer 2k
  // be carefull of the MAX_SOCK_NUM, because in the moment it can't dynamicly changed
  void initMaxSockNum(uint8_t maxSockNum = 8);

  uint8_t softreset(); // can set only after Ethernet.begin
  void hardreset(); // You need to set the Rst pin
  
	// Initialise the Ethernet shield to use the provided MAC address and
	// gain the rest of the configuration through DHCP.
	// Returns 0 if the DHCP configuration failed, and 1 if it succeeded
	int begin(uint8_t *mac, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);
	int maintain();
	EthernetLinkStatus linkStatus();
	EthernetHardwareStatus hardwareStatus();

	// Manual configuration
	 void begin(uint8_t *mac, IPAddress ip);
	 void begin(uint8_t *mac, IPAddress ip, IPAddress dns);
	 void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway);
	 void begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet);
	 void init(uint8_t sspin = 10);

	 void MACAddress(uint8_t *mac_address);
	 IPAddress localIP();
	 IPAddress subnetMask();
	 IPAddress gatewayIP();
	 IPAddress dnsServerIP() { return _dnsServerAddress; }

	void setMACAddress(const uint8_t *mac_address);
	void setLocalIP(const IPAddress local_ip);
	void setSubnetMask(const IPAddress subnet);
	void setGatewayIP(const IPAddress gateway);
	void setDnsServerIP(const IPAddress dns_server) { _dnsServerAddress = dns_server; }
	void setRetransmissionTimeout(uint16_t milliseconds);
	void setRetransmissionCount(uint8_t num);

	friend class EthernetClient;
	friend class EthernetServer;
	friend class EthernetUDP;
private:
	// Opens a socket(TCP or UDP or IP_RAW mode)
	 uint8_t socketBegin(uint8_t protocol, uint16_t port);
	 uint8_t socketBeginMulticast(uint8_t protocol, IPAddress ip,uint16_t port);
	 uint8_t socketStatus(uint8_t s);
	// Close socket
	 void socketClose(uint8_t s);
	// Establish TCP connection (Active connection)
	 void socketConnect(uint8_t s, uint8_t * addr, uint16_t port);
	// disconnect the connection
	 void socketDisconnect(uint8_t s);
	// Establish TCP connection (Passive connection)
	 uint8_t socketListen(uint8_t s);
	// Send data (TCP)
	 uint16_t socketSend(uint8_t s, const uint8_t * buf, uint16_t len);
	 uint16_t socketSendAvailable(uint8_t s);
	// Receive data (TCP)
	 int socketRecv(uint8_t s, uint8_t * buf, int16_t len);
	 uint16_t socketRecvAvailable(uint8_t s);
	 uint8_t socketPeek(uint8_t s);
	// sets up a UDP datagram, the data for which will be provided by one
	// or more calls to bufferData and then finally sent with sendUDP.
	// return true if the datagram was successfully set up, or false if there was an error
	 bool socketStartUDP(uint8_t s, uint8_t* addr, uint16_t port);
	// copy up to len bytes of data from buf into a UDP datagram to be
	// sent later by sendUDP.  Allows datagrams to be built up from a series of bufferData calls.
	// return Number of bytes successfully buffered
	 uint16_t socketBufferData(uint8_t s, uint16_t offset, const uint8_t* buf, uint16_t len);
	// Send a UDP datagram built up from a sequence of startUDP followed by one or more
	// calls to bufferData.
	// return true if the datagram was successfully sent, or false if there was an error
	 bool socketSendUDP(uint8_t s);
	// Initialize the "random" source port number
	 void socketPortRand(uint16_t n);
};

extern EthernetClass Ethernet;


#define UDP_TX_PACKET_MAX_SIZE 24

class EthernetUDP : public UDP {
private:
	uint16_t _port; // local port to listen on
	IPAddress _remoteIP; // remote IP address for the incoming packet whilst it's being processed
	uint16_t _remotePort; // remote port for the incoming packet whilst it's being processed
	uint16_t _offset; // offset into the packet being sent

protected:
	uint8_t sockindex;
	uint16_t _remaining; // remaining bytes of incoming packet yet to be processed

public:
	EthernetUDP() : sockindex(MAX_SOCK_NUM) {}  // Constructor
	virtual uint8_t begin(uint16_t);      // initialize, start listening on specified port. Returns 1 if successful, 0 if there are no sockets available to use
	virtual uint8_t beginMulticast(IPAddress, uint16_t);  // initialize, start listening on specified port. Returns 1 if successful, 0 if there are no sockets available to use
	virtual void stop();  // Finish with the UDP socket

	// Sending UDP packets

	// Start building up a packet to send to the remote host specific in ip and port
	// Returns 1 if successful, 0 if there was a problem with the supplied IP address or port
	virtual int beginPacket(IPAddress ip, uint16_t port);
	// Start building up a packet to send to the remote host specific in host and port
	// Returns 1 if successful, 0 if there was a problem resolving the hostname or port
	virtual int beginPacket(const char *host, uint16_t port);
	// Finish off this packet and send it
	// Returns 1 if the packet was sent successfully, 0 if there was an error
	virtual int endPacket();
	// Write a single byte into the packet
	virtual size_t write(uint8_t);
	// Write size bytes from buffer into the packet
	virtual size_t write(const uint8_t *buffer, size_t size);

	using Print::write;

	// Start processing the next available incoming packet
	// Returns the size of the packet in bytes, or 0 if no packets are available
	virtual int parsePacket();
	// Number of bytes remaining in the current packet
	virtual int available();
	// Read a single byte from the current packet
	virtual int read();
	// Read up to len bytes from the current packet and place them into buffer
	// Returns the number of bytes read, or 0 if none are available
	virtual int read(unsigned char* buffer, size_t len);
	// Read up to len characters from the current packet and place them into buffer
	// Returns the number of characters read, or 0 if none are available
	virtual int read(char* buffer, size_t len) { return read((unsigned char*)buffer, len); };
	// Return the next byte from the current packet without moving on to the next byte
	virtual int peek();
	virtual void flush(); // Finish reading the current packet

	// Return the IP address of the host who sent the current incoming packet
	virtual IPAddress remoteIP() { return _remoteIP; };
	// Return the port of the host who sent the current incoming packet
	virtual uint16_t remotePort() { return _remotePort; };
	virtual uint16_t localPort() { return _port; }
};




class EthernetClient : public Client {
public:

	EthernetClient() : sockindex(MAX_SOCK_NUM), _timeout(5000) { }
	EthernetClient(uint8_t s) : sockindex(s), _timeout(5000) { }
  
	uint8_t status();
	virtual int connect(IPAddress ip, uint16_t port);
	virtual int connect(const char *host, uint16_t port);
	virtual int availableForWrite(void);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buf, size_t size);
	
	virtual int available();
	virtual int read();
	virtual int read(uint8_t *buf, size_t size);
	virtual int peek();
	virtual void flush();
	virtual void stop();
	virtual uint8_t connected();
	virtual operator bool() { return sockindex < MAX_SOCK_NUM; }
	virtual bool operator==(const bool value) { return bool() == value; }
	virtual bool operator!=(const bool value) { return bool() != value; }
	virtual bool operator==(const EthernetClient&);
	virtual bool operator!=(const EthernetClient& rhs) { return !this->operator==(rhs); }
	uint8_t getSocketNumber() const { return sockindex; }
	virtual uint16_t localPort();
	virtual IPAddress remoteIP();
	virtual uint16_t remotePort();
	virtual void setConnectionTimeout(uint16_t timeout) { _timeout = timeout; }

	friend class EthernetServer;

	using Print::write;

private:
	uint8_t sockindex; // MAX_SOCK_NUM means client not in use
	uint16_t _timeout;
};


class EthernetServer : public Server {
private:
	uint16_t _port;
public:
	EthernetServer(uint16_t port) : _port(port) { }
	EthernetClient available();
	EthernetClient accept();
	virtual void begin();
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buf, size_t size);
	virtual operator bool();
	using Print::write;
	//void statusreport();

	// TODO: make private when socket allocation moves to EthernetClass
	static uint16_t server_port[MAX_SOCK_NUM];
};


class DhcpClass {
private:
	uint32_t _dhcpInitialTransactionId;
	uint32_t _dhcpTransactionId;
	uint8_t  _dhcpMacAddr[6];
#ifdef __arm__
	uint8_t  _dhcpLocalIp[4] __attribute__((aligned(4)));
	uint8_t  _dhcpSubnetMask[4] __attribute__((aligned(4)));
	uint8_t  _dhcpGatewayIp[4] __attribute__((aligned(4)));
	uint8_t  _dhcpDhcpServerIp[4] __attribute__((aligned(4)));
	uint8_t  _dhcpDnsServerIp[4] __attribute__((aligned(4)));
#else
	uint8_t  _dhcpLocalIp[4];
	uint8_t  _dhcpSubnetMask[4];
	uint8_t  _dhcpGatewayIp[4];
	uint8_t  _dhcpDhcpServerIp[4];
	uint8_t  _dhcpDnsServerIp[4];
#endif
	uint32_t _dhcpLeaseTime;
	uint32_t _dhcpT1, _dhcpT2;
	uint32_t _renewInSec;
	uint32_t _rebindInSec;
	unsigned long _timeout;
	unsigned long _responseTimeout;
	unsigned long _lastCheckLeaseMillis;
	uint8_t _dhcp_state;
	EthernetUDP _dhcpUdpSocket;

	int request_DHCP_lease();
	void reset_DHCP_lease();
	void presend_DHCP();
	void send_DHCP_MESSAGE(uint8_t, uint16_t);
	void printByte(char *, uint8_t);

	uint8_t parseDHCPResponse(unsigned long responseTimeout, uint32_t& transactionId);
public:
	IPAddress getLocalIp();
	IPAddress getSubnetMask();
	IPAddress getGatewayIp();
	IPAddress getDhcpServerIp();
	IPAddress getDnsServerIp();

	int beginWithDHCP(uint8_t *, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);
	int checkLease();
};

#endif
