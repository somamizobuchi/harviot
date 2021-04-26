#include "Harviot.hpp"
#include <ArduinoJson.h>

Harviot::Harviot(const char *plant_id, const char *password):
    plant_id(plant_id),
    password(password){

}

void Harviot::init(){
    requestAuthToken();
    wsConnect();
}

void Harviot::requestAuthToken(){
    // Headers to collect
    const char *headerKeys[] = {
        "Set-Cookie"
    };
    size_t headerKeysCount = sizeof(headerKeys) / sizeof(char *);
    String cookie;
    // Set headers
    char contentType[] = "application/json";
    // POST body
    const size_t doc_size = 1024;
    char post_body_cstr[doc_size];
    DynamicJsonDocument post_body(doc_size);
    post_body["_id"] = plant_id;
    post_body["password"] = password;
    serializeJson(post_body, post_body_cstr);
    // Begin the request
    http_client.begin(AUTH_URI);
    http_client.collectHeaders(headerKeys, headerKeysCount);
    http_client.addHeader(HTTP_HEADER_CONTENT_TYPE, contentType);
    // Make post request
    if(http_client.POST(post_body_cstr) == HTTP_CODE_OK){
        cookie = http_client.header("Set-Cookie");
        int first = cookie.indexOf("auth=");
        int last = cookie.indexOf(";", first);
        cookie = cookie.substring(first, last);
    }
    // end
    http_client.end();
    auth_token = cookie.c_str();
}

const char * Harviot::getAuthToken(){
    return auth_token;
}

void Harviot::wsConnect(){
    // Set cookie
    ws.addHeader("Cookie", auth_token);
    // configure url
    const char * ws_uri_base = WS_URI_BASE;
    char * ws_uri = (char *)malloc(sizeof(char) * (strlen(ws_uri_base) + strlen(plant_id) + 1));
    strcpy(ws_uri, ws_uri_base);
    strcat(ws_uri, plant_id);
    // define event callback
    ws.onEvent([&](websockets::WebsocketsEvent e, String data){
        using namespace websockets;
        switch (e)
        {
            case(WebsocketsEvent::ConnectionOpened):
                Serial.println("Connnection Opened");
                break;
            case(WebsocketsEvent::ConnectionClosed):
                Serial.println("Connnection Closed");
                break;
            case(WebsocketsEvent::GotPing):
                Serial.println("Got Ping!");
                break;
            case(WebsocketsEvent::GotPong):
                Serial.println("Got Pong!");
                break;
            default:
                break;
        }
    });
    // Connect
    ws.connect(ws_uri);
}

void Harviot::poll(){
    if(ws.available()){
        ws.poll();
    }
}

void Harviot::wsOnMessage(void (*f)(websockets::WebsocketsMessage)){
    ws.onMessage(f);
}