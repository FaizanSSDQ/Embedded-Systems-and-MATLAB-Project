float amplitude = 1.0;          // Amplitude of the sawtooth wave
float frequency = 1.0;          // Frequency of the sawtooth wave in Hz
float samplingRate = 100.0;     // Sampling rate in Hz (samples per second)
float timeStep;                 // Time step between samples
unsigned long lastSampleTime = 0; // Time of the last sample

void setup() {
  Serial.begin(115200);         // Initialize serial communication
  timeStep = 1.0 / samplingRate; // Calculate time step based on sampling rate
  Serial.println("Generating Sawtooth Wave...");
}

void loop() {
  // Ensure correct sampling interval
  unsigned long currentTime = millis();
  if (currentTime - lastSampleTime >= 1000.0 / samplingRate) {
    static float time = 0.0;    // Time variable for the sawtooth wave
    static float value = -amplitude; // Starting value of the wave

    // Generate sawtooth wave value
    float increment = (2 * amplitude * frequency) / samplingRate; // Change per sample
    value += increment;         // Increase linearly
    if (value >= amplitude) {   // Reset after reaching the peak
      value = -amplitude;
    }

    // Print the value to Serial Plotter
    Serial.println(value);

    // Update the last sample time
    lastSampleTime = currentTime;
  }
}
