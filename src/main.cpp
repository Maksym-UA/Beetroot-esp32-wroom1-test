#include <Arduino.h>

const int bluePin = 4; 
const int redPin = 5;


void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Система запущена!");

  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
}

void loop() {
  // Мигаємо синім
  Serial.println("Вмикаю СИНІЙ (GPIO 5)");
  digitalWrite(bluePin, HIGH);
  delay(50);
  digitalWrite(bluePin, LOW);
  delay(50);

  // Мигаємо червоним
  Serial.println("Вмикаю ЧЕРВОНИЙ (GPIO 4)");
  digitalWrite(redPin, HIGH);
  delay(50);
  digitalWrite(redPin, LOW);
  delay(50);
}
