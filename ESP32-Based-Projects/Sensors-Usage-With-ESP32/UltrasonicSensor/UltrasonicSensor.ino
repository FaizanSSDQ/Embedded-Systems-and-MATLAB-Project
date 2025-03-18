#include "NewPing.h"
#define TrigPin 12
#define EchoPin 13
#define Max_Dist 390
NewPing MySonar(TrigPin , EchoPin , Max_Dist);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Distance = ");
	Serial.print(MySonar.ping_cm());
	Serial.println(" cm");
	delay(500);

}
