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

byte data[6];
byte base_byte, shoulder_byte, elbow_byte, wrist_byte, gripper_byte;

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
  if (Serial.available() >= 6) {
    byte data[6];
    int messageLength = Serial.readBytesUntil('\n', data, 7);

    byte base_byte = data[0];
    byte shoulder_byte = data[1];
    byte elbow_byte = data[2];
    byte wrist_byte = data[3];
    byte gripper_byte = data[4];
    byte dir_byte = data[5];

    //Serial.write(base_byte);
    //Serial.write(shoulder_byte);
    //Serial.write(elbow_byte);
    //Serial.write(wrist_byte);
    //Serial.write(gripper_byte);

    // check order of arm operations
    // backwards direction
    if (dir_byte == 1) {
      // Gripper Byte
      if (gripper_byte != 0) {
        int grp_pos = map(gripper_byte, 0, 255, S_GRP_MIN, S_GRP_MAX);
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

      // Shoulder Byte
      if (shoulder_byte != 0) {
        // Serial.write("shoulder");
        int shoulder_pos = map(shoulder_byte, 0, 255, SHOULDER_MIN, SHOULDER_MAX);
        step_shoulder.moveTo(shoulder_pos);
        step_shoulder.runToPosition();
      }

      // Wrist Byte
      if (wrist_byte != 0) {
        // Serial.write("wrist");
        int wrs_pos = map(wrist_byte, 0, 255, S_WRS_MIN, S_WRS_MAX);
        int dist = (wrs_pos - servo_pos[1])/SERVOCHG;
        int dir = dist/abs(dist);
        for (int i = 0; i < abs(dist); i++) {
          delay(5);
          servo_pos[1] = servo_pos[1] + dir*SERVOCHG;
          pwm.setPWM(S_WRS, 0, servo_pos[1]);
        }
        // servo_pos[1] = wrs_pos;
        // pwm.setPWM(S_WRS, 0, servo_pos[1]);
      }

      // Elbow Byte
      if (elbow_byte != 0) {
        // Serial.write("elbow");
        int elb_pos = map(elbow_byte, 0, 255, S_ELB_MIN, S_ELB_MAX);
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

      // Base Byte
      if (base_byte != 0) {
        int base_pos = map(base_byte, 0, 255, BASE_MIN, BASE_MAX);
        step_base.moveTo(base_pos);
        step_base.runToPosition();
      }
    } else { // FORWARD
      // Base Byte
      if (base_byte != 0) {
        int base_pos = map(base_byte, 0, 255, BASE_MIN, BASE_MAX);
        Serial.write(base_pos);
        step_base.moveTo(base_pos);
        step_base.runToPosition();
      }

      // Shoulder Byte
      if (shoulder_byte != 0) {
        // Serial.write("shoulder");
        int shoulder_pos = map(shoulder_byte, 0, 255, SHOULDER_MIN, SHOULDER_MAX);
        step_shoulder.moveTo(shoulder_pos);
        step_shoulder.runToPosition();
      }

      // Elbow Byte
      if (elbow_byte != 0) {
        // Serial.write("elbow");
        int elb_pos = map(elbow_byte, 0, 255, S_ELB_MIN, S_ELB_MAX);
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

      // Wrist Byte
      if (wrist_byte != 0) {
        // Serial.write("wrist");
        int wrs_pos = map(wrist_byte, 0, 255, S_WRS_MIN, S_WRS_MAX);
        int dist = (wrs_pos - servo_pos[1])/SERVOCHG;
        int dir = dist/abs(dist);
        for (int i = 0; i < abs(dist); i++) {
          delay(5);
          servo_pos[1] = servo_pos[1] + dir*SERVOCHG;
          pwm.setPWM(S_WRS, 0, servo_pos[1]);
        }
        // servo_pos[1] = wrs_pos;
        // pwm.setPWM(S_WRS, 0, servo_pos[1]);
      }

      // Gripper Byte
      if (gripper_byte != 0) {
        int grp_pos = map(gripper_byte, 0, 255, S_GRP_MIN, S_GRP_MAX);
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
}

