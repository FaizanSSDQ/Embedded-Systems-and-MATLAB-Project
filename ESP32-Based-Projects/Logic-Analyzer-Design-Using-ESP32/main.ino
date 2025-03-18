#include "LogicAnalyzer.h"
#include "Display.h"
#include "FileSystem.h"

void setup() {
  Serial.begin(115200);
  if (!LogicAnalyzer::begin()) {
    Serial.println("Failed to initialize Logic Analyzer!");
    while (1);
  }
  Display::begin();
  FileSystem::begin();
  Serial.println("ESP32 Logic Analyzer Ready!");
}

void loop() {
  // Capture data
  LogicAnalyzer::captureData();

  // Display data
  Display::showData(LogicAnalyzer::getBuffer(), LogicAnalyzer::getBufferSize());

  // Save data to file
  FileSystem::saveData(LogicAnalyzer::getBuffer(), LogicAnalyzer::getBufferSize());

  // Wait before next capture
  delay(2000);
}