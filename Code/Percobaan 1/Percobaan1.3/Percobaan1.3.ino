#define potensio A2
char pinsCount = 6;
int pins[] = {3, 5, 6, 9, 10, 11};

void lamp (int pin) {
  for (int i = 0; i < 255; i++) {
    analogWrite(pin)
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < pinsCount; i++) {
    pinMode(pins[i], OUTPUT);
  }
}
void loop() {
  int sensorValue = analogRead(potensio);
  Serial.println(sensorValue);
  if (sensorValue < 512) {

  }
  digitalWrite(8, HIGH);
  delay(sensorValue);
  digitalWrite(8, LOW);
  delay(sensorValue);
}
