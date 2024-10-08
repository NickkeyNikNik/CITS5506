/*
   -- smartCoasterNew --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.11 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.4 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_WIFI_POINT
#include <WiFi.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "SmartCoaster2"
#define REMOTEXY_WIFI_PASSWORD "88880000"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 268 bytes
  { 255,4,0,44,0,5,1,16,16,5,67,5,13,23,39,15,1,8,29,11,
  3,3,43,24,12,32,2,64,27,1,2,36,65,12,12,2,50,31,43,0,
  1,2,16,65,12,12,2,205,16,45,0,67,5,24,23,13,5,2,192,30,
  11,129,0,12,16,40,4,1,65,67,117,114,114,101,110,116,32,84,101,109,
  112,101,114,97,116,117,114,101,0,67,5,24,37,13,5,2,78,30,11,67,
  5,24,51,13,5,2,51,30,11,129,0,9,23,11,5,2,192,67,111,108,
  100,0,129,0,8,37,13,5,2,78,87,97,114,109,0,129,0,10,51,8,
  5,2,51,72,111,116,0,129,0,5,3,54,8,0,65,83,109,97,114,116,
  32,67,111,97,115,116,101,114,0,129,0,16,45,32,6,1,65,78,111,116,
  105,102,105,99,97,116,105,111,110,0,131,1,8,90,20,7,1,2,31,77,
  97,105,110,0,131,0,35,90,20,7,2,2,31,83,101,116,116,105,110,103,
  0,3,131,11,63,41,15,1,2,26,129,0,9,54,13,6,1,178,67,111,
  108,100,0,129,0,25,54,16,6,1,64,87,97,114,109,0,129,0,44,54,
  9,6,1,51,72,111,116,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t TempSwitch; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t add; // =1 if button pressed, else =0 
  uint8_t minus; // =1 if button pressed, else =0 
  uint8_t SMSswitch; // =0 if select position A, =1 if position B, =2 if position C, ... 

    // output variables
  char TempDisplay[11];  // string UTF8 end zero 
  char coldTemp[11];  // string UTF8 end zero 
  char warmTemp[11];  // string UTF8 end zero 
  char hotTemp[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
// Import necessary libraries
#include <HTTPClient.h>
#include <DFRobot_MLX90614.h>

// WiFi and Pushbullet Setup
const char* ssid = "IOTproject";        // WiFi SSID (network name)
const char* password = "hahaha123";     // WiFi password
const char* apiKey = <insert you own api key>;

// Define pins for LEDs, distance sensor and button
int yellowLED = 2;
int redLED = 13;
int blueLED = 14;
int DistTrigger = 23;                  // Ultrasonic distance sensor trigger pin
int DistEcho = 4;                      // Ultrasonic distance sensor echo pin
int button = 35;
int buttonState = 0;
bool buttonFlag = false;

// Default temperature settings (in Celsius)
float cold = 30.0;
float warm = 50.0;
float hot = 70.0;
float distance = 0.0;
bool distanceFlag = false;

// Initialize the IR temperature sensor
DFRobot_MLX90614_I2C sensor;

void setup() {
  RemoteXY_Init();                      // Initialize RemoteXY (an external library for remote control)
  // Set the pin modes
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(DistTrigger, OUTPUT);
  pinMode(DistEcho, INPUT);
  pinMode(button, INPUT);
  
  // Convert default temperature settings to strings and save to RemoteXY
  dtostrf(cold, 0, 1, RemoteXY.coldTemp);
  dtostrf(warm, 0, 1, RemoteXY.warmTemp);
  dtostrf(hot, 0, 1, RemoteXY.hotTemp);

  Serial.begin(9600);                  // Begin Serial communication

  // Reset the thermal sensor
  sensor.enterSleepMode();
  RemoteXY_delay(50);
  sensor.enterSleepMode(false);
  RemoteXY_delay(200);
}

float readDistanceSensor() {
  // Send a pulse from the trigger pin and measure the time for the echo pin to receive the reflected signal
  digitalWrite(DistTrigger, LOW);
  RemoteXY_delay(2);
  digitalWrite(DistTrigger, HIGH);
  RemoteXY_delay(10);
  digitalWrite(DistTrigger, LOW);

  float duration = pulseIn(DistEcho, HIGH);
  float distance = duration * 0.0343 / 2.0;  // Convert duration to distance in centimeters
  return distance;
}

void initializeWiFi() {
  // Establish WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    RemoteXY_delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void disconnectWiFi() {
  WiFi.disconnect();                      // Disconnect from the WiFi network
}

void sendNotification(String type) {
  // Send a notification to Pushbullet service
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://api.pushbullet.com/v2/pushes");
    http.addHeader("Authorization", "Bearer " + String(apiKey));
    http.addHeader("Content-Type", "application/json");

    String json = "{\"type\": \"note\", \"title\": \"SMART COASTER Notification\", \"body\": \"Your " + type + " drink is ready!!\"}";
    int httpResponseCode = http.POST(json);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }
}

void loop() {
  RemoteXY_Handler();                    // Update RemoteXY states

  // Read the distance sensor
  distance = readDistanceSensor();
  if (distance < 5 || distance > 750) {
    distanceFlag = true;
  } else {
    distanceFlag = false;
  }

  // Read temperature from the IR sensor
  float temp = sensor.getObjectTempCelsius();
  RemoteXY_delay(100);

  // Check button press and light up all LEDs when pressed
  buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    buttonFlag = false;
    Serial.println("Button Pressed!");
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    RemoteXY_delay(100);
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
  }
  
  // Check distance and temperature to send notifications
  if (!buttonFlag && distanceFlag) {
    // ... (the code checks for various temperature ranges and sends appropriate notifications)

    // Adjust the temperature settings remotely
    // ... (the code checks for RemoteXY inputs and adjusts temperature settings)

    // LED indications based on temperature readings
    if (distanceFlag) {
      if (temp > warm) {
        digitalWrite(redLED, HIGH);      // Hot temperature indication
        digitalWrite(blueLED, LOW);
        digitalWrite(yellowLED, LOW);
      } else if (temp <= warm && temp > cold) {
        digitalWrite(redLED, LOW);
        digitalWrite(yellowLED, HIGH);   // Warm temperature indication
        digitalWrite(blueLED, LOW);
      } else if (temp <= cold) {
        digitalWrite(redLED, LOW);
        digitalWrite(yellowLED, LOW);
        digitalWrite(blueLED, HIGH);    // Cold temperature indication
      }
    } else {
      // Turn off all LEDs if no cup is detected
      digitalWrite(blueLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, LOW);
    }
  }
}