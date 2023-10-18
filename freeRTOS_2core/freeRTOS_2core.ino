/**
https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial1-creating-freertos-task-to-blink-led-in-arduino-uno

https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial-using-semaphore-and-mutex-in-freertos-with-arduino


 */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define LED_1  2
#define LED_2  3

SemaphoreHandle_t  sema_v; 
SemaphoreHandle_t mutex_v;

void setup() 
{
  delay(2000);
  Serial.begin(115200);  
}



void setup1() 
{
  mutex_v = xSemaphoreCreateMutex(); 
  if (mutex_v == NULL) 
  { 
    Serial.println("Mutex can not be created"); 
  } 
  xTaskCreate(blink1,"BLINK1",128,nullptr,1,nullptr);
  xTaskCreate(blink2,"BLINK2",128,nullptr,1,nullptr);
  sema_v = xSemaphoreCreateBinary();

  pinMode(LED_BUILTIN,OUTPUT);

}


void blink1(void *param) {
  (void) param;
  pinMode(LED_1,OUTPUT);
  while(true)
  {
    xSemaphoreTake(mutex_v, portMAX_DELAY); 
    digitalWrite(LED_1,LOW);
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    digitalWrite(LED_1,HIGH);
    xSemaphoreGive(mutex_v); 
    vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
}

void blink2(void *param) {
  (void) param;
  pinMode(LED_2,OUTPUT);
  while(true)
  {
    xSemaphoreTake(mutex_v, portMAX_DELAY); 
    digitalWrite(LED_2,LOW);
    delay(500);
    digitalWrite(LED_2,HIGH);
    xSemaphoreGive(mutex_v); 
    delay(500);
  }
}

void loop() 
{
  taskDebugInfo();
  delay(250);
}

void loop1()
{
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(250);

}

void taskDebugInfo() {
  int numberOfTasks = uxTaskGetNumberOfTasks();
  TaskStatus_t *pxTaskStatusArray = new TaskStatus_t[numberOfTasks];
  unsigned long runtime;
  numberOfTasks = uxTaskGetSystemState( pxTaskStatusArray, numberOfTasks, &runtime );
  Serial.printf("# Tasks: %d\n", numberOfTasks);
  for (int i=0; i < numberOfTasks; i++) {
    Serial.printf("ID: %d %-7s", i, pxTaskStatusArray[i].pcTaskName);
    int currentState = pxTaskStatusArray[i].eCurrentState;
    switch(currentState){
      case 0:
      Serial.printf(" Current State running  ");
      break;
      case 1:
      Serial.printf(" Current State ready    ");
      break;
      case 2:
      Serial.printf(" Current State blocked  ");
      break;
      case 3:
      Serial.printf(" Current State suspended");
      break;
      case 4:
      Serial.printf(" Current State deleted  ");
      break;
    }
    
   
    Serial.printf(" Priority %-2d", pxTaskStatusArray[i].uxCurrentPriority);
    Serial.printf(" Freestack %-3d", pxTaskStatusArray[i].usStackHighWaterMark);
    Serial.printf(" Runtime %-9d\n", pxTaskStatusArray[i].ulRunTimeCounter);
  
  }
  delete[] pxTaskStatusArray;
}

