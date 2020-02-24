/****************************************************************************************************************************
 * EthernetWebServer.h - Dead simple web-server.
 * For Ethernet shields
 *
 * EthernetWebServer is a library for the Ethernet shields to run WebServer
 *
 * Forked and modified from ESP8266 https://github.com/esp8266/Arduino/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
 * Licensed under MIT license
 * Version: 1.0.3
 *
 * Original author:
 * @file       Esp8266WebServer.h
 * @author     Ivan Grokhotkov
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
 *  1.0.1   K Hoang      20/02/2020 Add support to lambda functions
 *  1.0.2   K Hoang      20/02/2020 Add support to UIPEthernet library for ENC28J60
 *  1.0.3   K Hoang      23/02/2020 Add support to SAM DUE / SAMD boards
 *****************************************************************************************************************************/

#ifndef EthernetWebServer_h
#define EthernetWebServer_h

#include <functional-vlpp.h>

#if    ( defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAM3X8E__) || defined(__CPU_ARC__) )      
  #if defined(ESP8266_AT_USE_SAMD)
    #undef ETHERNET_USE_SAMD
  #endif
  #define ETHERNET_USE_SAMD      true
#endif

#ifndef USE_UIP_ETHERNET
// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)
#define USE_UIP_ETHERNET   false
#endif

#if USE_UIP_ETHERNET
#include <UIPEthernet.h>
#include <utility/logging.h>
#else
#include <Ethernet.h>
#endif

enum HTTPMethod { HTTP_ANY, HTTP_GET, HTTP_POST, HTTP_PUT, HTTP_PATCH, HTTP_DELETE, HTTP_OPTIONS };
enum HTTPUploadStatus { UPLOAD_FILE_START, UPLOAD_FILE_WRITE, UPLOAD_FILE_END,
                        UPLOAD_FILE_ABORTED };
enum HTTPClientStatus { HC_NONE, HC_WAIT_READ, HC_WAIT_CLOSE };

#define HTTP_DOWNLOAD_UNIT_SIZE 1460

#define HTTP_UPLOAD_BUFLEN 2048

#define HTTP_MAX_DATA_WAIT 1000 //ms to wait for the client to send the request
#define HTTP_MAX_POST_WAIT 1000 //ms to wait for POST data to arrive
#define HTTP_MAX_SEND_WAIT 5000 //ms to wait for data chunk to be ACKed
#define HTTP_MAX_CLOSE_WAIT 2000 //ms to wait for the client to close the connection

#define CONTENT_LENGTH_UNKNOWN ((size_t) -1)
#define CONTENT_LENGTH_NOT_SET ((size_t) -2)

class EthernetWebServer;

typedef struct {
  HTTPUploadStatus status;
  String  filename;
  String  name;
  String  type;
  size_t  totalSize;    // file size
  size_t  currentSize;  // size of data currently in buf
  uint8_t buf[HTTP_UPLOAD_BUFLEN];
} HTTPUpload;

#include "detail/RequestHandler.h"

class EthernetWebServer
{
public:
  EthernetWebServer(int port = 80);
  ~EthernetWebServer();

  void begin();
  void handleClient();

  void close();
  void stop();

  bool authenticate(const char * username, const char * password);
  void requestAuthentication();

  typedef vl::Func<void(void)> THandlerFunction;
  //typedef std::function<void(void)> THandlerFunction;
  //typedef void (*THandlerFunction)(void);
  
  void on(const String &uri, THandlerFunction handler);
  void on(const String &uri, HTTPMethod method, THandlerFunction fn);
  void on(const String &uri, HTTPMethod method, THandlerFunction fn, THandlerFunction ufn);
  void addHandler(RequestHandler* handler);
  void onNotFound(THandlerFunction fn);  //called when handler is not assigned
  void onFileUpload(THandlerFunction fn); //handle file uploads

  String uri() { return _currentUri; }
  HTTPMethod method() { return _currentMethod; }
  EthernetClient client() { return _currentClient; }
  HTTPUpload& upload() { return _currentUpload; }

  String arg(String name);        // get request argument value by name
  String arg(int i);              // get request argument value by number
  String argName(int i);          // get request argument name by number
  int args();                     // get arguments count
  bool hasArg(String name);       // check if argument exists
  void collectHeaders(const char* headerKeys[], const size_t headerKeysCount); // set the request headers to collect
  String header(String name);      // get request header value by name
  String header(int i);              // get request header value by number
  String headerName(int i);          // get request header name by number
  int headers();                     // get header count
  bool hasHeader(String name);       // check if header exists

  String hostHeader();            // get request host header if available or empty String if not

  // send response to the client
  // code - HTTP response code, can be 200 or 404
  // content_type - HTTP content type, like "text/plain" or "image/png"
  // content - actual content body
  void send(int code, const char* content_type = NULL, const String& content = String(""));
  void send(int code, char* content_type, const String& content);
  void send(int code, const String& content_type, const String& content);
  //KH
  void send(int code, char*  content_type, const String& content, size_t contentLength);
  
  #if !( defined(CORE_TEENSY) || ETHERNET_USE_SAMD )
  void send_P(int code, PGM_P content_type, PGM_P content);
  void send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength);
  #endif

  void setContentLength(size_t contentLength);
  void sendHeader(const String& name, const String& value, bool first = false);
  void sendContent(const String& content);
  void sendContent(const String& content, size_t size);
  void sendContent_P(PGM_P content);
  void sendContent_P(PGM_P content, size_t size);
  
  static String urlDecode(const String& text);

template<typename T> size_t streamFile(T &file, const String& contentType){
  setContentLength(file.size());
  if (String(file.name()).endsWith(".gz") &&
      contentType != "application/x-gzip" &&
      contentType != "application/octet-stream"){
    sendHeader("Content-Encoding", "gzip");
  }
  send(200, contentType, "");
  return _currentClient.write(file);
}

protected:
  void _addRequestHandler(RequestHandler* handler);
  void _handleRequest();
  bool _parseRequest(EthernetClient& client);
  void _parseArguments(String data);
  static String _responseCodeToString(int code);
  bool _parseForm(EthernetClient& client, String boundary, uint32_t len);
  bool _parseFormUploadAborted();
  void _uploadWriteByte(uint8_t b);
  uint8_t _uploadReadByte(EthernetClient& client);
  void _prepareHeader(String& response, int code, const char* content_type, size_t contentLength);
  bool _collectHeader(const char* headerName, const char* headerValue);

  struct RequestArgument {
    String key;
    String value;
  };

  EthernetServer  _server;

  EthernetClient  _currentClient;
  HTTPMethod  _currentMethod;
  String      _currentUri;
  uint8_t     _currentVersion;
  HTTPClientStatus _currentStatus;
  unsigned long _statusChange;

  RequestHandler*  _currentHandler;
  RequestHandler*  _firstHandler;
  RequestHandler*  _lastHandler;
  THandlerFunction _notFoundHandler;
  THandlerFunction _fileUploadHandler;

  int              _currentArgCount;
  RequestArgument* _currentArgs;
  HTTPUpload       _currentUpload;

  int              _headerKeysCount;
  RequestArgument* _currentHeaders;
  size_t           _contentLength;
  String           _responseHeaders;

  String           _hostHeader;
  bool             _chunked;

};

#include "EthernetWebServer-impl.h"
#include "Parsing-impl.h"


#endif //EthernetWebServer_H
