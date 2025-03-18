#include <SPI.h>

//CSN PIN GPIO 5
//CE PIN GPIO 17
void setup() {
  // put your setup code here, to run once:

  SPI.begin();
  Serial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Absolutely Fine");

}
