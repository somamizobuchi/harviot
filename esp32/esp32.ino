#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <esp_camera.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>

// Camera Setup
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// LED Setup
#define NUM_LEDS 64
#define LED_PIN 14

// functions definitions
void configCamera();

// WiFi settings
const char* ssid = "AMOS_2G";  // SSID
const char* password = "orangehat983"; //Enter Password

// WebSockets settings
String websockets_server_host = "ws://192.168.1.208:8080/?plant_id=6021f39b3e64fd8d1fc5c2aa"; //Enter server adress

// HttpClient settings
HTTPClient http;
const char * headerkeys[] = {"Set-Cookie"};
size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
const char * post_url = "http://192.168.1.208:8080/auth?entity=plant";
const char * post_content = "{\"_id\": \"6021f39b3e64fd8d1fc5c2aa\", \"password\": \"password\"}";

// enum to decode websocket binary data
enum control{PUMP, LIGHT_R, LIGHT_G, LIGHT_B, LIGHT_A, VIDEO_ON};

// timers
unsigned long lastFrame = 0;
// video on
bool videoOn = false;

// LEDs
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint8_t LED_RGB[3] = {0, 0, 0};

using namespace websockets;
WebsocketsClient ws;
void setup() {
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);
    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Check if connected to wifi
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }
    Serial.print("Connected to: ");
    Serial.println(ssid);

    // HTTP Request to get Cookie
    http.begin(post_url);
    http.collectHeaders(headerkeys, headerkeyssize);
    http.addHeader("Content-Type", "application/json");
    uint8_t code = http.POST(post_content);
    String cookie;
    Serial.printf("Server responded with code: %d\n", code);
    if(code == 200){
      cookie = http.header("Set-Cookie");
      int first = cookie.indexOf("auth=");
      int last = cookie.indexOf(";", first);
      cookie = cookie.substring(first, last);
      Serial.printf("Authorization Token: %s\n", cookie.c_str());
    }

    // LEDs
    pixels.begin();
    pixels.clear();
    for(uint8_t i=0; i<NUM_LEDS; i++){
      pixels.setPixelColor(i, pixels.Color(LED_RGB[0], LED_RGB[1], LED_RGB[2]));
    }
    pixels.show();
  
    configCamera();
    // try to connect to Websockets server
    ws.addHeader("Cookie", cookie);
    bool connected = ws.connect(websockets_server_host);
    if(connected) {
      Serial.println("Connected to WebSockets");
    } else {
      Serial.println("Connection to WebSockets Failed");
    }
    // run callback when messages are received
    ws.onMessage([&](WebsocketsMessage message){
      if(message.isBinary()){
        const uint8_t * msg = (uint8_t *)message.c_str();
        videoOn = msg[VIDEO_ON];
        LED_RGB[0] = msg[LIGHT_R];
        LED_RGB[1] = msg[LIGHT_G];
        LED_RGB[2] = msg[LIGHT_B];
        pixels.clear();
        for(uint8_t i=0; i<NUM_LEDS; i++){
          pixels.setPixelColor(i, pixels.Color(LED_RGB[0], LED_RGB[1], LED_RGB[2]));
        }
        pixels.show();
      }
    });
}

void loop() {
  // let the websockets ws check for incoming messages
  ws.poll();
  // Video Stream
  if(videoOn){
    if(lastFrame - millis() > 43){
      camera_fb_t * fb = esp_camera_fb_get();
      if (!fb) {
          Serial.println("Frame buffer could not be acquired");
          return;
      }
      // websockets
      ws.sendBinary((const char *)fb->buf, fb->len);
      // return frame buffer to grabber
      esp_camera_fb_return(fb);
      lastFrame = millis();
    }
  }
}


void configCamera(){
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 9;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}
