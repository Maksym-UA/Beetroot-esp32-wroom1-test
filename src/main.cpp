#include <Arduino.h>

const int bootButton = 0; // GPIO0 як пін для кнопки

const int buttonPin = 17;  // the number of the pushbutton pin
const int bluePin =  5;    // the number of the blue pin
const int redPin =  16;    // the number of the red pin


bool isBlinking = false;    // Toggle this with the button
bool ledState = LOW;
bool lastButtonState = HIGH;

unsigned long previousMillis = 0;
const long interval = 500;  // Blink speed in milliseconds


void btnBlinkControl(int rLED, int bLED) {
  
   // Мигаємо синім
  Serial.println("Вмикаю СИНІЙ (GPIO 5)");
  digitalWrite(bLED, HIGH);
  delay(50);
  digitalWrite(bLED, LOW);
  delay(50);

  // Мигаємо червоним
  Serial.println("Вмикаю ЧЕРВОНИЙ (GPIO 16)");
  digitalWrite(rLED, HIGH);
  delay(50);
  digitalWrite(rLED, LOW);
  delay(50);
}

void bootBtnBlinkControl(int rLED, int bLED) {
  
   // Мигаємо синім
  Serial.println("Вмикаю СИНІЙ (GPIO 5)");
  digitalWrite(bLED, LOW);
  delay(80);
  digitalWrite(bLED, HIGH);
  delay(80);

  // Мигаємо червоним
  Serial.println("Вмикаю ЧЕРВОНИЙ (GPIO 16)");
  digitalWrite(rLED, LOW);
  delay(80);
  digitalWrite(rLED, HIGH);
  delay(80);
}

void setup() {
  Serial.begin(115200);  
  // initialize the pushbutton pin as an input
  delay(500); // Wait a moment for serial port to initialize
  pinMode(buttonPin, INPUT);
  // initialize the LED pins as an output
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);

  pinMode(bootButton, INPUT_PULLUP); // Встановлюємо GPIO0 як вхід з підтягуванням
  digitalWrite(bluePin, LOW); // led вимкнений на початку
  digitalWrite(redPin, LOW); // led вимкнений на початку

}

void loop() {
  int currentButtonState = digitalRead(bootButton);

  // 1. Check for button press (falling edge)
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        isBlinking = !isBlinking; // Toggle the blinking mode
        
        // If we stop blinking, make sure the LED stays OFF
        if (!isBlinking) {
            digitalWrite(redPin, LOW);
            digitalWrite(bluePin, LOW);
        }
        
        Serial.print("Blinking Mode: ");
        Serial.println(isBlinking ? "ENABLED" : "DISABLED");
        delay(50); // Simple debounce
    }
    lastButtonState = currentButtonState;

    // 2. Handle Blinking (Non-blocking)
    if (isBlinking) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            ledState = !ledState; // Toggle LED state
            digitalWrite(redPin, ledState);
            delay(50);
            digitalWrite(bluePin, ledState);
        }
    }
}