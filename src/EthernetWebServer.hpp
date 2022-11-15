/****************************************************************************************************************************
  EthernetWebServer.h - Dead simple web-server.
  For Ethernet shields

  EthernetWebServer is a library for the Ethernet shields to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov

  Version: 2.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
  ...
  2.0.0   K Hoang      16/01/2022 To coexist with ESP32 WebServer and ESP8266 ESP8266WebServer
  2.0.1   K Hoang      02/03/2022 Fix decoding error bug
  2.0.2   K Hoang      14/03/2022 Fix bug when using QNEthernet staticIP. Add staticIP option to NativeEthernet
  2.1.0   K Hoang      03/04/2022 Use Ethernet_Generic library as default. Support SPI2 for ESP32
  2.1.1   K Hoang      04/04/2022 Fix compiler error for Portenta_H7 using Portenta Ethernet
  2.1.2   K Hoang      08/04/2022 Add support to SPI1 for RP2040 using arduino-pico core
  2.1.3   K Hoang      27/04/2022 Change from `arduino.cc` to `arduino.tips` in examples
  2.2.0   K Hoang      05/05/2022 Add support to custom SPI for Teensy, Mbed RP2040, Portenta_H7, etc.
  2.2.1   K Hoang      25/08/2022 Auto-select SPI SS/CS pin according to board package
  2.2.2   K Hoang      06/09/2022 Slow SPI clock for old W5100 shield or SAMD Zero. Improve support for SAMD21
  2.2.3   K Hoang      17/09/2022 Add support to AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  2.2.4   K Hoang      26/10/2022 Add support to Seeed XIAO_NRF52840 and XIAO_NRF52840_SENSE using `mbed` or `nRF52` core
  2.3.0   K Hoang      15/11/2022 Add new features, such as CORS. Update code and examples to send big data
 *************************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_WEBSERVER_HPP
#define ETHERNET_WEBSERVER_HPP

/////////////////////////////////////////////////////////////////////////

#define USE_NEW_WEBSERVER_VERSION       true

#include <functional-vlpp.h>

/////////////////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #if defined(ETHERNET_USE_PORTENTA_H7)
    #undef ETHERNET_USE_PORTENTA_H7
  #endif
  #define ETHERNET_USE_PORTENTA_H7        true
  
  #if defined(USE_NEW_WEBSERVER_VERSION)
    #undef USE_NEW_WEBSERVER_VERSION
  #endif
  #define USE_NEW_WEBSERVER_VERSION   false
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Use mbed-portenta architecture for PORTENTA_H7 from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(ETHERNET_USE_SAMD)
    #undef ETHERNET_USE_SAMD
  #endif
  #define ETHERNET_USE_SAMD      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using SAMD architecture from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if (defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
     defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || \
     defined(NRF52840_CLUE) || defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || \
     defined(NRF52840_LED_GLASSES) || defined(MDBT50Q_RX) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) || \
     defined(ARDUINO_Seeed_XIAO_nRF52840) || defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) || \
     defined(ARDUINO_SEEED_XIAO_NRF52840) || defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE) )
  #if defined(ETHERNET_USE_NRF528XX)
    #undef ETHERNET_USE_NRF528XX
  #endif
  #define ETHERNET_USE_NRF528XX      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using nFR52 architecture from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ETHERNET_USE_SAM_DUE)
    #undef ETHERNET_USE_SAM_DUE
  #endif
  #define ETHERNET_USE_SAM_DUE      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using SAM_DUE architecture from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if ( defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || \
      defined(__AVR_ATmega640__) || defined(__AVR_ATmega641__))
  #if defined(ETHERNET_USE_AVR_MEGA)
    #undef ETHERNET_USE_AVR_MEGA
  #endif
  #define ETHERNET_USE_AVR_MEGA      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using AVR_MEGA architecture from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if defined(DXCORE)
  #if defined(ETHERNET_USE_DXCORE)
    #undef ETHERNET_USE_DXCORE
  #endif
  #define ETHERNET_USE_DXCORE      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using DXCORE architecture from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if ( defined(__AVR_ATmega4809__) || defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_AVR_NANO_EVERY) )

  #if defined(ETHERNET_USE_MEGA_AVR)
    #undef ETHERNET_USE_MEGA_AVR
  #endif
  #define ETHERNET_USE_MEGA_AVR      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using MEGA_AVR architecture from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if defined(ESP32)

  #if defined(ETHERNET_USE_ESP)
    #undef ETHERNET_USE_ESP32
  #endif
  #define ETHERNET_USE_ESP32        true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using ESP32 architecture from EthernetWebServer
  #endif
  
#endif

/////////////////////////////////////////////////////////////////////////

#if defined(ESP8266)

  #if defined(ETHERNET_USE_ESP8266)
    #undef ETHERNET_USE_ESP8266
  #endif
  #define ETHERNET_USE_ESP8266      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning Using ESP8266 architecture from EthernetWebServer
  #endif

#endif

/////////////////////////////////////////////////////////////////////////

#if USE_UIP_ETHERNET
  #include <UIPEthernet.h>
  #include <utility/logging.h>
#elif USE_CUSTOM_ETHERNET
  // Do nothing here
#elif !( ETHERNET_USE_PORTENTA_H7 || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC || \
         USE_NATIVE_ETHERNET || USE_QN_ETHERNET)
  #include <Ethernet_Generic.hpp>
#endif

/////////////////////////////////////////////////////////////////////////

#include "detail/mimetable.h"

// KH, For PROGMEM commands
// ESP32/ESP8266 includes <pgmspace.h> by default, and memccpy_P was already defined there
#if !( defined(ESP32) || defined(ESP8266) )
  #include <avr/pgmspace.h>
  #define memccpy_P(dest, src, c, n) memccpy((dest), (src), (c), (n))
#endif

/////////////////////////////////////////////////////////////////////////

// Permit redefinition of SENDCONTENT_P_BUFFER_SZ in sketch, default is 4K, minimum is 256 bytes
#ifndef SENDCONTENT_P_BUFFER_SZ
  #define SENDCONTENT_P_BUFFER_SZ     4096
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
  	#warning SENDCONTENT_P_BUFFER_SZ using default 4 Kbytes
  #endif
#else
  #if (SENDCONTENT_P_BUFFER_SZ < 256)
    #undef SENDCONTENT_P_BUFFER_SZ
    #define SENDCONTENT_P_BUFFER_SZ   256
    
    #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
    	#warning SENDCONTENT_P_BUFFER_SZ reset to min 256 bytes
    #endif
  #endif
#endif

#ifndef PGM_VOID_P
  #define PGM_VOID_P const void *
#endif

/////////////////////////////////////////////////////////////////////////

// New definitions only when not using ESP32 WebServer.h
#if !(( defined(ESP32) || defined(ESP8266) ) && (__has_include("WebServer.h") || __has_include("ESP8266WebServer.h")) )

  enum HTTPMethod
  {
    HTTP_ANY,
    HTTP_GET,
    HTTP_HEAD,
    HTTP_POST,
    HTTP_PUT,
    HTTP_PATCH,
    HTTP_DELETE,
    HTTP_OPTIONS
  };
  
  enum HTTPUploadStatus
  {
    UPLOAD_FILE_START,
    UPLOAD_FILE_WRITE,
    UPLOAD_FILE_END,
    UPLOAD_FILE_ABORTED
  };
  
  enum HTTPClientStatus
  {
    HC_NONE,
    HC_WAIT_READ,
    HC_WAIT_CLOSE
  };
  
  enum HTTPAuthMethod
  {
    BASIC_AUTH,
    DIGEST_AUTH
  };
  
  #if defined(HTTP_DOWNLOAD_UNIT_SIZE)
    #undef HTTP_DOWNLOAD_UNIT_SIZE
    #define HTTP_DOWNLOAD_UNIT_SIZE 1460
  #endif
  
  // Permit user to increase HTTP_UPLOAD_BUFLEN larger than default 2K
  //#define HTTP_UPLOAD_BUFLEN 2048
  #if !defined(HTTP_UPLOAD_BUFLEN)
    #define HTTP_UPLOAD_BUFLEN 4096   //2048
  #endif
  
  #define HTTP_MAX_DATA_WAIT      3000 //ms to wait for the client to send the request
  #define HTTP_MAX_POST_WAIT      3000 //ms to wait for POST data to arrive
  #define HTTP_MAX_SEND_WAIT      3000 //ms to wait for data chunk to be ACKed
  #define HTTP_MAX_CLOSE_WAIT     2000 //ms to wait for the client to close the connection

#else
	#if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 3)
		#if defined(ESP32)
		  #warning ESP32 __has_include WebServer.h
		#else
		  #warning ESP8266 __has_include ESP8266WebServer.h
		#endif
  #endif

#endif    // #if !(( defined(ESP32) || defined(ESP8266)) && (__has_include("WebServer.h") || __has_include("ESP8266WebServer.h")) )

/////////////////////////////////////////////////////////////////////////

#define CONTENT_LENGTH_UNKNOWN  ((size_t) -1)
#define CONTENT_LENGTH_NOT_SET  ((size_t) -2)

/////////////////////////////////////////////////////////////////////////

#define RETURN_NEWLINE       "\r\n"

#include <Arduino.h>

#if ( ETHERNET_USE_AVR_MEGA || ETHERNET_USE_MEGA_AVR || ETHERNET_USE_DXCORE )
  typedef String EWString;
#else
  #include <string>
  typedef std::string EWString;
#endif

/////////////////////////////////////////////////////////////////////////

class EthernetWebServer;

typedef struct
{
  HTTPUploadStatus status;
  String  filename;
  String  name;
  String  type;
  size_t  totalSize;      // file size
  size_t  currentSize;    // size of data currently in buf
  size_t  contentLength;  // size of entire post request, file size + headers and other request data.
  uint8_t buf[HTTP_UPLOAD_BUFLEN];
} ethernetHTTPUpload;

#include "detail/RequestHandler.h"

#if (defined(ESP32) || defined(ESP8266))
  #include "FS.h"
#endif

/////////////////////////////////////////////////////////////////////////

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
    void addHandler(ethernetRequestHandler* handler);
    void onNotFound(THandlerFunction fn);  //called when handler is not assigned
    void onFileUpload(THandlerFunction fn); //handle file uploads

    String uri()
    {
      return _currentUri;
    }

    HTTPMethod method()
    {
      return _currentMethod;
    }

    EthernetClient client()
    {
      return _currentClient;
    }

#if USE_NEW_WEBSERVER_VERSION
    ethernetHTTPUpload& upload()
    {
      return *_currentUpload;
    }
#else
    ethernetHTTPUpload& upload()
    {
      return _currentUpload;
    }
#endif

    String arg(const String& name);        // get request argument value by name
    String arg(int i);              // get request argument value by number
    String argName(int i);          // get request argument name by number

    int args();                     // get arguments count
    bool hasArg(const String& name);       // check if argument exists
    void collectHeaders(const char* headerKeys[], const size_t headerKeysCount); // set the request headers to collect
    String header(const String& name);      // get request header value by name
    String header(int i);              // get request header value by number
    String headerName(int i);          // get request header name by number
    int headers();                     // get header count
    bool hasHeader(const String& name);       // check if header exists

    String hostHeader();            // get request host header if available or empty String if not

    // send response to the client
    // code - HTTP response code, can be 200 or 404
    // content_type - HTTP content type, like "text/plain" or "image/png"
    // content - actual content body
    void send(int code, const char* content_type = NULL, const String& content = String(""));
    void send(int code, char* content_type, const String& content);
    void send(int code, const String& content_type, const String& content);

    void send(int code, char* content_type, const String& content, size_t contentLength);
    void send(int code, const char* content_type, const char* content);
    void send(int code, const char* content_type, const char* content, size_t contentLength);

		////////////////////////////////////////
    
    inline void enableDelay(bool value)
    {
    	_nullDelay = value;
    }

		////////////////////////////////////////
        
		inline void enableCORS(bool value = true) 
		{
  		_corsEnabled = value;
		}

		////////////////////////////////////////
    
		inline void enableCrossOrigin(bool value = true) 
		{
			enableCORS(value);
		}

		////////////////////////////////////////
		
    void setContentLength(size_t contentLength);
    void sendHeader(const String& name, const String& value, bool first = false);
    //void sendHeader(const EWString& name, const EWString& value, bool first = false);
    void sendContent(const String& content);
    void sendContent(const String& content, size_t size);

		// New
    void sendContent(const char* content, size_t contentLength);
    //////
    
    // KH, Restore PROGMEM commands
    void send_P(int code, PGM_P content_type, PGM_P content);
    void send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength);

    void sendContent_P(PGM_P content);
    void sendContent_P(PGM_P content, size_t size);
    //////

    static String urlDecode(const String& text);

#if !(defined(ESP32) || defined(ESP8266))
    template<typename T> size_t streamFile(T &file, const String& contentType)
    {
      using namespace mime;
      setContentLength(file.size());

      if (String(file.name()).endsWith(mimeTable[gz].endsWith) && contentType != mimeTable[gz].mimeType &&
          contentType != mimeTable[none].mimeType)
      {
        sendHeader("Content-Encoding", "gzip");
      }

      send(200, contentType, "");

      return _currentClient.write(file);
    }

		////////////////////////////////////////
        
#else

		////////////////////////////////////////
    
    // serve static pages from file system
    void serveStatic(const char* uri, fs::FS& fs, const char* path, const char* cache_header = NULL ); 

    // Handle a GET request by sending a response header and stream file content to response body
    //template<typename T> 
    //size_t streamFile(T &file, const String& contentType)
    //{
    //  return streamFile(file, contentType, HTTP_GET);
    //}

    // Implement GET and HEAD requests for files.
    // Stream body on HTTP_GET but not on HTTP_HEAD requests.
    template<typename T> 
    size_t streamFile(T &file, const String& contentType, const int code = 200)
      {
				_streamFileCore(file.size(), file.name(), contentType, code);
				
    		return _currentClient.write(file);     
      }

		////////////////////////////////////////
            
#endif

  protected:
  
  	////////////////////////////////////////
  
		virtual size_t _currentClientWrite(const char* buffer, size_t length) 
		{ 
			return _currentClient.write( buffer, length ); 
		}

		////////////////////////////////////////
	
    void _addRequestHandler(ethernetRequestHandler* handler);
    void _handleRequest();
    void _finalizeResponse();
    bool _parseRequest(EthernetClient& client);

    //KH
#if USE_NEW_WEBSERVER_VERSION
    void _parseArguments(const String& data);
    int  _parseArgumentsPrivate(const String& data, vl::Func<void(String&, String&, const String&, int, int, int, int)> handler);
    bool _parseForm(EthernetClient& client, const String& boundary, uint32_t len);
#else
    void _parseArguments(const String& data);
    bool _parseForm(EthernetClient& client, const String& boundary, uint32_t len);
#endif

    static String _responseCodeToString(int code);
    bool _parseFormUploadAborted();
    void _uploadWriteByte(uint8_t b);
    uint8_t _uploadReadByte(EthernetClient& client);
    void _prepareHeader(String& response, int code, const char* content_type, size_t contentLength);

#if ! ( ETHERNET_USE_AVR_MEGA || ETHERNET_USE_MEGA_AVR || ETHERNET_USE_DXCORE )
    void _prepareHeader(EWString& response, int code, const char* content_type, size_t contentLength);
#endif
    bool _collectHeader(const char* headerName, const char* headerValue);

#if (defined(ESP32) || defined(ESP8266))
    void _streamFileCore(const size_t fileSize, const String & fileName, const String & contentType, const int code = 200);

    template<typename T>
    size_t _customClientWrite(T &file)
    {
      char buffer[256];
      size_t contentLength = 0;
      size_t bytesRead = 0;

      // read up to sizeof(buffer) bytes
      while ((bytesRead = file.readBytes(buffer, sizeof(buffer))) > 0)
      {
        _currentClient.write(buffer, bytesRead);
        contentLength += bytesRead;
      }

      return contentLength;
    }
#endif

    struct RequestArgument
    {
      String key;
      String value;
    };
    
    bool    					_corsEnabled;

    EthernetServer  	_server;

    EthernetClient    _currentClient;
    HTTPMethod        _currentMethod;
    String            _currentUri;
    uint8_t           _currentVersion;
    HTTPClientStatus  _currentStatus;
    unsigned long     _statusChange;
    
    bool     					_nullDelay;

    ethernetRequestHandler*   _currentHandler   = nullptr;
    ethernetRequestHandler*   _firstHandler   	= nullptr;
    ethernetRequestHandler*   _lastHandler   		= nullptr;
    THandlerFunction  				_notFoundHandler;
    THandlerFunction  				_fileUploadHandler;

    int               _currentArgCount;
    RequestArgument*  _currentArgs   						= nullptr;

    //KH
#if USE_NEW_WEBSERVER_VERSION
    ethernetHTTPUpload*   _currentUpload   			= nullptr;
    int                   _postArgsLen;
    RequestArgument*      _postArgs   					= nullptr;
#else
    ethernetHTTPUpload    _currentUpload;
#endif

    int               _headerKeysCount;
    RequestArgument*  _currentHeaders   				= nullptr;
    size_t            _contentLength;
    int              	_clientContentLength;				// "Content-Length" from header of incoming POST or GET request
    String            _responseHeaders;
    String            _hostHeader;
    bool              _chunked;
};

/////////////////////////////////////////////////////////////////////////

#endif  // ETHERNET_WEBSERVER_HPP
