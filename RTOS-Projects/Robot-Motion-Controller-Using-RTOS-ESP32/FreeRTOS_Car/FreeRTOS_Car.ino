#define LED1 13
#define LED2 2



//#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
//#else
//static const BaseType_t app_cpu = 1;
//#endif

//Function of Task 1
void Toggle_1(void *parameter)
{
  while(1)
  {
    Serial.println("I am Task 1");
    digitalWrite(LED1 , HIGH);
    vTaskDelay(500);
    digitalWrite(LED1 , LOW);
    vTaskDelay(500);
  }
}


//Function of Task 2
void Toggle_2(void *parameter)
{
  while(true)
  {
    Serial.println("I am Task 2");
    digitalWrite(LED2 , HIGH);
    vTaskDelay(500);
    digitalWrite(LED2 , LOW);
    vTaskDelay(500);
  }
}



void setup() {
  // put your setup code here, to run once:
  pinMode(LED1 , OUTPUT);
  pinMode(LED2 , OUTPUT);
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    Toggle_1,
    "Blue LED",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);

  xTaskCreatePinnedToCore(
    Toggle_2,
    "Outer LED",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);
}

void loop() {
  // put your main code here, to run repeatedly:

}
