// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

// Servo Config
#define S_ELB 12
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

#define SERVOCHG 1

// Stepper Config
#define BASE_1 33
#define BASE_2 35
#define BASE_3 37
#define BASE_4 39

#define BASE_SPD 600
#define BASE_ACCEL 600
#define BASE_CHG 20
#define BASE_MIN -1000 // pickup
#define BASE_MAX 1000 // dropoff

#define SHOULDER_1 49
#define SHOULDER_2 47

// shoulder is 1/16 steps
#define SHOULDER_SPD 3200
#define SHOULDER_ACCEL 1600
#define SHOULDER_MIN -1000
#define SHOULDER_MAX 3840
#define SHOULDER_CHG 128

byte data[5];
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
  step_base.setCurrentPosition(0);
  step_base.disableOutputs();

  step_shoulder.setMaxSpeed(SHOULDER_SPD);
  step_shoulder.setAcceleration(SHOULDER_ACCEL);
  step_shoulder.setCurrentPosition(0);
  step_shoulder.disableOutputs();
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  // servo_pos[0] = map(pwm.getPWM(S_GRP), S_GRP_MIN, S_GRP_MAX, 0, 180);
  // for (int i = 0; i < 10; i++) {
  //   Serial.println(pwm.getPWM(S_GRP));    
  // }
  pwm.setPWM(S_ELB, 0, servo_pos[0]);
  pwm.setPWM(S_WRS, 0, servo_pos[1]);
  pwm.setPWM(S_GRP, 0, servo_pos[2]);
}


void loop() {
  if (Serial.available() >= 5) {
    byte data[5];
    int messageLength = Serial.readBytesUntil('\n', data, 6);

    byte byte1 = data[0];
    byte byte2 = data[1];
    byte byte3 = data[2];
    byte byte4 = data[3];
    byte byte5 = data[4];

    //Serial.write(byte1);
    //Serial.write(byte2);
    //Serial.write(byte3);
    //Serial.write(byte4);
    //Serial.write(byte5);

    // Base Byte
    if (byte1 != 0) {
      int base_pos = map(byte1, 0, 255, BASE_MIN, BASE_MAX);
      step_base.moveTo(base_pos);
      step_base.runToPosition();
    }

    // Shoulder Byte
    if (byte2 != 0) {
      // Serial.write("shoulder");
      int shoulder_pos = map(byte2, 0, 255, SHOULDER_MIN, SHOULDER_MAX);
      step_shoulder.moveTo(shoulder_pos);
      step_shoulder.runToPosition();
    }

    // Elbow  and Wrist Byte
    if (byte3 != 0) {
      // Serial.write("elbow");
      int elb_pos = map(byte3, 0, 255, S_ELB_MIN, S_ELB_MAX);
      int dist = (elb_pos - servo_pos[0])/SERVOCHG;
      int dir = dist/abs(dist);
      for (int i = 0; i < abs(dist); i++) {
        delay(5);
        servo_pos[0] = servo_pos[0] + dir*SERVOCHG;
        pwm.setPWM(S_ELB, 0, servo_pos[0]);
      }
      // servo_pos[0] = elb_pos;
      // pwm.setPWM(S_ELB, 0, servo_pos[0]);
    }

    // // Elbow  and Wrist Byte
    // if (byte3 != 0) {
    //   // Serial.write("elbow");
    //   int elb_pos = map(byte3, 0, 255, S_ELB_MIN, S_ELB_MAX);
    //   int dist = (elb_pos - servo_pos[0])/SERVOCHG;
    //   int dir = dist/abs(dist);
    //   for (int i = 0; i < abs(dist); i++) {
    //     delay(5);
    //     servo_pos[0] = servo_pos[0] + dir*SERVOCHG;
    //     pwm.setPWM(S_ELB, 0, servo_pos[0]);
    //   }
    //   // servo_pos[0] = elb_pos;
    //   // pwm.setPWM(S_ELB, 0, servo_pos[0]);
    // }

    //     // Wrist Byte
    // if (byte4 != 0) {
    //   // Serial.write("wrist");
    //   int wrs_pos = map(byte4, 0, 255, S_WRS_MIN, S_WRS_MAX);
    //   int dist = (wrs_pos - servo_pos[1])/SERVOCHG;
    //   int dir = dist/abs(dist);
    //   for (int i = 0; i < abs(dist); i++) {
    //     delay(5);
    //     servo_pos[1] = servo_pos[1] + dir*SERVOCHG;
    //     pwm.setPWM(S_WRS, 0, servo_pos[1]);
    //   }
    //   // servo_pos[1] = wrs_pos;
    //   // pwm.setPWM(S_WRS, 0, servo_pos[1]);
    // }

    // Gripper Byte
    if (byte5 != 0) {
      int grp_pos = map(byte5, 0, 255, S_GRP_MIN, S_GRP_MAX);
      int dist = (grp_pos - servo_pos[2])/SERVOCHG;
      int dir = dist/abs(dist);
      for (int i = 0; i < abs(dist); i++) {
        delay(5);
        servo_pos[2] = servo_pos[2] + dir*SERVOCHG;
        pwm.setPWM(S_GRP, 0, servo_pos[2]);
      }
      // servo_pos[2] = grp_pos;
      // pwm.setPWM(S_GRP, 0, grp_pos);
    }
  }
}

