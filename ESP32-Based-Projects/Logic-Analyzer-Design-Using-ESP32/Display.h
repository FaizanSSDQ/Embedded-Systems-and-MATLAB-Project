#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

class Display {
public:
  static void begin();
  static void showData(uint8_t* data, int size);
};

#endif
