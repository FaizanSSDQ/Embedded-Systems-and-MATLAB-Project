// KY-026 Flame Sensor
#define ledPIN  14 // define the LED pin
#define digitalPIN  12 // KY-026 digital interface
#define analogPIN   13 // KY-026 analog interface
int digitalVal; // digital readings
int analogVal; //analog readings
void setup()
{
  pinMode(ledPIN, OUTPUT);
  pinMode(digitalPIN, INPUT);
  //pinMode(analogPin, OUTPUT);
  Serial.begin(115200);
}
void loop()
{
  // Read the digital interface
  digitalVal = digitalRead(digitalPIN); 
  if(digitalVal == HIGH) // if flame is detected
  {
    digitalWrite(ledPIN, HIGH); // turn ON Arduino's LED
  }
  else
  {
    digitalWrite(ledPIN, LOW); // turn OFF Arduino's LED
  }

  // Read the analog interface
  analogVal = analogRead(analogPIN); 
  Serial.print("Flame value: ");
  Serial.println(analogVal); // print analog value to serial

  delay(100);
}