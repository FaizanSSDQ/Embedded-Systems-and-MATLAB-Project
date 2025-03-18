#include "Display.h"

void Display::begin() {
  Serial.println("Display Initialized");
}

void Display::showData(uint8_t* data, int size) {
  Serial.println("Captured Data:");
  for (int i = 0; i < BUFFER_SIZE; i++) {
    for (int j = 0; j < NUM_CHANNELS; j++) {
      Serial.print(data[i * NUM_CHANNELS + j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
