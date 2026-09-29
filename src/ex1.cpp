// IoT 2026 - Lab 2
// ESP32 / Arduino

// -------------------- Pin Configuration --------------------
const int RED_LED    = 26;
const int GREEN_LED  = 27;
const int BLUE_LED   = 14;
const int YELLOW_LED = 12;

const int BUTTON = 25;
const int LIGHT  = 33;

const int SERVO  = 5;
const int BUZZER = 32;

// LCD:
// SDA = 21
// SCL = 22


// ==========================================================
// Exercise 1: LED Chase (Knight Rider)
// ==========================================================

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

const int chaseLength = 6;

int chaseIndex = 0;


// ==========================================================
// Exercise 2: Sensor Statistics
// ==========================================================

unsigned long lastStatsTime = 0;
const unsigned long statsInterval = 1000;


// ==========================================================
// Exercise 3: Sensor Threshold Alert
// ==========================================================

unsigned long lastAlertRead = 0;
const unsigned long alertInterval = 300;

bool alertActive = false;


// ==========================================================
// Exercise 4: Button Press Counter
// ==========================================================

int pressCount = 0;

bool lastButtonState = LOW;


// ==========================================================
// Setup
// ==========================================================

void setup() {
  Serial.begin(115200);

  // LED pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  // Button
  pinMode(BUTTON, INPUT);

  // Light sensor
  pinMode(LIGHT, INPUT);

  // Start with all LEDs OFF
  turnOffAllLEDs();
}


// ==========================================================
// Main Loop
// ==========================================================

void loop() {

  // --------------------------------------------------------
  // Exercise 1: LED Chase
  // --------------------------------------------------------

  turnOffAllLEDs();

  digitalWrite(chaseLEDs[chaseIndex], HIGH);

  Serial.print("chase=");
  Serial.println(chaseNames[chaseIndex]);

  chaseIndex++;

  if (chaseIndex >= chaseLength) {
    chaseIndex = 0;
  }

  delay(150);


  // --------------------------------------------------------
  // Exercise 2: Sensor Statistics
  // --------------------------------------------------------

  if (millis() - lastStatsTime >= statsInterval) {

    lastStatsTime = millis();

    int minimum = 4095;
    int maximum = 0;
    long total = 0;

    // 10 back-to-back samples
    for (int i = 0; i < 10; i++) {

      int reading = analogRead(LIGHT);

      if (reading < minimum) {
        minimum = reading;
      }

      if (reading > maximum) {
        maximum = reading;
      }

      total += reading;
    }

    int average = total / 10;

    Serial.print("min=");
    Serial.print(minimum);

    Serial.print(" max=");
    Serial.print(maximum);

    Serial.print(" avg=");
    Serial.println(average);
  }


  // --------------------------------------------------------
  // Exercise 3: Sensor Threshold Alert with Hysteresis
  // --------------------------------------------------------

  if (millis() - lastAlertRead >= alertInterval) {

    lastAlertRead = millis();

    int lightValue = analogRead(LIGHT);

    // Activate only when above 3000
    if (!alertActive && lightValue > 3000) {

      alertActive = true;

      Serial.println("ALERT=1");
    }

    // Clear only when below 2500
    else if (alertActive && lightValue < 2500) {

      alertActive = false;

      Serial.println("ALERT=0");
    }
  }


  // --------------------------------------------------------
  // Exercise 4: Button Press Counter
  // --------------------------------------------------------

  bool buttonState = digitalRead(BUTTON);

  // Detect LOW -> HIGH transition
  if (buttonState == HIGH && lastButtonState == LOW) {

    pressCount++;

    // Wrap 4 -> 0
    if (pressCount > 4) {
      pressCount = 0;
    }

    Serial.print("count=");
    Serial.println(pressCount);

    updateButtonPattern();
  }

  lastButtonState = buttonState;
}


// ==========================================================
// Turn all LEDs OFF
// ==========================================================

void turnOffAllLEDs() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}


// ==========================================================
// Exercise 4 LED Pattern
// ==========================================================

void updateButtonPattern() {

  turnOffAllLEDs();

  if (pressCount >= 1) {
    digitalWrite(RED_LED, HIGH);
  }

  if (pressCount >= 2) {
    digitalWrite(GREEN_LED, HIGH);
  }

  if (pressCount >= 3) {
    digitalWrite(YELLOW_LED, HIGH);
  }

  if (pressCount >= 4) {
    digitalWrite(BLUE_LED, HIGH);
  }
}
