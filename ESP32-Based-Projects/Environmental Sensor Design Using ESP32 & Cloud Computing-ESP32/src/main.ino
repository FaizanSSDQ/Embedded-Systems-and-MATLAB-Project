// Environmental Sensor Project using ESP32 & ThingSpeak
// Reads temperature, humidity, pressure, and altitude, then uploads data to ThingSpeak

#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include "config.h"

#define CHANNEL_ID 2033403
#define CHANNEL_API_KEY "HZLJIODEMOEDBV4Z"

WiFiClient client;
DHT dht(PIN_DHT, DHT11);
Adafruit_BMP280 bmp;

int id = 0;
float temperature = 0.0;
float humidity = 0.0;
float pressure = 0.0;
float altitude = 0.0;

void connectToWiFi() {
    Serial.print("Connecting to WiFi");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < WIFI_TIMEOUT_MS) {
        Serial.print(".");
        delay(100);
    }
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(" Failed");
    } else {
        Serial.println(" Connected to WiFi");
        Serial.println(WiFi.localIP());
    }
}

void setup() {
    Serial.begin(115200);
    connectToWiFi();
    dht.begin();
    if (!bmp.begin(0x76)) {
        Serial.println("BMP280 sensor not found!");
    }
    ThingSpeak.begin(client);
    delay(2500);
}

void loop() {
    id++;
    temperature = dht.readTemperature(); // Read temperature
    humidity = dht.readHumidity(); // Read humidity
    pressure = bmp.readPressure() / 100.0F; // Convert pressure to hPa
    altitude = bmp.readAltitude(1013.25); // Estimate altitude
    
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Pressure: "); Serial.print(pressure); Serial.println(" hPa");
    Serial.print("Altitude: "); Serial.print(altitude); Serial.println(" m");
    
    ThingSpeak.setField(1, id);
    ThingSpeak.setField(2, temperature);
    ThingSpeak.setField(3, humidity);
    ThingSpeak.setField(4, pressure);
    ThingSpeak.setField(5, altitude);
    ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
    
    delay(15000); // Upload interval
}
