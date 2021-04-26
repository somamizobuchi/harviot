#include <Arduino.h>
#include <esp_camera.h>
#include <WiFi.h>
#include <Wire.h>
#include <ArduinoWebsockets.h>
#include <Harviot.hpp>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Si7021.h>
#include "camera_config.h"
#include "config.h"

// MACROS
#define NUM_LEDS 64
#define LED_PIN 12
#define SI7021_ADDR 0x40

// Function declarations
void onMessageCb(websockets::WebsocketsMessage m);

// enum to decode websocket binary data
enum control{PUMP, LIGHT_R, LIGHT_G, LIGHT_B, LIGHT_A, VIDEO_ON};

// LEDs
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t default_led_color = pixels.Color(50, 50, 50);

// HttpClient settings
Harviot harviot(PLANT_ID, PLANT_PASS);

bool videoOn = false;

unsigned long last_frame = 0;
// Si7021 sensors
TwoWire i2c(0);
Adafruit_Si7021 si7021(&i2c);

void setup() {
  Serial.begin(115200);
  // Init sensors
  si7021.begin(15, 14, 10000);
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
  if(videoOn){
    if(millis() - last_frame > 500){
      harviot.captureFrame([](camera_fb_t * fb){
        harviot.WsSendBinary((const char *)fb->buf, fb->len);
      });
      last_frame = millis();
    }
  }
  Serial.print(si7021.readTemperature(), 2);
  Serial.print(si7021.readHumidity(), 2);
  delay(200);
}


void onMessageCb(websockets::WebsocketsMessage m){
  if(m.isBinary()){
    const uint8_t * data = (uint8_t *)m.c_str();
    uint32_t color = pixels.Color(data[LIGHT_R], data[LIGHT_B], data[LIGHT_B]);
    pixels.clear();
    pixels.fill(color, 0, pixels.numPixels());
    pixels.show();
    videoOn = data[VIDEO_ON];
  } else if(m.isText()) {
    Serial.println(m.c_str());
  }
}