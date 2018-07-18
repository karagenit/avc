// PWM Ports
#define MOTOR_A 2
#define MOTOR_B 3
#define MOTOR_C 4
#define MOTOR_D 5

// Connection timeout, ms
#define TIMEOUT 1000

// TODO: need direction control pins?

void setup() {
    // TODO: set pinMode output?
    Serial.begin(115200);
    Serial.setTimeout(TIMEOUT);
}

void loop() {
    signed byte motorValues[4];

    // it may get mad about this being signed, so we might have to store
    // as unsigned and cast to signed
    byte status = Serial.readBytes(motorValues, 4);

    if (status >= 4) {
        setMotors(motorValues);
    } else {
        stopMotors();
    }
}

// TODO: set directions based on motorValues signs
void setMotors(signed byte motorValues[4]) {
    analogWrite(MOTOR_A, mapValue(motorValues[0]));
    analogWrite(MOTOR_B, mapValue(motorValues[1]));
    analogWrite(MOTOR_C, mapValue(motorValues[2]));
    analogWrite(MOTOR_D, mapValue(motorValues[3]));
}

// TODO: error on -128?
int mapValue(signed byte value) {
    return map(abs(value), 0, 127, 0, 255);
}

void stopMotors() {
    signed byte zero = {0,0,0,0};
    setMotors(zero);
}
