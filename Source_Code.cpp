
/*
  PROJECT: AUTO-ALIGNING SOLAR TRACKER
  BOARD: Arduino Nano (ATmega328P)
  MOTOR DRIVER: L9110
  SERIAL MONITOR: 9600 BAUD

  FEATURES:
  1. Dual LDR light detection
  2. Automatic left/right tracking
  3. Potentiometer sensitivity adjustment
  4. Solar panel voltage measurement
  5. Short motor movements
  6. Settling interval between movements
*/

// =============== PIN CONFIGURATION ===============

const int LDR_LEFT  = A0;
const int LDR_RIGHT = A1;
const int POT_PIN   = A2;
const int SOLAR_PIN = A3;

const int MOTOR_IN1 = 5;
const int MOTOR_IN2 = 6;

// =============== TRACKING SETTINGS ===============

const int MIN_THRESHOLD = 30;
const int MAX_THRESHOLD = 180;

const unsigned long MOTOR_PULSE_TIME = 50;
const unsigned long SETTLE_TIME = 1000;
const unsigned long PRINT_INTERVAL = 500;

// =============== VARIABLES ===============

unsigned long lastPrintTime = 0;

int leftValue = 0;
int rightValue = 0;
int difference = 0;
int threshold = 0;
int potValue = 0;
int solarReading = 0;

float solarVoltage = 0.0;

const float ADC_REFERENCE = 5.0;
const float VOLTAGE_DIVIDER_RATIO = 2.0;

String motorStatus = "STOPPED";

// =============== SETUP ===============

void setup() {

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  stopMotor();

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("   AUTO-ALIGNING SOLAR TRACKER");
  Serial.println("================================");

  Serial.println("System Initializing...");
  delay(1000);

  Serial.println("System Ready!");
  Serial.println();
}

// =============== MAIN LOOP ===============

void loop() {

  // 1. Read left and right LDR sensors

  leftValue = analogRead(LDR_LEFT);
  rightValue = analogRead(LDR_RIGHT);

  difference = abs(leftValue - rightValue);

  // 2. Read potentiometer

  potValue = analogRead(POT_PIN);

  threshold = map(
    potValue,
    0,
    1023,
    MIN_THRESHOLD,
    MAX_THRESHOLD
  );

  // 3. Read solar panel voltage

  solarReading = analogRead(SOLAR_PIN);

  solarVoltage =
    (solarReading * ADC_REFERENCE / 1023.0)
    * VOLTAGE_DIVIDER_RATIO;

  // 4. Determine motor direction

  motorStatus = "STOPPED";

  if (difference > threshold) {

    if (leftValue > rightValue) {

      rotateLeft();
      motorStatus = "LEFT";

    } else {

      rotateRight();
      motorStatus = "RIGHT";

    }

    // Short motor movement
    delay(MOTOR_PULSE_TIME);

    // Stop motor
    stopMotor();

    // Allow sensors and panel to settle
    delay(SETTLE_TIME);

  } else {

    stopMotor();

  }

  // 5. Print readings

  if (millis() - lastPrintTime >= PRINT_INTERVAL) {

    Serial.println("--------------------------------");

    Serial.print("Left LDR: ");
    Serial.println(leftValue);

    Serial.print("Right LDR: ");
    Serial.println(rightValue);

    Serial.print("Difference: ");
    Serial.println(difference);

    Serial.print("Threshold: ");
    Serial.println(threshold);

    Serial.print("Potentiometer: ");
    Serial.println(potValue);

    Serial.print("Solar Voltage: ");
    Serial.print(solarVoltage, 2);
    Serial.println(" V");

    Serial.print("Motor Status: ");
    Serial.println(motorStatus);

    lastPrintTime = millis();
  }
}

// =============== MOTOR FUNCTIONS ===============

void rotateLeft() {

  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);

}

void rotateRight() {

  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);

}

void stopMotor() {

  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);

}
