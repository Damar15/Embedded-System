#define potensio A2
char pinsCount = 6;
int pins[] = { 3, 5, 6, 9, 10, 11 };
int sensorValue = 0;


void lampAnalog(int pin) {
  sensorValue = analogRead(potensio);
  Serial.println(sensorValue);
  for (int i = 0; i <= 255; i++) {
    analogWrite(pins[pin], i);
    delay(5);
  }

  for (int i = 255; i >= 0; i--) {
    analogWrite(pins[pin], i);
    delay(5);
  }
}

void lampDigital(int pin) {
  sensorValue = analogRead(potensio);
  Serial.println(sensorValue);
  digitalWrite(pins[pin], HIGH);
  delay(1000);
  digitalWrite(pins[pin], LOW);
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < pinsCount; i++) {
    pinMode(pins[i], OUTPUT);
  }
}
void loop() {
  sensorValue = analogRead(potensio);
  Serial.println(sensorValue);
  if (sensorValue < 512) {
    for (int pin = 0; pin < 3; pin++) {
      lampAnalog(pin);
      if (sensorValue > 512) {
        break;
      }
    }

    for (int pin = 2; pin >= 0; pin--) {
      lampAnalog(pin);
      if (sensorValue > 512) {
        break;
      }
    }
  } else if (sensorValue > 512) {
    for (int pin = 3; pin < pinsCount; pin++) {
      lampDigital(pin);
      if (sensorValue < 512) {
        break;
      }
    }

    for (int pin = 5; pin >= 3; pin--) {
      lampDigital(pin);
      if (sensorValue < 512) {
        break;
      }
    }
  }
}
