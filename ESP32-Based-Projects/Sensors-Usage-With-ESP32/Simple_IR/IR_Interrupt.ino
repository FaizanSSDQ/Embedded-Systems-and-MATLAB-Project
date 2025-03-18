
#define IRPin 13 
bool ledState = false;

void IRAM_ATTR IR_Result() {
  ledState = !ledState; // Toggle LED state
}
void setup() {
  // put your setup code here, to run once:
  pinMode(IRPin , INPUT_PULLUP);
  pinMode(2 , OUTPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(IRPin) , IR_Result , FALLING);
  Serial.println("Ready To Detect: ");

}

void loop() {

digitalWrite(2 , ledState);
Serial.println(ledState);

}
