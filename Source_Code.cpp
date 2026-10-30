
/*
  PROJECT: AUTO-ALIGNING SOLAR TRACKER

  Board          : Arduino Nano
  Sensors        : 2 LDRs
  Motor Driver   : L9110S
  Motor          : 3-6V DC Geared Motor
  Potentiometer  : 10k ohm

  LDR 1          : A0
  LDR 2          : A1
  Potentiometer : A2

  L9110S IN1     : D5
  L9110S IN2     : D6
*/

// -------- PIN DEFINITIONS --------

const int LDR_LEFT  = A0;
const int LDR_RIGHT = A1;
const int POT_PIN = A2;
const int MOTOR_IN1 = 5;
const int MOTOR_IN2 = 6;

// -------- TRACKING SETTINGS --------

const int MIN_THRESHOLD = 15;
const int MAX_THRESHOLD = 200;
const int MOTOR_RUN_TIME = 120;
const int SETTLE_TIME = 150;
const unsigned long PRINT_INTERVAL = 500;
unsigned long previousPrintTime = 0;


// -------- SETUP --------

void setup() {

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  Serial.begin(9600);

  stopMotor();

  Serial.println("AUTO-ALIGNING SOLAR TRACKER");
  Serial.println("Left | Right | Difference | Threshold");
}
// -------- MAIN PROGRAM --------
void loop() {
  // Read both LDR sensors
  int leftValue = analogRead(LDR_LEFT);
  int rightValue = analogRead(LDR_RIGHT);
  // Calculate difference in light intensity
  int difference = abs(leftValue - rightValue);
  // Read potentiometer
  int potValue = analogRead(POT_PIN);
  // Adjust sensitivity threshold
  int threshold = map(
    potValue,
    0, 1023,
    MIN_THRESHOLD,
    MAX_THRESHOLD
  );
  // Decide motor direction
  if (difference > threshold) {

    if (leftValue > rightValue) {
      rotateLeft();
    }
    else {
      rotateRight();
    }
    delay(MOTOR_RUN_TIME);
    stopMotor();
    delay(SETTLE_TIME);
  } 
  else {
 // Stop when both LDR readings are nearly equal
    stopMotor();
  }

  // Display sensor readings in Serial Monitor
  if (millis() - previousPrintTime >= PRINT_INTERVAL) {
    Serial.print(leftValue);
    Serial.print(" | ");
    Serial.print(rightValue);
    Serial.print(" | ");
    Serial.print(difference);
    Serial.print(" | ");
    Serial.println(threshold);
    previousPrintTime = millis();
  }
}


// -------- MOTOR CONTROL FUNCTIONS --------

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
