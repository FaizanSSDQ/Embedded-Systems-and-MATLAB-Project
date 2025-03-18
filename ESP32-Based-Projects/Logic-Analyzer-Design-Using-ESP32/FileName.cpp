#include "FileSystem.h"

bool FileSystem::begin() {
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS");
    return false;
  }
  Serial.println("SPIFFS Initialized");
  return true;
}

void FileSystem::saveData(uint8_t* data, int size) {
  File file = SPIFFS.open("/capture.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  for (int i = 0; i < BUFFER_SIZE; i++) {
    for (int j = 0; j < NUM_CHANNELS; j++) {
      file.print(data[i * NUM_CHANNELS + j]);
      file.print(" ");
    }
    file.println();
  }

  file.close();
  Serial.println("Data saved to SPIFFS");
}
