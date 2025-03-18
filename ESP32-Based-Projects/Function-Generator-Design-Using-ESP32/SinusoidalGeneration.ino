int ADC=13;
int DAC=26;
float inpV=0;
int ADCV=0;
int deg=0;
void setup() {
  Serial.begin(9600);
  pinMode(13 , INPUT);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  // put your setup code here, to run once:

}

void loop() {
  ADCV=int(128+127*(cos(deg*PI/180)));
  dacWrite(26 , ADCV);
  deg=deg+1;
  if(deg>=360)
  deg=0;
  delay(25);
  inpV=analogRead(ADC);
  Serial.println(inpV*3.3/4096);
  // put your main code here, to run repeatedly:

}
