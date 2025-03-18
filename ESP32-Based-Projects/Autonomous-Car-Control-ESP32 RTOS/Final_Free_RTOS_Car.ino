//START OF HEADER FILE SECTION......................
#include <NewPing.h>
//END OF HEADER FILE SECTION........................



#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//START OF USER DEFINITIONS..........................
//Motor Driver 1

//Front L   Motor A
#define ENA_1 23 
#define IN1_1 22
#define IN2_1  1

//Front R    Motor B
#define IN3_1 3
#define IN4_1 21
#define ENB_1 19


//Motor Driver 2
//Back L    Motor A
#define ENA_2 18
#define IN1_2 5
#define IN2_2  17

//Back R    Motor B
#define IN3_2 16
#define IN4_2 4
#define ENB_2 2

//IR Sensor PINS
#define IR1 41
#define IR2 42

//Sharp Sensor PINS
#define Sharp1 51
#define Sharp2 52

//Ultrasonic Sensor PINS
#define Trig 61
#define Echo 62
#define Maxdis 400

//END OF USER DEFINITIONS.........................................

// START OF USER DEFINED OBJECTS...................................
NewPing sonar(Trig , Echo , Maxdis);
//END OF USER DEFINED OBJECTS......................................


//START OF USER VARIABLES......................................
short int x;
bool IR_Sensor;
bool IRS1;
bool IRS2;

short int IR_Value;
float US_Value;
float Moving_USValue[6];
float Sharp_Value1;
float Sharp_Value2;


//END OF USER VARIALES............................................


//START OF RTOS TASK FUNCTIONS.......................................
//IR Sensor Monitoring //Sensor 1 //Sensor 2
void IR_1 (void *parameter)
{
while(1)
{     
  
  if(digitalRead(IR1)==0 && digitalRead(IR2)==0 ) //No Detection
  {
    IR_Value = 0;
  }
   if(digitalRead(IR1)==0 && digitalRead(IR2)==1 ) //Left OFF Right ON
  {
    IR_Value = 1;
  }
   if(digitalRead(IR1)==1 && digitalRead(IR2)==0 ) //Left ON Right OFF
  {
    IR_Value = 2;
  }
   if(digitalRead(IR1)==1 && digitalRead(IR2)==1 ) //Both ON
  { 
    IR_Value = 3;
  }
}


}

/*void IR_2 (void *parameter)
{
  while(1)
  {

  }
}
*/

//Sharp Sensor 1 
void Sharp_1 (void *parameter)
{
  while(1)
  {
  float x=0;
  float distance;
  x = analogRead(Sharp1)*0.0008056640625;
  Sharp_Value1 = 13*pow(x , -1);
  vTaskDelay(50);
  
  }
}

//Sharp Sensor 2
void Sharp_2 (void *parameter)
{
  while(1)
  {
  float x=0;
  float distance;
  x = analogRead(Sharp2)*0.0008056640625;
  Sharp_Value1 = 13*pow(x , -1);
  vTaskDelay(50);
  
  }
}

void UltraSonic (void *parameter)
{
  while(1)
  {
  float Temp;
  float Dis;
  for (int i = 1; i<=5 ; i++)
  {
    Dis  = sonar.ping_cm();
    Temp = Temp + Dis;
  }
  US_Value = Temp/5;
  }
}

void Controller (void *parameter)
{
  while(1)
  {
    if (US_Value >15 && IR_Value ==2 && Sharp_Value1 > 15 && Sharp_Value2 > 15    )
    {
        Forward();
    }
    else
    Serial.print("Failed....");

  }
}

//END OF RTOS TASK FUNCTIONS......................................





void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

pinMode(IN1_1 , OUTPUT);
pinMode(IN2_1 , OUTPUT);
pinMode(IN3_1 , OUTPUT);
pinMode(IN4_1 , OUTPUT);
pinMode(IN1_2 , OUTPUT);
pinMode(IN1_2 , OUTPUT);
pinMode(IN1_2 , OUTPUT);
pinMode(IN1_2 , OUTPUT);


analogWrite(ENA_1 , 255);
analogWrite(ENB_1 , 255);
analogWrite(ENA_2 , 255);
analogWrite(ENA_2 , 255);


//Task to invoke 

//IR Sensor Task
xTaskCreatePinnedToCore(
    IR_1,
    "Invoking IR",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);

//Sharp Sensor Task
xTaskCreatePinnedToCore(
    Sharp_1,
    "Invoking Sharp",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);

xTaskCreatePinnedToCore(
    UltraSonic,
    "Invoking Ultrasonic",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);

xTaskCreatePinnedToCore(
    Controller,
    "Main Controller Task",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);






}

void loop() {
  // put your main code here, to run repeatedly:

}


void Forward()
{

  Serial.print("Moving Forward.....");
  //Motor F-L
  digitalWrite(IN1_1 , HIGH);
  digitalWrite(IN2_1 , LOW);
  //Motor F-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
  //Motor B-L
  digitalWrite(IN1_2 , HIGH);
  digitalWrite(IN2_2 , LOW);
  //Motor B-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
  
}

void Stop()
{
    Serial.print("Stpped..");
  //Motor F-L
  digitalWrite(IN1_1 , LOW);
  digitalWrite(IN2_1 , LOW);
  analogWrite(ENA_1 , 0);

  //Motor F-R
  digitalWrite(IN3_1 , LOW);
  digitalWrite(IN4_1 , LOW);
  analogWrite(ENB_1 , 0);

  //Motor B-L
  digitalWrite(IN1_2 , LOW);
  digitalWrite(IN2_2 , LOW);
  analogWrite(ENA_2 , 0);

  //Motor B-R
  digitalWrite(IN3_1 , LOW);
  digitalWrite(IN4_1 , LOW);
  analogWrite(ENA_2 , 0);

}


void Backword()
{
    Serial.print("Moving Backward....");
    //Motor F-L
  digitalWrite(IN1_1 , LOW);
  digitalWrite(IN2_1 , HIGH);
  //Motor F-R
  digitalWrite(IN3_1 , LOW);
  digitalWrite(IN4_1 , HIGH);
  //Motor B-L
  digitalWrite(IN1_2 , LOW);
  digitalWrite(IN2_2 , HIGH);
  //Motor B-R
  digitalWrite(IN3_1 , LOW);
  digitalWrite(IN4_1 , HIGH);

}

void FullLeft()
{
    Serial.print("Moving Full left....");
  //Motor F-L
  digitalWrite(IN1_1 , LOW);
  digitalWrite(IN2_1 , LOW);
  //Motor F-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
  //Motor B-L
  digitalWrite(IN1_2 , LOW);
  digitalWrite(IN2_2 , LOW);
  //Motor B-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
}
void HalfLeft()
{
    //Motor F-L
  digitalWrite(IN1_1 , HIGH);
  digitalWrite(IN2_1 , LOW);
  analogWrite(ENA_1 , 100);

  //Motor F-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
  analogWrite(ENB_1 , 255);

  //Motor B-L
  digitalWrite(IN1_2 , HIGH);
  digitalWrite(IN2_2 , LOW);
  analogWrite(ENA_2 , 100);

  //Motor B-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
  analogWrite(ENA_2 , 255);
}

void FullRight()
{
      //Motor F-L
  digitalWrite(IN1_1 , HIGH);
  digitalWrite(IN2_1 , LOW);
  //Motor F-R
  digitalWrite(IN3_1 , LOW);
  digitalWrite(IN4_1 , LOW);
  //Motor B-L
  digitalWrite(IN1_2 , HIGH);
  digitalWrite(IN2_2 , LOW);
  //Motor B-R
  digitalWrite(IN3_1 , LOW);
  digitalWrite(IN4_1 , LOW);
}
void HalfRight()
{

    //Motor F-L
  digitalWrite(IN1_1 , HIGH);
  digitalWrite(IN2_1 , LOW);
  analogWrite(ENA_1 , 255);

  //Motor F-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
  analogWrite(ENB_1 , 100);

  //Motor B-L
  digitalWrite(IN1_2 , HIGH);
  digitalWrite(IN2_2 , LOW);
  analogWrite(ENA_2 , 255);

  //Motor B-R
  digitalWrite(IN3_1 , HIGH);
  digitalWrite(IN4_1 , LOW);
  analogWrite(ENA_2 , 100);

}



