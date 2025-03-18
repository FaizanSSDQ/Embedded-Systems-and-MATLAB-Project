#ifndef SENSORS_H
#define SENSORS_H

#include <DHT.h>
#include <Adafruit_BMP280.h>

extern DHT dht;
extern Adafruit_BMP280 bmp;

void initSensors() {
    dht.begin();
    if (!bmp.begin(BMP280_I2C_ADDR)) {
        Serial.println("BMP280 sensor not found!");
    }
}

void readSensors(float &temperature, float &humidity, float &pressure, float &altitude) {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    pressure = bmp.readPressure() / 100.0F; // Convert pressure to hPa
    altitude = bmp.readAltitude(1013.25); // Estimate altitude
}

#endif
