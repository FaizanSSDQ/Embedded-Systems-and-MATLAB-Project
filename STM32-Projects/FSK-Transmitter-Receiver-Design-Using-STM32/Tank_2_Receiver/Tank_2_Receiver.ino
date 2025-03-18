//CSN 5
//CE 17

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(17, 5); // CE, CSN

struct RotoryData {
    uint8_t message[40];
    int counter;
    //unsigned short int Tank_Sr;
    //unsigned short int Tank_Freq;
    //uint8_t check;
};



//This is Tank_2
uint8_t channelNo = 70;
byte address[10] = "Tank_70_2" ;



//0x00,0xDD,0xCC,0xBB,0xAA
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(channelNo);
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
  radio.startListening();

}

void loop() {
    if (radio.available()) {
        // Variable to store the received integer
        int receivedValue = 0;

        // Read the incoming integer
        radio.read(&receivedValue, sizeof(receivedValue));
        
        // Print out the received integer
        Serial.print("Received Value: Tank 2  ");
        Serial.println(receivedValue);
    }
}


/*

void loop() {
    if (radio.available()) {
      RotoryData LocalObject;
        // Read the incoming data into the struct
        radio.read(&LocalObject, sizeof(LocalObject));
        delay(10);
        // Print out the received data
        Serial.print("Message: ");
        Serial.println((char*)LocalObject.message);
        Serial.print("Counter: ");
        Serial.println(LocalObject.counter);
        Serial.print("Tank_Sr: ");
      //  Serial.println(LocalObject.Tank_Sr);
        Serial.print("Tank_Freq: ");
       // Serial.println(LocalObject.Tank_Freq);
        Serial.print("Check Value is :");
       // Serial.println(LocalObject.check);
    }
  


 
}
*/
