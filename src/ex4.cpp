#include <Arduino.h>

// LED pins
const int RED_LED = 26;
const int GREEN_LED = 27;
const int YELLOW_LED = 12;
const int BLUE_LED = 14;

// Button
const int BUTTON = 25;

// Counter
int count = 0;

// Previous button state
bool previousButtonState = LOW;

void setup() {
  Serial.begin(115200);

  // LED setup
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Button setup
  pinMode(BUTTON, INPUT);

  // All LEDs OFF
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void loop() {

  // Read current button state
  bool currentButtonState = digitalRead(BUTTON);

  // Detect LOW -> HIGH edge
  if (currentButtonState == HIGH && previousButtonState == LOW) {

    // Increase counter
    count++;

    // Wrap 4 -> 0
    if (count > 4) {
      count = 0;
    }

    // Print counter
    Serial.print("count=");
    Serial.println(count);

    // Turn all LEDs OFF first
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    // Light LEDs according to counter
    if (count >= 1) {
      digitalWrite(RED_LED, HIGH);
    }

    if (count >= 2) {
      digitalWrite(GREEN_LED, HIGH);
    }

    if (count >= 3) {
      digitalWrite(YELLOW_LED, HIGH);
    }

    if (count >= 4) {
      digitalWrite(BLUE_LED, HIGH);
    }
  }

  // Save current state
  previousButtonState = currentButtonState;
}
