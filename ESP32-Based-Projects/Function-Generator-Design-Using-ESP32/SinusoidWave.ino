#define PI 3.14159265358979323846  // Define PI for calculations
float amplitude = 1.0;            // Amplitude of the sine wave
float frequency = 10.0;            // Frequency of the sine wave in Hz
float samplingRate = 100.0;       // Sampling rate in Hz (samples per second)
unsigned long lastSampleTime = 0; // Time of the last sample
float timeStep;                   // Time step between samples

void setup() {
  Serial.begin(115200); // Initialize serial communication
  timeStep = 1.0 / samplingRate; // Calculate time step based on sampling rate
  Serial.println("Generating Sinusoidal Wave...");
  Serial.println("Adjust amplitude, frequency, or sampling rate in code if needed.");
}

void loop() {
  // Calculate time difference and ensure sampling at correct rate
  unsigned long currentTime = millis();
  if (currentTime - lastSampleTime >= 1000.0 / samplingRate) {
    // Generate sine wave value
    static float time = 0.0; // Time variable for sine function
    float sineValue = amplitude * sin(2 * PI * frequency * time);
    time += timeStep;

    // Print value to Serial Plotter
    Serial.println(sineValue);

    // Update last sample time
    lastSampleTime = currentTime;
  }
}
