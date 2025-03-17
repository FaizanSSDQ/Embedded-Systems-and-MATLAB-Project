#include "BluetoothSerial.h"
String Data;
BluetoothSerial MyBT;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MyBT.begin("Faizan Bluetooth");
    Serial.println("Bluetooth Device is Ready to Pair");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(MyBT.available())
  {
    Data = MyBT.readString();
    Serial.print(Data);
  }

}
