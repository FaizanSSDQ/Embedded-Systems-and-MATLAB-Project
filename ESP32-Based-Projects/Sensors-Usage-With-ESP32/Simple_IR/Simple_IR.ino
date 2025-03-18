#define IRPin 13 
void setup() {
  // put your setup code here, to run once:
  pinMode(IRPin , INPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(IRPin)==HIGH)
  {
    Serial.println("--NO--");
  }
  else if (digitalRead(IRPin)==LOW)
  {
    Serial.println("Obstacle..");
  }
  else
  {
    Serial.println("-------------");
  }
}
