#include <Arduino.h>

const int buttonPin = 17;  // the number of the pushbutton pin
const int bluePin =  5;    // the number of the blue pin
const int redPin =  16;    // the number of the red pin

// variable for storing the pushbutton status 
int buttonState = 0;

void setup() {
  Serial.begin(115200);  
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  // initialize the LED pins as an output
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH
  if (buttonState == HIGH) {
    // turn LED on
    digitalWrite(bluePin, HIGH);
    digitalWrite(redPin, HIGH);
  } else {
    // turn LED off
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
  }
  // Затримка для антидребезгу та зменшення навантаження
  delay(50);
}