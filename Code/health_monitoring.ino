
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// ---------------- WIFI CONFIGURATION ----------------
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// ThingSpeak Write API Key
const char* THINGSPEAK_API_KEY =
    "YOUR_THINGSPEAK_WRITE_API_KEY";

// ---------------- PIN CONFIGURATION ----------------
#define OLED_SDA 21
#define OLED_SCL 22

#define TEMP_PIN 23

#define ECG_PIN 34
#define ECG_LO_PLUS 32
#define ECG_LO_MINUS 33

#define BEAT_LED 2

// ---------------- OLED CONFIGURATION ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// ---------------- SENSOR OBJECTS ----------------
PulseOximeter pox;

OneWire oneWire(TEMP_PIN);
DallasTemperature temperatureSensor(&oneWire);

// ---------------- SENSOR VARIABLES ----------------
float heartRate = 0.0;
float spo2 = 0.0;
float bodyTemperature = NAN;

int ecgValue = 0;
bool leadsConnected = false;

bool max30100Ready = false;
bool oledReady = false;

// ---------------- TIMING ----------------
unsigned long lastDisplayTime = 0;
unsigned long lastUploadTime = 0;
unsigned long lastTempRequest = 0;
unsigned long lastTempRead = 0;
unsigned long lastECGSample = 0;

const unsigned long DISPLAY_INTERVAL = 1000;
const unsigned long UPLOAD_INTERVAL = 20000;
const unsigned long TEMP_INTERVAL = 2000;
const unsigned long ECG_INTERVAL = 10;

// ---------------- HEARTBEAT CALLBACK ----------------
void onBeatDetected() {
  digitalWrite(BEAT_LED, HIGH);
}

// ---------------- WIFI CONNECTION ----------------
void connectWiFi() {

  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startTime < 20000) {

    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println("\nWiFi Connection Failed!");
  }
}

// ---------------- MAX30100 INITIALIZATION ----------------
void initializeMAX30100() {

  Serial.println("Initializing MAX30100...");

  if (!pox.begin()) {

    Serial.println("MAX30100 initialization failed!");
    max30100Ready = false;

  } else {

    Serial.println("MAX30100 initialized!");

    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);

    max30100Ready = true;
  }
}

// ---------------- TEMPERATURE INITIALIZATION ----------------
void initializeTemperature() {

  temperatureSensor.begin();

  temperatureSensor.setWaitForConversion(false);

  temperatureSensor.requestTemperatures();

  lastTempRequest = millis();

  Serial.println("DS18B20 initialized!");
}

// ---------------- ECG READING ----------------
void readECG() {

  if (millis() - lastECGSample >= ECG_INTERVAL) {

    lastECGSample = millis();

    bool loPlus = digitalRead(ECG_LO_PLUS);
    bool loMinus = digitalRead(ECG_LO_MINUS);

    leadsConnected = (!loPlus && !loMinus);

    if (leadsConnected) {

      ecgValue = analogRead(ECG_PIN);

    } else {

      ecgValue = 0;
    }
  }
}

// ---------------- TEMPERATURE READING ----------------
void readTemperature() {

  unsigned long now = millis();

  if (now - lastTempRequest >= TEMP_INTERVAL) {

    bodyTemperature =
      temperatureSensor.getTempCByIndex(0);

    if (bodyTemperature == DEVICE_DISCONNECTED_C ||
        bodyTemperature < -55 ||
        bodyTemperature > 125) {

      bodyTemperature = NAN;
    }

    temperatureSensor.requestTemperatures();

    lastTempRequest = now;
  }
}

// ---------------- OLED DISPLAY ----------------
void updateDisplay() {

  if (!oledReady) return;

  if (millis() - lastDisplayTime >= DISPLAY_INTERVAL) {

    lastDisplayTime = millis();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.println("IoT HEALTH MONITOR");
    display.println("--------------------");

    display.print("HR: ");

    if (max30100Ready && heartRate > 0) {
      display.print(heartRate, 0);
      display.println(" BPM");
    } else {
      display.println("-- BPM");
    }

    display.print("SpO2: ");

    if (max30100Ready && spo2 > 0) {
      display.print(spo2, 0);
      display.println(" %");
    } else {
      display.println("-- %");
    }

    display.print("Temp: ");

    if (!isnan(bodyTemperature)) {
      display.print(bodyTemperature, 1);
      display.println(" C");
    } else {
      display.println("-- C");
    }

    display.print("ECG: ");
    display.println(leadsConnected ?
                    String(ecgValue) : "LEAD OFF");

    display.print("WiFi: ");
    display.println(WiFi.status() == WL_CONNECTED ?
                    "CONNECTED" : "OFFLINE");

    display.display();
  }
}

// ---------------- SERIAL MONITOR ----------------
void printSensorData() {

  Serial.println("\n------ HEALTH DATA ------");

  Serial.print("Heart Rate: ");
  Serial.println(heartRate);

  Serial.print("SpO2: ");
  Serial.println(spo2);

  Serial.print("Temperature: ");
  Serial.println(bodyTemperature);

  Serial.print("ECG ADC: ");
  Serial.println(ecgValue);

  Serial.print("ECG Leads: ");
  Serial.println(leadsConnected ?
                 "Connected" : "Disconnected");

  Serial.println("-------------------------");
}

// ---------------- THINGSPEAK UPLOAD ----------------
void uploadToThingSpeak() {

  if (millis() - lastUploadTime < UPLOAD_INTERVAL) {
    return;
  }

  lastUploadTime = millis();

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi unavailable. Upload skipped.");
    return;
  }

  WiFiClientSecure secureClient;

  // Demonstration configuration.
  // Use certificate validation in production.
  secureClient.setInsecure();

  HTTPClient https;

  String url =
    "https://api.thingspeak.com/update?api_key=";

  url += THINGSPEAK_API_KEY;

  url += "&field1=" + String(heartRate, 1);
  url += "&field2=" + String(spo2, 1);

  if (!isnan(bodyTemperature)) {
    url += "&field3=" + String(bodyTemperature, 2);
  }

  // Field 4: Latest ECG ADC sample
  if (leadsConnected) {
    url += "&field4=" + String(ecgValue);
  }

  // Field 5: ECG lead status (1 = connected)
  url += "&field5=";
  url += leadsConnected ? "1" : "0";

  https.setTimeout(5000);

  if (https.begin(secureClient, url)) {

    int httpCode = https.GET();

    if (httpCode > 0) {

      String response = https.getString();

      Serial.print("ThingSpeak HTTP Code: ");
      Serial.println(httpCode);

      Serial.print("ThingSpeak Entry ID: ");
      Serial.println(response);

    } else {

      Serial.print("Upload Error: ");
      Serial.println(https.errorToString(httpCode));
    }

    https.end();

  } else {

    Serial.println("Unable to connect to ThingSpeak.");
  }
}

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);

  pinMode(BEAT_LED, OUTPUT);
  pinMode(ECG_LO_PLUS, INPUT);
  pinMode(ECG_LO_MINUS, INPUT);

  digitalWrite(BEAT_LED, LOW);

  analogReadResolution(12);

  Wire.begin(OLED_SDA, OLED_SCL);

  // OLED initialization
  oledReady = display.begin(
    SSD1306_SWITCHCAPVCC,
    0x3C
  );

  if (oledReady) {

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    display.println("IoT Health Monitor");
    display.println("System Starting...");
    display.display();

  } else {

    Serial.println("OLED initialization failed!");
  }

  // Initialize sensors
  initializeMAX30100();
  initializeTemperature();

  // WiFi
  connectWiFi();

  Serial.println("\nSystem Initialization Complete!");
}

// ---------------- MAIN LOOP ----------------
void loop() {

  // MAX30100 requires frequent updates
  if (max30100Ready) {

    pox.update();

    heartRate = pox.getHeartRate();
    spo2 = pox.getSpO2();

    digitalWrite(BEAT_LED, LOW);
  }

  // Read ECG
  readECG();

  // Read temperature
  readTemperature();

  // Update display
  updateDisplay();

  // Print data
  if (millis() - lastDisplayTime < 5) {
    // No additional blocking operation
  }

  // Upload to cloud
  uploadToThingSpeak();

  // Reconnect WiFi when disconnected
  static unsigned long lastWiFiCheck = 0;

  if (WiFi.status() != WL_CONNECTED &&
      millis() - lastWiFiCheck >= 10000) {

    lastWiFiCheck = millis();
    connectWiFi();
  }

  // Keep sensor updates running
}
