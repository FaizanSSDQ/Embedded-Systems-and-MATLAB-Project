#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the struct
struct RotoryData {
    uint8_t message[40];
    int counter;
  //  unsigned short int Tank_Sr;
  //  unsigned short int Tank_Freq;
  //  uint8_t check;
};

// Create an instance of the struct
RotoryData LocalObject_;

// Create an RF24 object
//RF24 radio(9, 10); // CE, CSN pins
RF24 radio(17, 5); // CE, CSN

// Address variable
uint8_t channelNo = 5;
byte address[10] = "Tank_05_1" ;

void setup() {
    // Start the Serial communication
    Serial.begin(115200);
    
    // Initialize the radio
    radio.begin();
    radio.setChannel(channelNo);
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_2MBPS);
    radio.stopListening();

    // Fill the struct with some data
    strcpy((char*)LocalObject_.message, "Hello from transmitter!");
    LocalObject_.counter = 42;
 //   LocalObject_.Tank_Sr = 123;
   // LocalObject_.Tank_Freq = 456;
   // LocalObject_.check = 55;
}

void loop() {
    // Integer to send
   static int valueToSend = 14;

    // Send the integer
    bool report = radio.write(&valueToSend, sizeof(valueToSend));
    
    if (report) {
        Serial.println("Transmission successful");
    } else {
        Serial.println("Transmission failed");
    }
    valueToSend++;
    delay(1000); // Wait for a second before sending the next packet
}

/*
void loop() {
    // Send the struct
    bool report = radio.write(&LocalObject_, sizeof(LocalObject_));
    Serial.println("Transmitted Data is");



        Serial.print("Message: ");
        Serial.println((char*)LocalObject_.message);
        Serial.print("Counter: ");
        Serial.println(LocalObject_.counter);
      //  Serial.print("Tank_Sr: ");
      //  Serial.println(LocalObject_.Tank_Sr);
      //  Serial.print("Tank_Freq: ");
       // Serial.println(LocalObject_.Tank_Freq);
       // Serial.print("Check Value is :");
       //   Serial.println(LocalObject_.check);
    if (report) {
        Serial.println("Transmission successful");
    } else {
        Serial.println("Transmission failed");
    }
    
    delay(1000); // Wait for a second before sending the next packet
}
*/