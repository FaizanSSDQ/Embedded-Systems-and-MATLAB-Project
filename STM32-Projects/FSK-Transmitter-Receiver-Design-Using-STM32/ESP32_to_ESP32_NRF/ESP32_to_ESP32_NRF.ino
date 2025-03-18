//GPIO Pins 32 and 33
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(2 , OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2 , !(digitalRead(2)));
  Serial.println("I am Tank 1");
  delay(100);


}
