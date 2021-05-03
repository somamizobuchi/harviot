#include "Harviot.hpp"
#include <ArduinoJson.h>
#include <time.h>

Harviot::Harviot(const char *plant_id, const char *password):
    plant_id(plant_id), password(password)
    {
        // Sychronize the time with npt_server
        configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
        // configure url
        const char * ws_uri_base = WS_URI_BASE;
        ws_uri = (char *)malloc(sizeof(char) * (strlen(ws_uri_base) + strlen(plant_id) + 1));
        strcpy(ws_uri, ws_uri_base);
        strcat(ws_uri, plant_id);

    }

void Harviot::init(){
    initCamera();
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
    auth_token = cookie;
}

String Harviot::getAuthToken(){
    return auth_token;
}

void Harviot::wsConnect(){
    // Set cookie
    ws.addHeader("Cookie", auth_token);
    // Connect
    ws.connect(ws_uri);
    // define event callback
    ws.onEvent([&](websockets::WebsocketsEvent event, String data){
        using namespace websockets;
        switch (event)
        {
            case WebsocketsEvent::ConnectionOpened:
                Serial.println("Websocket connnection opened");
                break;
            case WebsocketsEvent::ConnectionClosed:
                Serial.println("Websocket connnection closed");
                return;
            case WebsocketsEvent::GotPing:
                Serial.println("Got Ping!");
                break;
            case WebsocketsEvent::GotPong:
                Serial.println("Got Pong!");
                break;
            default:
                break;
        }
    });
}

void Harviot::poll(){
    if(ws.available()){
        ws.poll();
    } else {
        ws.connect(ws_uri);
    }
}

void Harviot::wsOnMessage(void (*f)(websockets::WebsocketsMessage)){
    ws.onMessage(f);
}
void Harviot::WsSendBinary(const char * data, size_t size){
    ws.sendBinary(data, size);
}

void Harviot::initCamera(){
    // Configure camera
    camera_config.ledc_channel = LEDC_CHANNEL_0;
    camera_config.ledc_timer = LEDC_TIMER_0;
    camera_config.pin_d0 = Y2_GPIO_NUM;
    camera_config.pin_d1 = Y3_GPIO_NUM;
    camera_config.pin_d2 = Y4_GPIO_NUM;
    camera_config.pin_d3 = Y5_GPIO_NUM;
    camera_config.pin_d4 = Y6_GPIO_NUM;
    camera_config.pin_d5 = Y7_GPIO_NUM;
    camera_config.pin_d6 = Y8_GPIO_NUM;
    camera_config.pin_d7 = Y9_GPIO_NUM;
    camera_config.pin_xclk = XCLK_GPIO_NUM;
    camera_config.pin_pclk = PCLK_GPIO_NUM;
    camera_config.pin_vsync = VSYNC_GPIO_NUM;
    camera_config.pin_href = HREF_GPIO_NUM;
    camera_config.pin_sscb_sda = SIOD_GPIO_NUM;
    camera_config.pin_sscb_scl = SIOC_GPIO_NUM;
    camera_config.pin_pwdn = PWDN_GPIO_NUM;
    camera_config.pin_reset = RESET_GPIO_NUM;
    camera_config.xclk_freq_hz = 20000000;
    camera_config.pixel_format = PIXFORMAT_JPEG;
    camera_config.frame_size = FRAMESIZE_QVGA;
    camera_config.jpeg_quality = 9;
    camera_config.fb_count = 1;
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
}

bool Harviot::captureFrame(void (*f)(camera_fb_t *)){
    fb = esp_camera_fb_get();
    if(!fb){
        Serial.println("Frame buffer could not be acquired");
    } else {
        (*f)(fb);
    }
    esp_camera_fb_return(fb);
    return true;
}

bool Harviot::logData(const float *data){
    DynamicJsonDocument doc(1024);
    char post_body[1024];
    char buf[sizeof "YYYY-MM-DDT00:00:00Z"];
    time_t now;
    time(&now);
    localtime(&now);
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    doc["date"] = buf;
    doc["sensorValues"]["temperature"] = data[0];
    doc["sensorValues"]["humidity"] = data[1];
    doc["sensorValues"]["ambient_light"] = data[2];
    doc["sensorValues"]["ph"] = data[3];
    http_client.begin("http://api.harviot.com/plants/logs");
    http_client.addHeader(HTTP_HEADER_CONTENT_TYPE, "application/json");
    http_client.addHeader("Cookie", auth_token);
    serializeJson(doc, post_body);
    if(http_client.POST(post_body) != HTTP_CODE_OK){
        return false;
    }
    http_client.end();
    return true;
}

