// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

// Servo Config
#define S_ELB 9
#define S_WRS 11
#define S_GRP 12

#define S_ELB_MIN 175
#define S_ELB_MAX 600
#define S_ELB_HOME 250

#define S_WRS_MIN 125
#define S_WRS_MAX 550
#define S_WRS_HOME 250

#define S_GRP_MIN 150
#define S_GRP_MAX 575
#define S_GRP_HOME 250

#define SERVOCHG 10

// Stepper Config
#define BASE_1 33
#define BASE_2 35
#define BASE_3 37
#define BASE_4 39

#define BASE_SPD 1000
#define BASE_ACCEL 500

#define SHOULDER_1 49
#define SHOULDER_2 47

#define SHOULDER_SPD 500
#define SHOULDER_ACCEL 1000

#define STEPPERCHG 20

byte c_data[5];
byte byte1, byte2, byte3, byte4, byte5;

// Initialize Motors
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int servo_pos[3] = {S_ELB_HOME, S_WRS_HOME, S_GRP_HOME}; // elbow, wrist, gripper

AccelStepper step_base(AccelStepper::FULL4WIRE, BASE_1, BASE_2, BASE_3, BASE_4);
AccelStepper step_shoulder(AccelStepper::DRIVER, SHOULDER_1, SHOULDER_2);


void setup() {
  Serial.begin(9600);

  step_base.setMaxSpeed(BASE_SPD);
  step_base.setAcceleration(BASE_ACCEL);
  step_base.disableOutputs();

  step_shoulder.setMaxSpeed(SHOULDER_SPD);
  step_shoulder.setAcceleration(SHOULDER_ACCEL);
  step_shoulder.disableOutputs();
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}

void loop() {
  checkSerial();
  step_base.run();
  step_shoulder.run();
}


void checkSerial() {
  if (Serial.available() >= 5) {
    for (int i = 0; i < 5; i++) {
      data[i] = Serial.read(); // Read the incoming data byte by byte
    }
    // Separate the bytes into their own variables
    byte byte1 = data[0];
    byte byte2 = data[1];
    byte byte3 = data[2];
    byte byte4 = data[3];
    byte byte5 = data[4];
    // Control motors
    step_base.move(byte1);
    step_shoulder.move(byte2);
    pwm.setPWM(1, 0, byte3);
    pwm.setPWM(2, 0, byte4);
    pwm.setPWM(3, 0, byte5);
  }
}