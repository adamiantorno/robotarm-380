// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

// Servo Config
#define S_ELB 9
#define S_WRS 11
#define S_GRP 12

#define S_ELB_MIN 200
#define S_ELB_MAX 600
#define S_ELB_HOME 300
#define S_ELB_CHG 5

#define S_WRS_MIN 125
#define S_WRS_MAX 550
#define S_WRS_HOME 250
#define S_WRS_CHG 5

#define S_GRP_MIN 150
#define S_GRP_MAX 575
#define S_GRP_HOME 150
#define S_GRP_CHG 10

// Stepper Config
#define BASE_1 33
#define BASE_2 35
#define BASE_3 37
#define BASE_4 39

#define BASE_SPD 500
#define BASE_ACCEL 800
#define BASE_CHG 45

#define SHOULDER_1 49
#define SHOULDER_2 47

#define SHOULDER_SPD 300
#define SHOULDER_ACCEL 100
#define SHOUDLER_CHG 5

// Initialize Motors
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int servo_pos[3] = {S_ELB_HOME, S_WRS_HOME, S_GRP_HOME}; // elbow, wrist, gripper

AccelStepper step_base(AccelStepper::FULL4WIRE, BASE_1, BASE_2, BASE_3, BASE_4);
AccelStepper step_shoulder(AccelStepper::DRIVER, SHOULDER_1, SHOULDER_2);

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

    pwm.setPWM(S_ELB, 0, S_ELB_HOME);
    pwm.setPWM(S_WRS, 0, S_WRS_HOME);
    pwm.setPWM(S_GRP, 0, S_GRP_HOME);
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
              step_base.move(BASE_CHG);
              break;
          case 'S':
              step_base.move(-BASE_CHG);
              break;
          case 'E':
              step_shoulder.move(SHOUDLER_CHG);
              break;
          case 'D':
              step_shoulder.move(-SHOUDLER_CHG);
              break;
          case 'R':
            servo_pos[0] = min(servo_pos[0] + S_ELB_CHG, S_ELB_MAX);
            pwm.setPWM(S_ELB, 0, servo_pos[0]);
            break;
          case 'F':
            servo_pos[0] = max(servo_pos[0] - S_ELB_CHG, S_ELB_MIN);
            pwm.setPWM(S_ELB, 0, servo_pos[0]);
            break;
          case 'T':
            servo_pos[1] = min(servo_pos[1] + S_WRS_CHG, S_WRS_MAX);
            pwm.setPWM(S_WRS, 0, servo_pos[1]);
            break;
          case 'G':
            servo_pos[1] = max(servo_pos[1] - S_WRS_CHG, S_WRS_MIN);
            pwm.setPWM(S_WRS, 0, servo_pos[1]);
            break;
          case 'Y':
            servo_pos[2] = min(servo_pos[2] + S_GRP_CHG, S_GRP_MAX);
            pwm.setPWM(S_GRP, 0, servo_pos[2]);
            break;
          case 'H':
            servo_pos[2] = max(servo_pos[2] - S_GRP_CHG, S_GRP_MIN);
            pwm.setPWM(S_GRP, 0, servo_pos[2]);
            break;
      }
    newData = false;
    }
}