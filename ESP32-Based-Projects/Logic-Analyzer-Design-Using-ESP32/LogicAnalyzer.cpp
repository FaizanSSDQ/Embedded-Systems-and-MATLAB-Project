#include "LogicAnalyzer.h"

const int LogicAnalyzer::channels[NUM_CHANNELS] = {13, 12, 14, 27, 26, 25, 33, 32};
uint8_t LogicAnalyzer::buffer[BUFFER_SIZE][NUM_CHANNELS];
int LogicAnalyzer::bufferIndex = 0;

bool LogicAnalyzer::begin() {
  for (int i = 0; i < NUM_CHANNELS; i++) {
    pinMode(channels[i], INPUT);
  }
  return true;
}

void LogicAnalyzer::captureData() {
  unsigned long startTime = micros();
  bufferIndex = 0;
  while (micros() - startTime < BUFFER_SIZE * SAMPLING_INTERVAL) {
    for (int i = 0; i < NUM_CHANNELS; i++) {
      buffer[bufferIndex][i] = digitalRead(channels[i]);
    }
    bufferIndex++;
    delayMicroseconds(SAMPLING_INTERVAL);
  }
}

uint8_t* LogicAnalyzer::getBuffer() {
  return &buffer[0][0];
}

int LogicAnalyzer::getBufferSize() {
  return BUFFER_SIZE * NUM_CHANNELS;
}
