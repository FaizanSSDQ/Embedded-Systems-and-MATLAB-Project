#define relayPIN 4 //Relay Pin
#define LED2 2 //Indication LED
String val;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relayPIN , OUTPUT);
  pinMode(LED2 , OUTPUT);
  Serial.println("Enter - H - To Turn ON LED | Enter - L - To Turn OFF LED ");
}
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    val = Serial.readStringUntil('\n');
    Serial.println(val);
    val.trim();
    if (val == "H")
    {
        digitalWrite(LED2 , HIGH);
        digitalWrite(relayPIN , LOW);
        Serial.println("Loop");
    }
    else
    {
        digitalWrite(LED2 , LOW);
        digitalWrite(relayPIN , HIGH);
        Serial.println("No Loop");
    }
  }

}
