#include <LiquidCrystal.h>

const int PIN_LM35 = A0;
const int PIN_LED  = 8;
const int PIN_BUZ  = 9;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZ, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Temp system ON");
  delay(1000);
}

int readADCStable() {
  analogRead(PIN_LM35);
  delayMicroseconds(200);
  long sum = 0;
  for (int i = 0; i < 32; i++) {
    sum += analogRead(PIN_LM35);
    delay(3);
  }
  return (int)(sum / 32);
}

void loop() {
  int adc = readADCStable();
  float voltage = adc * (5.0 / 1023.0);   
  float tempValue = voltage * 100.0;      /
  Serial.print("Temperature: ");
  Serial.println(tempValue, 2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempValue, 1);
  lcd.print((char)223);
  lcd.print("C");

  if (tempValue > 27) {
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_BUZ, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("ALERTA CALDURA!");
  } else {
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_BUZ, LOW);
    lcd.setCursor(0, 1);
    lcd.print("OK, TEMP NORMAL ");
  }

  delay(1000);
}
