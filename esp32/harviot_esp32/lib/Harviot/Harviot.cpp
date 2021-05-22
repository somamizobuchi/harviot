#include "Harviot.hpp"
#include <ArduinoJson.h>
#include <time.h>

namespace Harviot {
    /**
     * @brief Plant namespace
     * 
     */
    namespace Plant {
        /**
         * @brief Returns the temperature
         * 
         * @return float the temperature
         */
        float Plant::getAmbientLight() { return m_ambient_light; }

        /**
         * @brief Returns the humidity
         * 
         * @return float the humidity
         */
        float Plant::getHumidity() { return m_humidity; }

        /**
         * @brief Returns the PH level
         * 
         * @return float the PH level (0 - 14)
         */
        float Plant::getPh() { return m_ph; }

        /**
         * @brief Returns the temperature
         * 
         * @return float the temperature in celcius
         */
        float Plant::getTemperature() { return m_temperature; }
    };

    /**
     * @brief Web
     * 
     */
    namespace Web {
    };
}
Harviot::Harviot(const char *plant_id, const char *password):
    plant_id(plant_id), password(password)
    {
        const char *ntp_server = "pool.ntp.org";
        const long gmt_offset_sec = 14400;
        const int daylight_offset_sec = 3600;
        // Sychronize the time with npt_server
        configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
    }

void Harviot::init(){
    initCamera();
    requestAuthToken();
}

void Harviot::requestAuthToken(){
    WiFiClientSecure *client = new WiFiClientSecure;
    if(client){
        client->setCACert(ssl_ca_cert);
        HTTPClient http_client;
        StaticJsonDocument<256> login_json;
        // Headers to collect
        const char *headerKeys[] = {
            "Set-Cookie"};
        size_t headerKeysCount = sizeof(headerKeys) / sizeof(char *);
        String cookie;
        // POST body
        const size_t doc_size = 256;
        char post_body_cstr[doc_size];
        login_json["_id"] = plant_id;
        login_json["password"] = password;
        serializeJson(login_json, post_body_cstr);
        // Begin the request
        http_client.begin(AUTH_URI);
        http_client.collectHeaders(headerKeys, headerKeysCount);
        http_client.addHeader(HTTP_HEADER_CONTENT_TYPE, "application/json");
        // Make post request
        while (http_client.POST(post_body_cstr) != HTTP_CODE_OK)
        {
            delay(5000);
        }
        cookie = http_client.header("Set-Cookie");
        int first = cookie.indexOf("auth=");
        int last = cookie.indexOf(";", first);
        cookie = cookie.substring(first, last);
        // end
        http_client.end();
        auth_token = cookie;
    }
    delete client;
}

String Harviot::getAuthToken(){
    return auth_token;
}


void Harviot::initCamera(){
    camera_config_t camera_config;
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
    camera_config.frame_size = FRAMESIZE_SVGA;
    camera_config.jpeg_quality = 12;
    camera_config.fb_count = 1;
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
}


bool Harviot::logData(const float *data){
    HTTPClient http_client;
    DynamicJsonDocument log(512);
    String json;
    char buf[sizeof("YYYY-MM-DDT00:00:00Z")];
    time_t now;
    time(&now);
    localtime(&now);
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    log["date"] = buf;
    log["sensorValues"]["temperature"] = data[0];
    log["sensorValues"]["humidity"] = data[1];
    log["sensorValues"]["ambient_light"] = data[2];
    log["sensorValues"]["ph"] = data[3];
    serializeJson(log, json);
    http_client.useHTTP10();
    http_client.begin("https://api.harviot.com/plants/logs", ssl_ca_cert);
    http_client.addHeader(HTTP_HEADER_CONTENT_TYPE, "application/json");
    http_client.addHeader("Cookie", auth_token);
    int response_code = http_client.POST(json);
    http_client.end();
    return response_code == HTTP_CODE_OK;
}

bool Harviot::uploadImage(){

    WiFiClient client;

    String serverName = "192.168.1.13";
    String serverPath = "/plants/images";

    const int serverPort = 8080;

    String getAll;
    String getBody;

    camera_fb_t * fb = esp_camera_fb_get();

    if(!fb) {
        Serial.println("Camera capture failed");
        delay(1000);
        ESP.restart();
    }

    if (client.connect(serverName.c_str(), serverPort)) {
        String head = "--HarviotImageUpload\r\nContent-Disposition: form-data; name=\"imageFile\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
        String tail = "\r\n--HarviotImageUpload--\r\n";

        uint32_t imageLen = fb->len;
        uint32_t extraLen = head.length() + tail.length();
        uint32_t totalLen = imageLen + extraLen;
    
        client.println("POST " + serverPath + " HTTP/1.1");
        client.println("Host: " + serverName);
        client.println("Content-Length: " + String(totalLen));
        client.println("Content-Type: multipart/form-data; boundary=HarviotImageUpload");
        client.println();
        client.print(head);
    
        uint8_t *fbBuf = fb->buf;
        size_t fbLen = fb->len;
        client.write(fbBuf, fbLen);
        client.print(tail);
        
        esp_camera_fb_return(fb);
        
        int timoutTimer = 10000;
        long startTimer = millis();
        boolean state = false;
        
        while ((startTimer + timoutTimer) > millis()) {
            delay(100);      
            while (client.available()) {
                char c = client.read();
                if (c == '\n') {
                    if (getAll.length()==0)
                        state=true;
                    getAll = "";
                } else if (c != '\r')
                    getAll += String(c);
                if (state==true)
                    getBody += String(c);
                startTimer = millis();
            }
            if (getBody.length()>0) { break; }
        }
        client.stop();
    }
    fb = NULL;
    Serial.println(getBody);
    return (getBody == "OK");
}
