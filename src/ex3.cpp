#include <Arduino.h>

// Light sensor
const int LIGHT = 33;

// Timing
unsigned long previousMillis = 0;
const unsigned long interval = 300;

// Alert state
bool alertActive = false;

void setup() {
  Serial.begin(115200);

  pinMode(LIGHT, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // Read light sensor
    int lightValue = analogRead(LIGHT);

    // Activate alert above 3000
    if (!alertActive && lightValue > 3000) {

      alertActive = true;

      Serial.println("ALERT=1");
    }

    // Clear alert below 2500
    else if (alertActive && lightValue < 2500) {

      alertActive = false;

      Serial.println("ALERT=0");
    }
  }
}
