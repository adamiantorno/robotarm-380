// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

// Servo Config
#define SERVOMIN 175
#define SERVOMAX 500
#define SERVOCHG 50

#define SERV_ELBOW 9
#define SERV_WRIST 10
#define SERV_GRIPR 11

// Stepper Config
#define BASE_1 22
#define BASE_2 24
#define BASE_3 26
#define BASE_4 28

#define BASE_SPD 1000
#define BASE_ACCEL 500

#define SHOULDER_1 23
#define SHOULDER_2 25
#define SHOULDER_3 27
#define SHOULDER_4 29

#define SHOULDER_SPD 1000
#define SHOULDER_ACCEL 500

#define STEPPERCHG 600

// Initialize Motors
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

AccelStepper step_base(AccelStepper::FULL4WIRE, BASE_1, BASE_2, BASE_3, BASE_4);
AccelStepper step_shoulder(AccelStepper::FULL4WIRE, SHOULDER_1, SHOULDER_2, SHOULDER_3, SHOULDER_4);

char incomingByte;
bool newData;

void setup() {
    Serial.begin(9600);

    step_base.setMaxSpeed(BASE_SPD);
    step_base.setAcceleration(BASE_ACCEL);
    step_base.disableOutputs();

    step_shoulder.setMaxSpeed(SHOULDER_SPD);
    step_shoulder.setAcceleration(SHOULDER_ACCEL);
    step_shoulder.disableOutputs();

    pwm.begin();
    pwm.setPWMFreq(60);
}

void loop() {
    checkSerial();
    step_base.run();
    step_shoulder.run();
}

void checkSerial() {
    if (Serial.available() > 0) {
        incomingByte = Serial.read();
        newData = true;
    }
    if (newData == true) {
        switch(incomingByte) {
            case 'W':
                step_base.move(STEPPERCHG);
                break;
            case 'S':
                step_base.move(-STEPPERCHG);
                break;
            case 'E':
                step_shoulder.move(STEPPERCHG);
                break;
            case 'D':
                step_shoulder.move(-STEPPERCHG);
                break;
        }
    newData = false;
    }
}