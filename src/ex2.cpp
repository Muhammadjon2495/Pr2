#include <Arduino.h>

// Light sensor
const int LIGHT = 33;

// Statistics interval
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

void setup() {
  Serial.begin(115200);

  pinMode(LIGHT, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // Initial values
    int minimum = 4095;
    int maximum = 0;
    long total = 0;

    // Take exactly 10 back-to-back samples
    for (int i = 0; i < 10; i++) {

      int value = analogRead(LIGHT);

      if (value < minimum) {
        minimum = value;
      }

      if (value > maximum) {
        maximum = value;
      }

      total += value;
    }

    // Calculate average
    int average = total / 10;

    // Print result
    Serial.print("min=");
    Serial.print(minimum);

    Serial.print(" max=");
    Serial.print(maximum);

    Serial.print(" avg=");
    Serial.println(average);
  }
}
