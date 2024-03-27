#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores

/* Declare a mutex Semaphore Handle which we will use to manage the
 It will be used to ensure only one Task is accessing
*/
SemaphoreHandle_t xSerialSemaphore;

// define two Tasks for DigitalRead & AnalogRead
void TaskDigitalRead(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

// the setup function runs once when you press reset or power the

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect
  }

  /* Semaphores are useful to stop a Task proceeding, where it

 Semaphores should only be used whilst the scheduler
*/
  if (xSerialSemaphore == NULL)
  // confirm that the Serial Semaphore has not already been created
  {
    xSerialSemaphore = xSemaphoreCreateMutex();
    // Create a mutex semaphore we will use to manage the Serial Port
    if ((xSerialSemaphore) != NULL)
      xSemaphoreGive((xSerialSemaphore));
    // Make the Serial Port available for use, by "Giving" the
  }

  // Now set up two Tasks to run independently
  xTaskCreate(
    TaskDigitalRead, 
    "DigitalRead",  // A name just for humans
    128,  // Stack size
    NULL,  //Parameters for the task
    2,  // Priority, 3 being the highest, and 0 being the lowest
    NULL);  //Task Handle

  xTaskCreate(
    TaskAnalogRead, 
    "AnalogRead", 
    128, 
    NULL,
    1, 
    NULL);

  // Now the Task scheduler is automatically started
}

void loop() {
  // Empty Things are done in Tasks
}
/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskDigitalRead(void *pvParameters __attribute__((unused)))
// This is a Task
{
  /*
 DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial

 */

  // digital pin 2 has a pushbutton attached to it
  uint8_t pushButton = 2;

  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);

  for (;;)  // A Task shall never return or exit
  {
    // read the input pin:
    int buttonState = digitalRead(pushButton);

    /* See if we can obtain or "Take" the Serial Semaphore
 If the semaphore is not available, wait 5 ticks of the Scheduler

 if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) ==

 {
 /* We were able to obtain or "Take" the semaphore and can now
 We want to have the Serial Port for us

*/
    // print out the state of the button:
    Serial.println(buttonState);
    xSemaphoreGive(xSerialSemaphore);
    // Now free or "Give" the Serial Port for others
  }
}

void TaskAnalogRead(void *pvParameters __attribute__((unused)))

{

  for (;;) {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);

    /* See if we can obtain or "Take" the Serial Semaphore If the

*/
 if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE{
 /* We were able to obtain or "Take" the semaphore and
 We want to have the Serial Port

*/
    // print out the value you read:
    Serial.println(sensorValue);
    xSemaphoreGive(xSerialSemaphore);
    // Now free or "Give" the Serial Port for others
  }
  vTaskDelay(1);
  // one tick delay (15ms) in between ADC reads for stability
}
