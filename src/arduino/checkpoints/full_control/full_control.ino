// Software Developed for ME380 Project at the University of Waterloo - Group 7

#include <AccelStepper.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// Servo Config
#define SERVOMIN 180
#define SERVOMAX 700
#define SERVOCHG 50

#define POTENTMAX 1023
#define POTENTMIN 0

// Servo Pins on 
#define SERV_ELBOW 9
#define SERV_WRIST 10
#define SERV_GRIPR 11

#define ELBOW_PIN 64
#define WRIST_PIN 63
#define GRIPR_PIN 62

#define CHANGE_PIN 65

// Stepper Config
#define BASE_1 22
#define BASE_2 24
#define BASE_3 26
#define BASE_4 28

#define BASE_F 32
#define BASE_B 34

#define SHOULDER_1 23
#define SHOULDER_2 25
#define SHOULDER_3 27
#define SHOULDER_4 29

#define SHOULDER_F 45
#define SHOULDER_B 47

#define STEP_MS 1200
#define STEP_MA 1000

// Initialize Servo Motors and Pins
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// int serv_pin[3] = {ELBOW_PIN, WRIST_PIN, GRIPR_PIN};
const int servo_mid = floor((SERVOMAX+SERVOMIN)/2);
int serv_pos[3] = {SERVOMAX, SERVOMAX, servo_mid};  // {elbow, wrist, gripper}
int servo_dir = 1;
uint8_t ch_prev;
uint8_t el_prev;
uint8_t wr_prev;
uint8_t gr_prev;

// Initialize Stepper Motors and Pins
AccelStepper step_base(AccelStepper::FULL4WIRE, BASE_1, BASE_2, BASE_3, BASE_4);
AccelStepper step_shoulder(AccelStepper::FULL4WIRE, SHOULDER_1, SHOULDER_2, SHOULDER_3, SHOULDER_4);

void setup () {
  Serial.begin(9600);

  step_base.setMaxSpeed(STEP_MS);
  pinMode(BASE_F, INPUT_PULLUP);
  pinMode(BASE_B, INPUT_PULLUP);

  step_shoulder.setMaxSpeed(STEP_MS);
  pinMode(SHOULDER_F, INPUT_PULLUP);
  pinMode(SHOULDER_B, INPUT_PULLUP);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pinMode(ELBOW_PIN, INPUT_PULLUP);
  pinMode(WRIST_PIN, INPUT_PULLUP);
  pinMode(GRIPR_PIN, INPUT_PULLUP);
  pinMode(CHANGE_PIN, INPUT_PULLUP);

  ch_prev = digitalRead(CHANGE_PIN);
  el_prev = digitalRead(ELBOW_PIN);
  wr_prev = digitalRead(WRIST_PIN);
  gr_prev = digitalRead(GRIPR_PIN);

  pwm.setPWM(SERV_ELBOW, 0, SERVOMAX);
  pwm.setPWM(SERV_WRIST, 0, SERVOMAX);
  pwm.setPWM(SERV_GRIPR, 0, servo_mid);
  
}

void loop () {

  step_base.setAcceleration(5000);
  step_base.stop();
  step_base.runToPosition();

  step_shoulder.setAcceleration(5000);
  step_shoulder.stop();
  step_shoulder.runToPosition();

  while (digitalRead(BASE_F) == LOW){
    step_base.setAcceleration(STEP_MA);
    step_base.move(1000000);
    step_base.run();
  }

  while (digitalRead(BASE_B) == LOW){
    step_base.setAcceleration(STEP_MA);
    step_base.move(-1000000);
    step_base.run();
  }

  while (digitalRead(SHOULDER_F) == LOW){
    step_shoulder.setAcceleration(STEP_MA);
    step_shoulder.move(1000000);
    step_shoulder.run();
  }

  while (digitalRead(SHOULDER_B) == LOW){
    step_shoulder.setAcceleration(STEP_MA);
    step_shoulder.move(-1000000);
    step_shoulder.run();
  }

  if (digitalRead(CHANGE_PIN) == LOW && ch_prev == HIGH) {
    if (servo_dir == 1){
      servo_dir = -1;
    } else {
      servo_dir = 1;
    }
    delay(50);
    Serial.println(servo_dir);
  }

  if (digitalRead(ELBOW_PIN) == LOW) {
    if (servo_dir == 1) {
      Serial.println("ELBOW FRWD");
      serv_pos[0] = min(serv_pos[0] + 5, SERVOMAX);
      pwm.setPWM(SERV_ELBOW, 0, serv_pos[0]);
      //pwm.setPWM(SERV_ELBOW, 0, SERVOMAX);
      //delay(100);
    } else {
      Serial.println("ELBOW BWRD");
      serv_pos[0] = max(serv_pos[0] - 5, SERVOMIN);
      pwm.setPWM(SERV_ELBOW, 0, serv_pos[0]);
      //pwm.setPWM(SERV_ELBOW, 0, SERVOMIN);
      // delay(100);
    }
    delay(25);
  }

  if (digitalRead(WRIST_PIN) == LOW) {
    if (servo_dir == 1) {
      Serial.println("WRIST FRWD");
      serv_pos[1] = min(serv_pos[1] + 10, SERVOMAX);
      pwm.setPWM(SERV_WRIST, 0, serv_pos[1]);
      //pwm.setPWM(SERV_WRIST, 0, SERVOMAX);
      //delay(100);
    } else {
      Serial.println("WRIST BWRD");
      serv_pos[1] = max(serv_pos[1] - 10, SERVOMIN);
      pwm.setPWM(SERV_WRIST, 0, serv_pos[1]);
      //pwm.setPWM(SERV_WRIST, 0, SERVOMIN);
      // delay(100);
    }
    delay(20);
  }

  if (digitalRead(GRIPR_PIN) == LOW) {
    if (servo_dir == 1) {
      Serial.println("GRIPPER FRWD");
      serv_pos[2] = min(serv_pos[2] + 5, SERVOMAX);
      pwm.setPWM(SERV_GRIPR, 0, serv_pos[2]);
      //pwm.setPWM(SERV_WRIST, 0, SERVOMAX);
      //delay(100);
    } else {
      Serial.println("GRIPPER BWRD");
      serv_pos[2] = max(serv_pos[2] - 5, SERVOMIN);
      pwm.setPWM(SERV_GRIPR, 0, serv_pos[2]);
      //pwm.setPWM(SERV_WRIST, 0, SERVOMIN);
      // delay(100);
    }
    delay(25);
  }

  ch_prev = digitalRead(CHANGE_PIN);
  el_prev = digitalRead(ELBOW_PIN);
  wr_prev = digitalRead(WRIST_PIN);
  gr_prev = digitalRead(GRIPR_PIN);
}

