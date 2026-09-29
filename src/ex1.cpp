#include <Arduino.h>

// LED pins
const int RED_LED = 26;
const int GREEN_LED = 27;
const int YELLOW_LED = 12;
const int BLUE_LED = 14;

// Chase sequence
const int chaseLEDs[] = {
  RED_LED,
  GREEN_LED,
  YELLOW_LED,
  BLUE_LED,
  YELLOW_LED,
  GREEN_LED
};

const char* chaseNames[] = {
  "RED",
  "GREEN",
  "YELLOW",
  "BLUE",
  "YELLOW",
  "GREEN"
};

// Step index
int stepIndex = 0;

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // All LEDs OFF initially
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void loop() {
  // Turn all LEDs OFF
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  // Turn on current LED
  digitalWrite(chaseLEDs[stepIndex], HIGH);

  // Print LED name
  Serial.print("chase=");
  Serial.println(chaseNames[stepIndex]);

  // Move to next step
  stepIndex++;

  if (stepIndex >= 6) {
    stepIndex = 0;
  }

  // Exactly one step delay
  delay(150);
}
