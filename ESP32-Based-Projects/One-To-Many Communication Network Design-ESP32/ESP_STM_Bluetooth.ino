
#include "BluetoothSerial.h"
#include <ESP32Servo.h>

BluetoothSerial SerialBT;

//RTOS
TaskHandle_t TaskHandle_BLE;
Servo servo1;


//Begin User Defined PINs==============================================
#define servoPin 15
#define LED 2
//End User Defined PINs ===============================================


//String MACadd = "98:D3:32:11:31:37";
String MACadd = "00:23:00:01:0D:3F";
uint8_t address[6] = {0x00, 0x23, 0x00, 0x01, 0x0D, 0x3F};
//uint8_t address[6]  = {0x98, 0xD3, 0x32, 0x11, 0x31, 0x37};
//uint8_t address[6]  = {0x11, 0x1D, 0xA5, 0x02, 0xC3, 0x22};
String name = "TANK-1";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;
int angle;

void setup() {
  Serial.begin(115200);
  Bluetooth_Begin();
  pinMode(servoPin , OUTPUT);
   servo1.attach(servoPin);
  xTaskCreate(Bluetooth_Handle, "Task1", 16384, NULL, 1, &TaskHandle_BLE);
  
}

void loop() {
 
}

void Bluetooth_Begin()
{
SerialBT.begin("Monopoly", true); 
  SerialBT.setPin(pin);
  Serial.println("The device started in master mode, make sure Your HC-05 device is on!"); 

  connected = SerialBT.connect(address);

  if(connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
  // disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();
} //Bluetooth_Begin() end


//Function of RTOS Task
void Bluetooth_Handle(void* pvParameters)
{
  for(;;)
  {

    if ( SerialBT.available()) {
    String receivedData = "";
    while (SerialBT.available()) {  
      char c = SerialBT.read();
      receivedData += c;
    }
    // Print the received data to the Serial Monitor
    Serial.print("Received: ");
    Serial.println(receivedData);

    // Convert the received string to an integer
    int receivedInteger = receivedData.toInt();
    Serial.print("Received Integer: ");
    Serial.println(receivedInteger);
    angle = receivedInteger;
    servo1.write(angle);
//    Handle_Servo(receivedInteger);
  }

  }

} //Bluetooth_Handle end

void Handle_Servo(int angle)
{
 
}// Handle_Servo end