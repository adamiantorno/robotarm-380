// Software Developed for ME380 Project at the University of Waterloo - Group 7

#include <AccelStepper.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// Servo Config
#define SERVOMIN 175
#define SERVOMAX 500
#define SERVOCHG 50

// Servo Pins on 
#define SERV_ELBOW 1
#define SERV_WRIST 2
#define SERV_GRIPR 3

// Stepper Config
#define BASE_1 62
#define BASE_2 63
#define BASE_3 64
#define BASE_4 65

#define SHOULDER_1 67
#define SHOULDER_2 68
#define SHOULDER_3 69
#define SHOULDER_4 70

// Initialize Servo Motors and Pins
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int serv_pos[3] = {SERVOMIN, SERVOMIN, SERVOMIN};  // {elbow, wrist, gripper}
int control_index = 0
byte servo_pin = A10;

// Initialize Stepper Motors and Pins
AccelStepper step_base(AccelStepper::FULL4WIRE, BASE_1, BASE_2, BASE_3, BASE_4);
AccelStepper step_shoulder(AccelStepper::FULL4WIRE, SHOULDER_1, SHOULDER_2, SHOULDER_3, SHOULDER_4);

void setup () {
  Serial.begin(9600);

  pwm.begin();
  
}

void loop () {

}