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
#define LED_PIN 12
#define MOTOR_CTRL_PIN 13
#define ONE_HOUR_MILLIS (1000*60*60)

// Function declarations
void onMessageCb(websockets::WebsocketsMessage m);
void readSensors();

// enum for indexing the control register
enum control{PUMP, LIGHT_R, LIGHT_G, LIGHT_B, VIDEO_ON};
uint8_t controlRegister[5] = {0, 0, 127, 0, 127};

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

unsigned long last_frame = 0;
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
  si7021.begin(15, 14, 32000);
  adc.begin(ADS1X15_ADDRESS, &i2c);
  adc.setGain(GAIN_ONE);
  adc.setDataRate(RATE_ADS1115_8SPS);
  // LED setup
  pixels.begin();
  pixels.clear();
  pixels.fill(default_led_color, 0, pixels.numPixels());
  // WiFi setup
  Serial.println("Connecting to WiFi...");
  WiFi.begin(SSID, WIFI_PASS);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println(" ");
  Serial.println("Connected.");
  // Setup communication to the Harviot API
  harviot.wsOnMessage(onMessageCb);
  harviot.init();
  // Motor Setup
  pinMode(MOTOR_CTRL_PIN, OUTPUT);
}

/**
 * @brief Main Loop
 * To be executed by the ESP32
 */
void loop() {
  pixels.show();
  harviot.poll();
  // Send frames via websockets
  if(controlRegister[VIDEO_ON]){
    if(millis() - last_frame > 500){
      harviot.captureFrame([](camera_fb_t * fb){
        harviot.WsSendBinary((const char *)fb->buf, fb->len);
      });
      last_frame = millis();
    }
  }
  // motorState = motorState == HIGH ? LOW : HIGH;
  digitalWrite(MOTOR_CTRL_PIN, controlRegister[PUMP]);
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
  const unsigned long readInterval = 750;
  static unsigned long lastRead = 0;
  if(millis() - lastRead >= readInterval){
    sensorValues[TEMPERATURE] = si7021.readTemperature();
    sensorValues[HUMIDITY] = si7021.readHumidity();
    sensorValues[AMBIENT_LIGHT] = adc.readADC_SingleEnded(0);
    sensorValues[PH] = ((float)adc.readADC_SingleEnded(1) / 32768.0) * 5.0;
    Serial.println(sensorValues[PH]);
    lastRead = millis();
    // harviot.logData(sensorValues);
  }
}