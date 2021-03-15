/*
 modified 12 Aug 2013
 by Soohwan Kim (suhwan@wiznet.co.kr)

- 10 Apr. 2015
 Added support for Arduino Ethernet Shield 2
 by Arduino.org team

 */

#include "Ethernet3.h"
#include "Dhcp.h"

// XXX: don't make assumptions about the value of MAX_SOCK_NUM.
uint8_t EthernetClass::_state[MAX_SOCK_NUM] = { 0, };
uint16_t EthernetClass::_server_port[MAX_SOCK_NUM] = { 0, };

void EthernetClass::setRstPin(uint8_t pinRST) {
  _pinRST = pinRST;
  pinMode(_pinRST, OUTPUT);
  digitalWrite(_pinRST, HIGH);
  }
void EthernetClass::setCsPin(uint8_t pinCS) {
  _pinCS = pinCS;
  }

void EthernetClass::init(uint8_t maxSockNum) {
  _maxSockNum = maxSockNum;
  }

uint8_t EthernetClass::softreset() {
  return w5500.softReset();
  }

void EthernetClass::hardreset() {
  if(_pinRST != 0) {
    digitalWrite(_pinRST, LOW);
    delay(1);
    digitalWrite(_pinRST, HIGH);
    delay(150);
    }
  }

#if defined(WIZ550io_WITH_MACADDRESS)

int EthernetClass::begin(void)
{
  // KH mod to work with new func void MACAddress(uint8_t *mac_address); and SinricPro v2.5.1+
  // Now store to private var _mac_address
  //uint8_t mac_address[6] ={0,};
  //////
  
  _dhcp = new DhcpClass();

  // Initialise the basic info
  w5500.init(_maxSockNum, _pinCS);
  w5500.setIPAddress(IPAddress(0,0,0,0).raw_address());
  
  // KH mod
  w5500.getMACAddress(_mac_address);
  //////

  if (strlen(_customHostname) != 0)
  {
    _dhcp->setCustomHostname(_customHostname);
  }
  
  // Now try to get our config info from a DHCP server
  // KH mod
  int ret = _dhcp->beginWithDHCP(_mac_address);
  //////
  
  if(ret == 1)
  {
    // We've successfully found a DHCP server and got our configuration info, so set things
    // accordingly
    w5500.setIPAddress(_dhcp->getLocalIp().raw_address());
    w5500.setGatewayIp(_dhcp->getGatewayIp().raw_address());
    w5500.setSubnetMask(_dhcp->getSubnetMask().raw_address());
    _dnsServerAddress = _dhcp->getDnsServerIp();
  }
  return ret;
}

void EthernetClass::begin(IPAddress local_ip)
{
  IPAddress subnet(255, 255, 255, 0);
  begin(local_ip, subnet);
}

void EthernetClass::begin(IPAddress local_ip, IPAddress subnet)
{
  // Assume the gateway will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress gateway = local_ip;
  gateway[3] = 1;
  begin(local_ip, subnet, gateway);
}

void EthernetClass::begin(IPAddress local_ip, IPAddress subnet, IPAddress gateway)
{
  // Assume the DNS server will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress dns_server = local_ip;
  dns_server[3] = 1;
  begin(local_ip, subnet, gateway, dns_server);
}

void EthernetClass::begin(IPAddress local_ip, IPAddress subnet, IPAddress gateway, IPAddress dns_server)
{
  w5500.init(_maxSockNum, _pinCS);
  w5500.setIPAddress(local_ip.raw_address());
  w5500.setGatewayIp(gateway.raw_address());
  w5500.setSubnetMask(subnet.raw_address());
  _dnsServerAddress = dns_server;
}

#else
int EthernetClass::begin(uint8_t *mac_address)
{
  // KH mod to work with new func void MACAddress(uint8_t *mac_address); and SinricPro v2.5.1+
  // Now store to private var
  //uint8_t _mac_address[6] ={0,};
  memcpy(_mac_address, mac_address, sizeof(_mac_address));
  //////
  
  _dhcp = new DhcpClass();
  // Initialise the basic info
  w5500.init(_maxSockNum, _pinCS);
  w5500.setMACAddress(mac_address);
  w5500.setIPAddress(IPAddress(0,0,0,0).raw_address());

  if (strlen(_customHostname) != 0)
  {
    _dhcp->setCustomHostname(_customHostname);
  }
  
  // Now try to get our config info from a DHCP server
  int ret = _dhcp->beginWithDHCP(mac_address);
  if(ret == 1)
  {
    // We've successfully found a DHCP server and got our configuration info, so set things
    // accordingly
    w5500.setIPAddress(_dhcp->getLocalIp().raw_address());
    w5500.setGatewayIp(_dhcp->getGatewayIp().raw_address());
    w5500.setSubnetMask(_dhcp->getSubnetMask().raw_address());
    _dnsServerAddress = _dhcp->getDnsServerIp();
  }

  return ret;
}

void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip)
{
  // KH mod to work with new func void MACAddress(uint8_t *mac_address); and SinricPro v2.5.1+
  // Now store to private var
  //uint8_t _mac_address[6] ={0,};
  memcpy(_mac_address, mac_address, sizeof(_mac_address));
  //////
  
  IPAddress subnet(255, 255, 255, 0);
  begin(mac_address, local_ip, subnet);
}

void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, IPAddress subnet)
{
  // KH mod to work with new func void MACAddress(uint8_t *mac_address); and SinricPro v2.5.1+
  // Now store to private var
  //uint8_t _mac_address[6] ={0,};
  memcpy(_mac_address, mac_address, sizeof(_mac_address));
  //////
  
  // Assume the gateway will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress gateway = local_ip;
  gateway[3] = 1;
  begin(mac_address, local_ip, subnet, gateway);
}

void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, IPAddress subnet, IPAddress gateway)
{
  // KH mod to work with new func void MACAddress(uint8_t *mac_address); and SinricPro v2.5.1+
  // Now store to private var
  //uint8_t _mac_address[6] ={0,};
  memcpy(_mac_address, mac_address, sizeof(_mac_address));
  //////
  
  // Assume the DNS server will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress dns_server = local_ip;
  dns_server[3] = 1;
  begin(mac_address, local_ip, subnet, gateway, dns_server);
}

void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, IPAddress subnet, IPAddress gateway, IPAddress dns_server)
{
  // KH mod to work with new func void MACAddress(uint8_t *mac_address); and SinricPro v2.5.1+
  // Now store to private var
  //uint8_t _mac_address[6] ={0,};
  memcpy(_mac_address, mac_address, sizeof(_mac_address));
  //////
  
  w5500.init(_maxSockNum, _pinCS);
  w5500.setMACAddress(mac_address);
  w5500.setIPAddress(local_ip.raw_address());
  w5500.setGatewayIp(gateway.raw_address());
  w5500.setSubnetMask(subnet.raw_address());
  _dnsServerAddress = dns_server;
}

#endif

int EthernetClass::maintain(){
  int rc = DHCP_CHECK_NONE;
  if(_dhcp != NULL){
    //we have a pointer to dhcp, use it
    rc = _dhcp->checkLease();
    switch ( rc ){
      case DHCP_CHECK_NONE:
        //nothing done
        break;
      case DHCP_CHECK_RENEW_OK:
      case DHCP_CHECK_REBIND_OK:
        //we might have got a new IP.
        w5500.setIPAddress(_dhcp->getLocalIp().raw_address());
        w5500.setGatewayIp(_dhcp->getGatewayIp().raw_address());
        w5500.setSubnetMask(_dhcp->getSubnetMask().raw_address());
        _dnsServerAddress = _dhcp->getDnsServerIp();
        break;
      default:
        //this is actually a error, it will retry though
        break;
    }
  }
  return rc;
}

void EthernetClass::WoL(bool wol) { 
  uint8_t val = w5500.readMR();
  bitWrite(val, 5, wol);
  w5500.writeMR(val);
  }

bool EthernetClass::WoL() {
  uint8_t val = w5500.readMR();
  return bitRead(val, 5);
  }

void EthernetClass::phyMode(phyMode_t mode) {
  uint8_t val = w5500.getPHYCFGR();
  bitWrite(val, 6, 1);
  if (mode == HALF_DUPLEX_10) {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 0);
    bitWrite(val, 5, 0);
    w5500.setPHYCFGR(val);
    }
  else if (mode == FULL_DUPLEX_10) {
    bitWrite(val, 3, 1);
    bitWrite(val, 4, 0);
    bitWrite(val, 5, 0);
    w5500.setPHYCFGR(val);
    }
  else if (mode == HALF_DUPLEX_100) {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 0);
    w5500.setPHYCFGR(val);
    }
  else if (mode == FULL_DUPLEX_100) {
    bitWrite(val, 3, 1);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 0);
    w5500.setPHYCFGR(val);
    }
  else if (mode == FULL_DUPLEX_100_AUTONEG) {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 0);
    bitWrite(val, 5, 1);
    w5500.setPHYCFGR(val);
    }
  else if (mode == POWER_DOWN) {
    bitWrite(val, 3, 0);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 1);
    w5500.setPHYCFGR(val);
    }
  else if (mode == ALL_AUTONEG) {
    bitWrite(val, 3, 1);
    bitWrite(val, 4, 1);
    bitWrite(val, 5, 1);
    w5500.setPHYCFGR(val);
    }
  bitWrite(val, 7, 0);
  w5500.setPHYCFGR(val);
  bitWrite(val, 7, 1);
  w5500.setPHYCFGR(val);
  }

void EthernetClass::setHostname(const char* hostname) {
  memset(_customHostname, 0, 32);
  memcpy((void*)_customHostname, (void*)hostname, strlen(hostname) >= 31 ? 31 : strlen(hostname));
  }

uint8_t EthernetClass::phyState() {
  return w5500.getPHYCFGR();
  }

uint8_t EthernetClass::link() {
  return bitRead(w5500.getPHYCFGR(), 0);
  }

const char* EthernetClass::linkReport() 
{
  if (bitRead(w5500.getPHYCFGR(), 0) == 1) 
    return "LINK";
  else 
    return "NO LINK";
  }

uint8_t EthernetClass::speed() 
{
  if (bitRead(w5500.getPHYCFGR(), 0) == 1) 
  {
    if (bitRead(w5500.getPHYCFGR(), 1) == 1) 
      return 100;
      
    if (bitRead(w5500.getPHYCFGR(), 1) == 0) 
      return 10;
  }

  return 0;
}

const char* EthernetClass::speedReport() 
{
  if (bitRead(w5500.getPHYCFGR(), 0) == 1) 
  {
    if (bitRead(w5500.getPHYCFGR(), 1) == 1) 
      return "100 MB";
      
    if (bitRead(w5500.getPHYCFGR(), 1) == 0) 
      return "10 MB";
  }

  return "NO LINK";
}

uint8_t EthernetClass::duplex() 
{
  if(bitRead(w5500.getPHYCFGR(), 0) == 1) 
  {
    if (bitRead(w5500.getPHYCFGR(), 2) == 1) 
      return 2;
      
    if (bitRead(w5500.getPHYCFGR(), 2) == 0) 
      return 1;
  }

  return 0;
}

const char* EthernetClass::duplexReport() 
{
  if (bitRead(w5500.getPHYCFGR(), 0) == 1) 
  {
    if(bitRead(w5500.getPHYCFGR(), 2) == 1) 
      return "FULL DUPLEX";
      
    if (bitRead(w5500.getPHYCFGR(), 2) == 0) 
      return "HALF DUPLEX";
  }

  return "NO LINK";
}

void EthernetClass::setRtTimeOut(uint16_t timeout) {
  w5500.setRetransmissionTime(timeout);
  }

uint16_t EthernetClass::getRtTimeOut() {
  return w5500.getRetransmissionTime();
  }

void EthernetClass::setRtCount(uint8_t count) {
  w5500.setRetransmissionCount(count);
  }

uint8_t EthernetClass::getRtCount() {
  return w5500.getRetransmissionCount();
  }

void EthernetClass::macAddress(uint8_t mac[]) {
  w5500.getMACAddress(mac);
  }

const char* EthernetClass::macAddressReport() {
  uint8_t mac[6];
  static char str[18];
  w5500.getMACAddress(mac);
  sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return str;
  }

IPAddress EthernetClass::localIP()
{
  IPAddress ret;
  w5500.getIPAddress(ret.raw_address());
  return ret;
}

IPAddress EthernetClass::subnetMask()
{
  IPAddress ret;
  w5500.getSubnetMask(ret.raw_address());
  return ret;
}

IPAddress EthernetClass::gatewayIP()
{
  IPAddress ret;
  w5500.getGatewayIp(ret.raw_address());
  return ret;
}

IPAddress EthernetClass::dnsServerIP()
{
  return _dnsServerAddress;
}

EthernetClass Ethernet;
