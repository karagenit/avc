#include <stdint.h>

// PWM Ports
#define MOTOR_A_FWD 3
#define MOTOR_B_FWD 6
#define MOTOR_C_FWD 8
#define MOTOR_D_FWD 10

#define MOTOR_A_REV 5
#define MOTOR_B_REV 15
#define MOTOR_C_REV 9
#define MOTOR_D_REV 11

// Enable pins - active low
#define DISABLE_A 2
#define DISABLE_B 4
#define DISABLE_C 7
#define DISABLE_D 14

// Connection timeout, ms
#define TIMEOUT 100000 // FIXME

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(TIMEOUT);

    pinMode(MOTOR_A_FWD, OUTPUT);
    pinMode(MOTOR_B_FWD, OUTPUT);
    pinMode(MOTOR_C_FWD, OUTPUT);
    pinMode(MOTOR_D_FWD, OUTPUT);

    pinMode(MOTOR_A_REV, OUTPUT);
    pinMode(MOTOR_B_REV, OUTPUT);
    pinMode(MOTOR_C_REV, OUTPUT);
    pinMode(MOTOR_D_REV, OUTPUT);

    pinMode(DISABLE_A, OUTPUT);
    pinMode(DISABLE_B, OUTPUT);
    pinMode(DISABLE_C, OUTPUT);
    pinMode(DISABLE_D, OUTPUT);
}

void loop() {
    uint8_t motorValues[4];

    uint8_t byteCount = Serial.readBytes(motorValues, 4);

    noInterrupts();
    
    if (byteCount == 4) {
      clearMotors();
      setMotors(motorValues);
      enableMotors();
    } else {
      disableMotors();
    }

    interrupts();
}

void setMotors(uint8_t motorValues[4]) {
  analogWrite(motorValues[0] > 127 ? MOTOR_A_FWD : MOTOR_A_REV, mapValue(motorValues[0]));
  analogWrite(motorValues[1] > 127 ? MOTOR_B_FWD : MOTOR_B_REV, mapValue(motorValues[1]));
  analogWrite(motorValues[2] > 127 ? MOTOR_C_FWD : MOTOR_C_REV, mapValue(motorValues[2]));
  analogWrite(motorValues[3] > 127 ? MOTOR_D_FWD : MOTOR_D_REV, mapValue(motorValues[3]));
}

int mapValue(uint8_t value) {
    return abs(map(value, 0, 255, -255, 255));
}

// Enables all motors
void enableMotors() {
  digitalWrite(DISABLE_A, LOW);
  digitalWrite(DISABLE_B, LOW);
  digitalWrite(DISABLE_C, LOW);
  digitalWrite(DISABLE_D, LOW);
}

// Resets all PWM values to 0%
void clearMotors() {
  digitalWrite(MOTOR_A_FWD, LOW);
  digitalWrite(MOTOR_B_FWD, LOW);
  digitalWrite(MOTOR_C_FWD, LOW);
  digitalWrite(MOTOR_D_FWD, LOW);

  digitalWrite(MOTOR_A_REV, LOW);
  digitalWrite(MOTOR_B_REV, LOW);
  digitalWrite(MOTOR_C_REV, LOW);
  digitalWrite(MOTOR_D_REV, LOW);
}

// Disables all motors
void disableMotors() {
  digitalWrite(DISABLE_A, HIGH);
  digitalWrite(DISABLE_B, HIGH);
  digitalWrite(DISABLE_C, HIGH);
  digitalWrite(DISABLE_D, HIGH);
}

