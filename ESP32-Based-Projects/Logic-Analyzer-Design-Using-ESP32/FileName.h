#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <Arduino.h>
#include <SPIFFS.h>

class FileSystem {
public:
  static bool begin();
  static void saveData(uint8_t* data, int size);
};

#endif
