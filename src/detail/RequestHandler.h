/****************************************************************************************************************************
 * RequestHandler.h - Dead simple web-server.
 * For Ethernet shields
 *
 * EthernetWebServer is a library for the Ethernet shields to run WebServer
 *
 * Forked and modified from ESP8266 https://github.com/esp8266/Arduino/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
 * Licensed under MIT license
 * Version: 1.0.0
 *
 * Original author:
 * @file       Esp8266WebServer.h
 * @author     Ivan Grokhotkov
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc
 *****************************************************************************************************************************/

#ifndef RequestHandler_h
#define RequestHandler_h

class RequestHandler {
public:
    virtual ~RequestHandler() { }
    virtual bool canHandle(HTTPMethod method, String uri) { return false; }
    virtual bool canUpload(String uri) { return false; }
    virtual bool handle(EthernetWebServer& server, HTTPMethod requestMethod, String requestUri) { return false; }
    virtual void upload(EthernetWebServer& server, String requestUri, HTTPUpload& upload) {}

    RequestHandler* next() { return _next; }
    void next(RequestHandler* r) { _next = r; }

private:
    RequestHandler* _next = nullptr;
};

#endif //RequestHandler_h
