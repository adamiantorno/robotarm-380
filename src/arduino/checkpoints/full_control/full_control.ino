// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

// SERVO Motor Config
#define SERVOMIN 175;
#define SERVOMAX 500;
#define SERVOCHG 50;

#define ELBOW_SERV 1
#define WRIST_SERV 2
#define GRIPR_SERV 3

// Stepper Motor Config
#define BASE_1 14;
#define BASE_2 = 15;
#define BASE_3 = 16;
#define BASE_4 = 17;

#define SHOULDER_1 = 18;
#define SHOULDER_2 = 19;
#define SHOULDER_3 = 20;
#define SHOULDER_4 = 21;

int incomingByte;

AccelStepper step_base(AccelStepper::FULL4WIRE, BASE_1, BASE_2, BASE_3, BASE_4);
AccelStepper step_shoulder(AccelStepper::FULL4WIRE, SHOULDER_1, SHOULDER_2, SHOULDER_3, SHOULDER_4);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int serv_pos[3] = {SERVOMIN, SERVOMIN, SERVOMIN}


void setup() {
  Serial.begin(9600);

  step_base.setMaxSpeed(1200);
  step_base.setAcceleration(1000);

  step_shoulder.setMaxSpeed(1200);
  step_shoulder.setAcceleration(1000);
    
}

void loop() {


  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    
    switch (incomingByte) {
      case 'W': // BASE FRWD
        step_base.setAcceleration(1000);
        step_base.move(1);

        step_base.setSpeed(1000);
        step_base.runSpeed();
        break;
      case 'S': // BASE BWRD
        Serial.println("S");
        break;
      case 'E': // SHOULDER FRWD
        Serial.println("E");
        break;
      case 'D': // SHOULDER BWRD
        Serial.println("D");
        break;
      case 'R': // ELBOW FRWD
        pwm.setPWM(ELBOW_SERV, 0, SERVOMAX);
        break;
      case 'F': // ELBOW BWRD
        pwm.setPWM(ELBOW_SERV, 0, SERVOMIN);
        break;
      case 'T': // WRIST FRWD
        pwm.setPWM(WRIST_SERV, 0, SERVOMAX);
        break;
      case 'G': // WRIST BWRD
        pwm.setPWM(WRIST_SERV, 0, SERVOMIN);
        break;
      case 'Y': // GRIPPER FRWD
        pwm.setPWM(GRIPR_SERV, 0, SERVOMAX);
        break;
      case 'H': // GRIPPWR BWRD
        pwm.setPWM(GRIPR_SERV, 0, SERVOMIN);
        break;  
      case 0:
        step_base.setSpeed(0);
        step_base.runSpeed();
        break;
    }

    delay(20);
  }

}