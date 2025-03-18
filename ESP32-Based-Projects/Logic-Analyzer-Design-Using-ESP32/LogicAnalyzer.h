#ifndef LOGIC_ANALYZER_H
#define LOGIC_ANALYZER_H

#include <Arduino.h>

#define NUM_CHANNELS 8
#define BUFFER_SIZE 1000
#define SAMPLING_INTERVAL 100 // in microseconds

class LogicAnalyzer {
public:
  static bool begin();
  static void captureData();
  static uint8_t* getBuffer();
  static int getBufferSize();

private:
  static const int channels[NUM_CHANNELS];
  static uint8_t buffer[BUFFER_SIZE][NUM_CHANNELS];
  static int bufferIndex;
};

#endif
