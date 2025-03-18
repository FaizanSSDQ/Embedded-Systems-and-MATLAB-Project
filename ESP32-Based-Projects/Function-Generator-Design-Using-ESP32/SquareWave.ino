// Square Wave : Fixed Frequency & Duty Cycle
// Freq = 1Hz
// Duty Cycle = 50%

bool ledState = false;
#define LEDPIN 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDPIN , OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  ledState = !ledState;
  digitalWrite(LEDPIN , ledState);
  int val = ledState? 10:5;
  if (val == 10)
  {
  for (int i= 0; i<20 ; i++)
  {  
  Serial.println(val);
  delay(10);
  }
  }
  else
  for (int i= 0; i<80 ; i++)
  {  
  Serial.println(val);
  delay(10);
  }


}


// Take input of Frequency & Duty Cycle from User
  // Square Wave with User Input for Frequency and Duty Cycle

bool ledState = false;
#define LEDPIN 13

float frequency = 1.0;     // Default frequency in Hz
float dutyCycle = 20.0;    // Default duty cycle in percentage (20%)
unsigned long highTime;    // Time for HIGH state (milliseconds)
unsigned long lowTime;     // Time for LOW state (milliseconds)

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  pinMode(LEDPIN, OUTPUT);

  // Calculate initial HIGH and LOW times based on defaults
  calculateTimings();
  Serial.println("Enter frequency in Hz and duty cycle in percentage (e.g., 2 50):");
}

void loop() {
  // Check for user input via Serial
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read user input
    parseInput(input);                          // Parse and update values
    calculateTimings();                         // Recalculate timings
  }

  // Generate the square wave
  ledState = !ledState;
  digitalWrite(LEDPIN, ledState);

  unsigned long duration = ledState ? highTime : lowTime;

  for (int i = 0; i < duration / 10; i++) {
    Serial.println(ledState ? 1 : 0); // Output HIGH (1) or LOW (0)
    delay(10);
  }
}

// Calculate HIGH and LOW times based on frequency and duty cycle
void calculateTimings() {
  float period = 1000.0 / frequency; // Total period in milliseconds
  highTime = (period * dutyCycle) / 100; // HIGH time based on duty cycle
  lowTime = period - highTime;          // Remaining time for LOW state
}

// Parse user input and update frequency and duty cycle
void parseInput(String input) {
  float freq, duty;
  int values = sscanf(input.c_str(), "%f %f", &freq, &duty);

  if (values == 2 && freq > 0 && duty >= 0 && duty <= 100) {
    frequency = freq;
    dutyCycle = duty;
    Serial.print("Updated Frequency: ");
    Serial.print(frequency);
    Serial.print(" Hz, Duty Cycle: ");
    Serial.print(dutyCycle);
    Serial.println(" %");
  } else {
    Serial.println("Invalid input! Enter two numbers: frequency (Hz) and duty cycle (%)");
  }
}
