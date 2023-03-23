// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

// SERVO Motor Config
#define SERVOMIN 175
#define SERVOMAX 500
#define SERVOCHG 50

#define ELBOW_SERV 1
#define WRIST_SERV 5
#define GRIPR_SERV 6

// Stepper Motor Config
#define BASE_1 62
#define BASE_2 63
#define BASE_3 64
#define BASE_4 65

#define SHOULDER_1 67
#define SHOULDER_2 68
#define SHOULDER_3 69
#define SHOULDER_4 70

#define STEPPERCHG 300

long receivedMMdistance = 0;
long receivedDelay = 0;
long receivedAcceleration = 0;
char incomingByte;
/*
s = start
o = open
c = close
a = set accel
n = stop
*/

bool newData, run_base, run_shoulder = false;

AccelStepper step_base(AccelStepper::FULL4WIRE, BASE_1, BASE_2, BASE_3, BASE_4);
AccelStepper step_shoulder(AccelStepper::FULL4WIRE, SHOULDER_1, SHOULDER_2, SHOULDER_3, SHOULDER_4);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int serv_pos[3] = {SERVOMIN, SERVOMIN, SERVOMIN};  // {elbow, wrist, gripper}


void setup() {
  Serial.begin(9600);

  step_base.setMaxSpeed(1200);
  step_base.setAcceleration(1000);
  step_base.disableOutputs();

  step_shoulder.setMaxSpeed(1200);
  step_shoulder.setAcceleration(1000);
  step_shoulder.disableOutputs();
  
  Serial.println("we made it");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  Serial.println("cash money");

}

void loop() {
  
  checkSerial();
  step_base.run();
  step_shoulder.run();
  // control_steppermotors();

}


void checkSerial() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    newData = true;
    Serial.println(incomingByte);
  }

  if (newData == true) {
    switch (incomingByte){
        case 'W': // BASE FRWD
          // run_base = true;
          step_base.move(STEPPERCHG);
          break;
        case 'S': // BASE BWRD
          // run_base = true;
          step_base.move(-STEPPERCHG);
          break;
        case 'E': // SHOULDER FRWD
          // run_shoulder = true;
          step_shoulder.move(STEPPERCHG);
          break;
        case 'D': // SHOULDER BWRD
          // run_shoulder = true;
          step_shoulder.move(-STEPPERCHG);
          break;
        case 'R': // ELBOW FRWD
          Serial.println("CASE R");
          pwm.setPWM(ELBOW_SERV, 0, SERVOMAX);
          break;
        case 'F': // ELBOW BWRD
          Serial.println("CASE F");
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
      }
  newData = false;
  }
}


// void control_steppermotors() {
//   if (run_base == true) {
//     if (step_base.distanceToGo() != 0) {
//       step_base.enableOutputs();
//       step_base.run();    
//     }
//     else {
//       run_base = false;
//       step_base.setCurrentPosition(0);
//       // step_base.disableOutputs();            
//     }
//   }

//   if (run_shoulder == true) {
//     if (abs(step_shoulder.currentPosition()) < STEPPERCHG) {
//       step_shoulder.enableOutputs();
//       step_shoulder.run();    
//     }
//     else {
//       run_base = false;
//       step_shoulder.setCurrentPosition(0);
//       // step_shoulder.disableOutputs();            
//     }
//   }
// }