//SW-420
#define LedPIN 14
#define SensorPIN 12
bool SensorState = false;
int vibCounter = 0;
unsigned long int currentTime = 2000;
void setup(void) {
// put your setup code here, to run once:
Serial.begin(115200);
pinMode(LedPIN , OUTPUT);
pinMode(SensorPIN , INPUT);
}

void loop(void) {
  // put your main code here, to run repeatedly:
  SensorState = digitalRead(SensorPIN);
  if (SensorState == 1)
  {
    digitalWrite(LedPIN , HIGH);
    vibCounter++;
    Serial.println("Vibration...");
  }
  else
  {
    digitalWrite(LedPIN , LOW);
  }

  if ( millis() - currentTime >= 4000)
  {
    Serial.print("The counter is: ");
    Serial.println(vibCounter);
    currentTime = millis();
  }

}
