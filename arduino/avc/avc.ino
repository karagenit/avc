// PWM Ports
#define MOTOR_A 2
#define MOTOR_B 3
#define MOTOR_C 4
#define MOTOR_D 5

// Direction pins
#define DIR_A 6
#define DIR_B 7
#define DIR_C 8
#define DIR_D 9

// Connection timeout, ms
#define TIMEOUT 1000

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(TIMEOUT);

    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    pinMode(MOTOR_C, OUTPUT);
    pinMode(MOTOR_D, OUTPUT);

    pinMode(DIR_A, OUTPUT);
    pinMode(DIR_B, OUTPUT);
    pinMode(DIR_C, OUTPUT);
    pinMode(DIR_D, OUTPUT);
}

void loop() {
    signed byte motorValues[4];

    byte status = Serial.readBytes(motorValues, 4);

    if (status >= 4) {
        setMotors(motorValues);
    } else {
        stopMotors();
    }
}

void setMotors(signed byte motorValues[4]) {
    analogWrite(MOTOR_A, mapValue(motorValues[0]));
    analogWrite(MOTOR_B, mapValue(motorValues[1]));
    analogWrite(MOTOR_C, mapValue(motorValues[2]));
    analogWrite(MOTOR_D, mapValue(motorValues[3]));

    digitalWrite(DIR_A, motorValues[0] >= 0);
    digitalWrite(DIR_B, motorValues[1] >= 0);
    digitalWrite(DIR_C, motorValues[2] >= 0);
    digitalWrite(DIR_D, motorValues[3] >= 0);
}

// TODO: error on -128?
int mapValue(signed byte value) {
    return map(abs(value), 0, 127, 0, 255);
}

void stopMotors() {
    signed byte zero = {0,0,0,0};
    setMotors(zero);
}
