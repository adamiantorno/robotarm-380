// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

// Servo Config
#define S_ELB 14
#define S_WRS 11
#define S_GRP 9

#define S_ELB_MIN 200
#define S_ELB_MAX 600
#define S_ELB_HOME 325
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

#define BASE_SPD 1000
#define BASE_ACCEL 800 
#define BASE_CHG 20
#define BASE_MIN -1000 // pickup
#define BASE_MAX 1000 // dropoff

#define SHOULDER_1 49
#define SHOULDER_2 47

#define SHOULDER_SPD 3200
#define SHOULDER_ACCEL 1600
#define SHOULDER_CHG 128
#define SHOULDER_MIN -1000
#define SHOULDER_MAX 3840

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
    step_base.setCurrentPosition(0);
    step_base.disableOutputs();

    step_shoulder.setMaxSpeed(SHOULDER_SPD);
    step_shoulder.setAcceleration(SHOULDER_ACCEL);
    step_shoulder.setCurrentPosition(0);
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
        // Serial.write("goodbye");
        incomingByte = Serial.read();
        newData = true;
    }
    if (newData == true) {
      switch(incomingByte) { 
          case 'W':
              if (step_base.currentPosition() < BASE_MAX) {
                step_base.move(BASE_CHG);
              }
              break;
          case 'S':
              if (step_base.currentPosition() > BASE_MIN) {
                step_base.move(-BASE_CHG);
              }
              break;
          case 'E':
              if (step_shoulder.currentPosition() < SHOULDER_MAX) {
                step_shoulder.move(SHOULDER_CHG);
              }
              break;
          case 'D':
              if (step_shoulder.currentPosition() > SHOULDER_MIN) {
                step_shoulder.move(-SHOULDER_CHG);
              }
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
    // Serial.write(step_base.currentPosition());
    newData = false;
    }
}