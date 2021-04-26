#include <Arduino.h>
#include <esp_camera.h>
#include <WiFi.h>
#include <Wire.h>
#include <ArduinoWebsockets.h>
#include <Harviot.hpp>
#include <Adafruit_NeoPixel.h>
#include "camera_config.h"
#include "config.h"

// MACROS
#define NUM_LEDS 64
#define LED_PIN 12

// Function declarations
void configCamera();
void onMessageCb(websockets::WebsocketsMessage m);

// enum to decode websocket binary data
enum control{PUMP, LIGHT_R, LIGHT_G, LIGHT_B, LIGHT_A, VIDEO_ON};

// LEDs
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t default_led_color = pixels.Color(50, 50, 50);

// HttpClient settings
Harviot harviot(PLANT_ID, PLANT_PASS);


void setup() {
  Serial.begin(115200);
  // Setup camera
  configCamera();
  // LED setup
  pixels.begin();
  pixels.clear();
  pixels.fill(default_led_color, 0, pixels.numPixels());
  pixels.show();
  // WiFi setup
  Serial.println("Connecting to WiFi...");
  WiFi.begin(SSID, WIFI_PASS);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected.");
  // Make auth request
  harviot.wsOnMessage(onMessageCb);
  harviot.init();
}

void loop() {
  harviot.poll();
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


void onMessageCb(websockets::WebsocketsMessage m){
  if(m.isBinary()){
    const uint8_t * data = (uint8_t *)m.c_str();
    uint32_t color = pixels.Color(data[LIGHT_R], data[LIGHT_B], data[LIGHT_B]);
    pixels.clear();
    pixels.fill(color, 0, pixels.numPixels());
    pixels.show();
  } else if(m.isText()) {
    Serial.println(m.c_str());
  }
}