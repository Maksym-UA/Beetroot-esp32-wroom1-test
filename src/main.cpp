#include <Arduino.h>


const int bootButton = 0; // GPIO0 як пін для кнопки
const int extButton = 17;  // the number of the pushbutton pin
const int bluePin =  5;    // the number of the blue pin
const int redPin =  16;    // the number of the red pin

// Fixed timing intervals
const int  intervalSlow = 1000;
const int intervalFast = 200;

int currentInterval = intervalSlow;
bool isBlinking = false;
bool ledState = LOW;
unsigned long prevMillis = 0;

// Button state tracking
bool lastBootState = HIGH;
bool lastExtState  = HIGH;

void setup() {
    Serial.begin(115200);
    pinMode(bluePin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bootButton, INPUT_PULLUP);
    pinMode(extButton,  INPUT_PULLUP);
    Serial.println("System Ready. Boot=Slow, Ext=Fast");
}

void loop() {
    bool bootState = digitalRead(bootButton);
    bool extState  = digitalRead(extButton);

    // 1. BOOT Button -> Set to SLOW and Toggle ON/OFF
    if (lastBootState == HIGH && bootState == LOW) {
        if (isBlinking && currentInterval == intervalSlow) {
            isBlinking = false; // Stop if already slow
        } else {
            isBlinking = true;
            currentInterval = intervalSlow;
        }
        Serial.println(isBlinking ? "Mode: SLOW" : "Mode: STOPPED");
        delay(50); 
    }
    lastBootState = bootState;

    // 2. External Button -> Set to FAST and Toggle ON/OFF
    if (lastExtState == HIGH && extState == LOW) {
        if (isBlinking && currentInterval == intervalSlow) {
            isBlinking = false; // Stop if already fast
        } else {
            isBlinking = true;
            currentInterval = intervalFast;
        }
        Serial.println(isBlinking ? "Mode: FAST" : "Mode: STOPPED");
        delay(50);
    }
    lastExtState = extState;

    // 3. Non-blocking Blink Logic
    if (isBlinking) {
        if (millis() - prevMillis >= (unsigned long)currentInterval) {
            prevMillis = millis();
            ledState = !ledState;
            digitalWrite(bluePin, ledState);
            delay(50);
            digitalWrite(redPin,ledState);
            delay(50);
        }
    } else {
        digitalWrite(bluePin, LOW); // Keep LED off when stopped
        digitalWrite(redPin, LOW);
    }
}
