//CSN 5
//CE 17


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(17, 5); // CE, CSN

struct RotoryData {
    uint8_t message[40];
    int counter;
    unsigned short int Tank_Sr;
    unsigned short int Tank_Freq;
};
RotoryData LocalObject;


//This is Tank_1
uint8_t channelNo = 5;



//0x00,0xDD,0xCC,0xBB,0xAA
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(104);
  radio.openReadingPipe(0, 0xB3B4B5B602);
  radio.setPALevel(RF24_PA_LOW);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("I am working");
  


  if (radio.available()) {
    char Data[32] = "";
    radio.read(&Data, sizeof(Data));
    Serial.print("The Recieved String is : ");
    Serial.println(Data);
    //Serial.println(Receive.text);
    channelNo = radio.getChannel();
    Serial.println();
    Serial.print("The Value of Channel is ");
    Serial.println(channelNo);

   // Serial.print("The Recieved integer is : ");
   // Serial.println(Receive.x);
  }
}
