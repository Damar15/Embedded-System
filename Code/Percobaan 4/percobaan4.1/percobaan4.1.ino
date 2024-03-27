// define function
void TaskBlink();
void TaskAnalogRead();
void TaskDigitalRead();

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
  while (!Serial) {
    ;  // wait for serial port to connect
  }
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  TaskBlink();
  TaskAnalogRead();
  TaskDigitalRead();
}
/*--------------------------------------------------*/
/*---------------------- Function ---------------------*/
/*--------------------------------------------------*/

void TaskBlink() {
  /*
 Blink Turns on an LED on for one second, then off for one

 */
  digitalWrite(8, HIGH);  // turn the LED on
  delay(1000);            // wait for one second
  digitalWrite(8, LOW);   // turn the LED off
  delay(1000);            // wait for one second
}
void TaskAnalogRead() {
  /*
 AnalogReadSerial
 Reads an analog input on pin A0, prints the result to the serial
 Graphical representation is available using serial plotter (Tools > Serial Plotter Menu)*/
 // read the input on analog pin 0:
 int sensorValue = analogRead(A0);
 // print out the value you read:
 Serial.println(sensorValue);
 delay(15); // delay (15ms) in between reads for stability
 }
 void TaskDigitalRead()
 {
 /*
 DigitalRead
 Turns on and off a light emitting diode(LED) connected to digital pin 13 (onboard/built in), when pressing a pushbutton attached to pin 2.

 */
  // check if the pushbutton is pressed
  if (digitalRead(2) == HIGH) {
    // turn LED on:
    digitalWrite(13, HIGH);
  } else {
    // turn LED off:
    digitalWrite(13, LOW);
  }
}
