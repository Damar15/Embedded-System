#define LED_MERAH_PEDESTRIAN 4
#define LED_HIJAU_PEDESTRIAN 5
#define LED_MERAH 8
#define LED_KUNING 9
#define LED_HIJAU 10
#define TOMBOL 2
#define buzzer A1

int state = 0;
int input_sblm = HIGH;
int tepi_naik = HIGH;

unsigned long waktu_debouncing = 0;
unsigned long delay_debouncing = 50;

int input = LOW;
int kondisi_sblm = LOW;

unsigned long waktu_state = 0;
unsigned long delay_state = 5000;

void state_1();
void state_2();
void state_3();
void state_4();

void setup() {
  pinMode(LED_MERAH_PEDESTRIAN, OUTPUT);
  pinMode(LED_HIJAU_PEDESTRIAN, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(TOMBOL, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  int kondisi = digitalRead(TOMBOL);
  Serial.print("Nilai tombol: ");
  Serial.println(kondisi);
  if (kondisi != kondisi_sblm) {
    waktu_debouncing = millis();
  }
  if ((millis() - waktu_debouncing) > delay_debouncing) {
    if (kondisi != input) {
      input = kondisi;
    }
  }
  kondisi_sblm = kondisi;
  if (input == LOW && input_sblm == HIGH) {
    input_sblm = input;
  } else if (input == HIGH && input_sblm == LOW) {
    input_sblm = input;
    tepi_naik = LOW;
  }
  switch (state) {
    case 1:
      state_1();
      Serial.print("Nilai waktu state: ");
      Serial.println(millis() - waktu_state);
      if ((millis() - waktu_state) > 10000) {
        state = 2;
        waktu_state = millis();
      }
      break;
    case 2:
      state_2();
      Serial.print("Nilai waktu state: ");
      Serial.println(millis() - waktu_state);
      if (tepi_naik == LOW) {
        state = 4;
        waktu_state = millis();
      } else if ((millis() - waktu_state) > 1500) {
        state = 3;
        waktu_state = millis();
      }
      break;
    case 3:
      state_3();
      Serial.print("Nilai waktu state: ");
      Serial.println(millis() - waktu_state);
      if (tepi_naik == LOW) {
        state = 4;
        waktu_state = millis();
      } else if ((millis() - waktu_state) > 8000) {
        state = 1;
        waktu_state = millis();
      }
      break;
    case 4:
      state_4();
      state = 1;
      waktu_state = millis();
      break;
    default:
      state = 1;
      waktu_state = millis();
      break;
  }
  tepi_naik = HIGH;
}
void state_1() {
  digitalWrite(LED_MERAH, HIGH);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH_PEDESTRIAN, LOW);
  digitalWrite(LED_HIJAU_PEDESTRIAN, HIGH);
  Serial.println("Masuk state 1");
}
void state_2() {
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_KUNING, HIGH);
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH_PEDESTRIAN, LOW);
  digitalWrite(LED_HIJAU_PEDESTRIAN, LOW);
  Serial.println("Masuk state 2");
}
void state_3() {
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_HIJAU, HIGH);
  digitalWrite(LED_MERAH_PEDESTRIAN, HIGH);
  digitalWrite(LED_HIJAU_PEDESTRIAN, LOW);
  Serial.println("Masuk state 3");
}
void state_4() {
  digitalWrite(LED_KUNING, LOW);
  for (int i = 0; i < 6; i++) {
    tone(buzzer, 2000, 500);  
    digitalWrite(LED_KUNING, HIGH);
    delay(500);         
    digitalWrite(LED_KUNING, LOW);
    noTone(buzzer);      
    delay(500);
  }
  Serial.println("Masuk state 4");
}