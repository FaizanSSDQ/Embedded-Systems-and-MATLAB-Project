#define PotentioPIN 12

int value;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(PotentioPIN);
  Serial.print("Val: ");
  Serial.println(value);

}
