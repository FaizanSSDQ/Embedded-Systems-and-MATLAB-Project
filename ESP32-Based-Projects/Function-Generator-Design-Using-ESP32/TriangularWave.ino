float amplitude = 1.0;          // Amplitude of the triangular wave
float frequency = 1.0;          // Frequency of the triangular wave in Hz
float samplingRate = 100.0;     // Sampling rate in Hz (samples per second)
float timeStep;                 // Time step between samples
unsigned long lastSampleTime = 0; // Time of the last sample

void setup() {
  Serial.begin(115200);         // Initialize serial communication
  timeStep = 1.0 / samplingRate; // Calculate time step based on sampling rate
  Serial.println("Generating Triangular Wave...");
}

void loop() {
  // Ensure correct sampling interval
  unsigned long currentTime = millis();
  if (currentTime - lastSampleTime >= 1000.0 / samplingRate) {
    static float time = 0.0;    // Time variable for the triangular wave
    static bool increasing = true; // Direction of the wave
    static float value = -amplitude; // Starting value of the wave

    // Generate triangular wave value
    float increment = (4 * amplitude * frequency) / samplingRate; // Change per sample
    if (increasing) {
      value += increment; // Move upward
      if (value >= amplitude) { // Peak reached
        value = amplitude;
        increasing = false; // Switch direction
      }
    } else {
      value -= increment; // Move downward
      if (value <= -amplitude) { // Trough reached
        value = -amplitude;
        increasing = true; // Switch direction
      }
    }

    // Print the value to Serial Plotter
    Serial.println(value);

    // Update the last sample time
    lastSampleTime = currentTime;
  }
}
