#define DACPIN 25   //PIN For DAC where we will write any digital value
#define ADCIn 12  //Pin for ADC from where we will read value
float ADCValue=0;  //Variable to Store the vale of ADC which we will read 
int DACV=0;    //DAC Value variale which will store the value that will be written on DAC
int deg=0;     //I dont know
void setup() {

Serial.begin(115200);
pinMode(ADCIn , INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  DACV=int (64+63*(sin(deg*PI/180)));   //her PI is the pie ssymbol whose value is 3.1456863265
  dacWrite(DACPIN , DACV);
  deg=deg+1;
  if(deg=360)
  {
    deg=0;
  }

  delay(1000);

ADCValue=analogRead(ADCIn);
Serial.print("The Value on ADC is : ");
Serial.println(ADCValue*3.3/4096);
Serial.println("------------------------------");
}
