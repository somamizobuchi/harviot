#include <Arduino.h>
#include <esp_camera.h>
#include <WiFi.h>
#include <Wire.h>
#include <ArduinoWebsockets.h>
#include <Harviot.hpp>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Si7021.h>
#include <Adafruit_ADS1X15.h>
#include "camera_config.h"
#include "config.h"

// MACROS
#define NUM_LEDS 64
#define SDA_PIN 14
#define SCL_PIN 15
#define MTR_PIN 13
#define LED_PIN 12
#define ONE_SECOND_MILLIS 1000
#define LOG_INTERVAL_MILLIS 900000 // 15 minutes

// Function declarations
void onMessageCb(websockets::WebsocketsMessage m);
void readSensors();

// enum for indexing the control register
enum control{PUMP, LIGHT_R, LIGHT_G, LIGHT_B, VIDEO_ON};
uint8_t controlRegister[5] = {0, 127, 0, 127, 0};

// enum for indexing the sensor values
enum sensors{
  TEMPERATURE, 
  HUMIDITY, 
  AMBIENT_LIGHT,
  PH
};
float sensorValues[4] = {0, 0, 0};

// LEDs
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t default_led_color = pixels.Color(20, 0, 20);

// HttpClient settings
Harviot harviot(PLANT_ID, PLANT_PASS);

bool videoOn = false;
uint8_t motorState = HIGH;

// Si7021 sensors
TwoWire i2c(0);
Adafruit_Si7021 si7021(&i2c);
Adafruit_ADS1115 adc;

/**
 * @brief Setup
 * 
 */
void setup() {
  Serial.begin(115200);
  // Init sensors
  si7021.begin(SDA_PIN, SCL_PIN, 1000);
  adc.begin(ADS1X15_ADDRESS, &i2c);
  adc.setGain(GAIN_TWOTHIRDS);
  adc.setDataRate(RATE_ADS1115_8SPS);
  // LED setup
  pixels.begin();
  pixels.clear();
  pixels.fill(default_led_color, 0, pixels.numPixels());
  // WiFi setup
  const char *ssid = SSID;
  const char *wifi_pass = WIFI_PASS;
  WiFi.begin(ssid, wifi_pass);
  Serial.println("Connecting to WiFi...");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  Serial.println("Connected to WiFi.");
  // Setup communication to the Harviot API
  harviot.wsOnMessage(onMessageCb);
  harviot.init();
  // Motor Setup
  pinMode(MTR_PIN, OUTPUT);
}

/**
 * @brief Main Loop
 * To be executed by the ESP32
 */
void loop() {
  pixels.show();
  harviot.poll();
  // readSensors
  readSensors();
}

/**
 * @brief Callback to be executed when message received via WebSockets
 * 
 * @param m The websockets message
 */
void onMessageCb(websockets::WebsocketsMessage m){
  if(m.isBinary()){
    const uint8_t * data = (uint8_t *)m.c_str();
    controlRegister[data[0]] = data[1];
    if(data[0] >= LIGHT_R && data[0] <= LIGHT_B){
      uint32_t color = pixels.Color(controlRegister[LIGHT_R], controlRegister[LIGHT_G], controlRegister[LIGHT_B]);
      pixels.clear();
      pixels.fill(color, 0, pixels.numPixels());
      pixels.show();
    }
  } else if(m.isText()) {
    Serial.println(m.c_str());
  }
}

/**
 * @brief Reads the sensor values and posts data
 * 
 */
void readSensors(){
  static unsigned long lastRead = 0;
  if(millis() - lastRead >= LOG_INTERVAL_MILLIS){
    sensorValues[TEMPERATURE] = si7021.readTemperature();
    sensorValues[HUMIDITY] = si7021.readHumidity();
    sensorValues[AMBIENT_LIGHT] = adc.readADC_SingleEnded(0);
    sensorValues[PH] = ((float)adc.readADC_SingleEnded(1) / 32768.0) * 5.0;
    if(harviot.logData(sensorValues)){
      Serial.println("Data logged.");
    }
    if(harviot.uploadImage()){
      Serial.println("Image uploaded.");
    }
    lastRead = millis();
  }
}