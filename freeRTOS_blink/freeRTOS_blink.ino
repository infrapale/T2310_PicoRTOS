#include <FreeRTOS.h>
#include <task.h>

#define LED_1  2
#define LED_2  3

void setup() {
  // put your setup code here, to run once:
  xTaskCreate(blink1,"BLINK1",128,nullptr,1,nullptr);
  xTaskCreate(blink2,"BLINK2",128,nullptr,1,nullptr);
  pinMode(LED_1,OUTPUT);

}

void setup1() {
  // put your setup code here, to run once:
  pinMode(LED_1,OUTPUT);

}


void blink1(void *param) {
  (void) param;
  pinMode(LED_1,OUTPUT);
  while(true)
  {
    digitalWrite(LED_1,LOW);
    delay(100);
    digitalWrite(LED_1,HIGH);
    delay(100);
  }
}

void blink2(void *param) {
  (void) param;
  pinMode(LED_2,OUTPUT);
  while(true)
  {
    digitalWrite(LED_2,LOW);
    delay(500);
    digitalWrite(LED_2,HIGH);
    delay(500);
  }
}

void loop() 
{
  delay(500);
}
