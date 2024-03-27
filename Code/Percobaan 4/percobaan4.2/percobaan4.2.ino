#include <Arduino_FreeRTOS.h>
// 1. define tasks
void TaskBlink(void *pvParameters);
void TaskAnalogRead(void *pvParameters);
void TaskDigitalRead(void *pvParameters);

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // 2. Creating Task
  while (!Serial) {
    ;  // wait for serial port to connect
  }
  // Now set up tasks to run independently
  xTaskCreate(
    TaskBlink,
    "Blink",  // A name just for humans
    128,      // stack size
    NULL,
    2,  // Priority, with 3 being the highest, 0 being the lowest
    NULL);

  xTaskCreate(
    TaskAnalogRead,
    "AnalogRead",
    128,
    NULL,
    1,  // Priority
    NULL);

  xTaskCreate(
    TaskDigitalRead,
    "DigitalRead",
    128,  // Stack size
    NULL,
    1,  // Priority
    NULL);

  // Now the task scheduler is automatically started
}

void loop() {
  // Empty
}


// 4. Isikan perintah pada task
/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task
{
  (void)pvParameters;

  /* Blink Turns on an LED on for one second, then off for one*/

  // initialize digital pin 8 as an output
  pinMode(8, OUTPUT);

  for (;;)  // A Task shall never return or exit
  {
    digitalWrite(8, HIGH);                  // turn the LED on
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one second
    digitalWrite(8, LOW);                   // turn the LED off
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one second
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task
{
  (void)pvParameters;
  /* AnalogReadSerial Reads an analog input on pin A0, 
  prints the result to the serial Graphical representation is available using serial plotter*/
  for (;;) {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorValue);
      // one tick delay (15ms) in between reads for stability
      vTaskDelay(1);
  }
}

void TaskDigitalRead(void *pvParameters)  // This is a task
{
  (void)pvParameters;
  /*DigitalRead Turns on and off a light emitting diode(LED) connected to*/
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);

  for (;;) {
    if (digitalRead(2) == HIGH) {
      // turn LED on:
      digitalWrite(13, HIGH);
    } else {
      // turn LED off:
      digitalWrite(13, LOW);
    }
  }
}




xTaskCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName, 
                            const configSTACK_DEPTH_TYPE uxStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask )


/*
pxTaskCode = Merefer ke task function yang telah kita buat
pcName = Deskripsi nama yang digunakan untuk proses debugging
uxStackDepth = Stack size atau memory yang kita gunakan  --> perlu diperhatikan pada setiap MCU yang kita gunakan karena stack 32-bit
pvParameters = Task input parameters (ini di NULL kan saja)
uxPriority = Task priority (0 merupakan priority terendah)
pxCreatedTask = Argumen yang dapat digunakan untuk merubah task priority atau men-delete sebuah task (jika tidak difungsikan maka NULL)
*/ 



