// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const int SERVOMIN = 175;                               // 'minimum' pulse length count (out of 4096)
const int SERVOMAX = 500;                               // 'maximum' pulse length count (out of 4096)
const int SERVOMID = floor((SERVOMAX + SERVOMIN) / 2);  // 'mid' pulse length count (out of 4096)
const int SERVOCHG = 50;                                // 'change' pulse length count

const int POTENTMAX = 1023;
const int POTENTMIN = 0;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

String valInput;                                // Serial input var.
byte potent_pin = A10;                          // analog pin
byte max_pin = A12;
byte min_pin = A14; 

int min_state = 0;
int max_state = 0;       

int i = 0;                                      // loop index var.
int val[3] = { SERVOMID, SERVOMID, SERVOMID };  // PWM var
int prev_val = 0;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(10);  // change default (1000ms) to have faster response time
  Serial.println("Program Start: Servo motor actuation using potentiometer");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pinMode(min_pin, INPUT);
  pinMode(max_pin, INPUT);

}

void loop() {

  // Read Sensor Da
  min_state = digitalRead(min_pin);
  max_state = digitalRead(max_pin);

  int sensorValue = analogRead(potent_pin);  // read input on analog pin 10
  sensorValue = map(sensorValue, POTENTMIN, POTENTMAX, SERVOMIN, SERVOMAX);

  if (min_state == 1) {
    pwm.setPWM(1, 0, SERVOMIN);
    delay(750);
  } else if (max_state == 1) {
    pwm.setPWM(1, 0, );
    delay(750);
  } else {
    if (abs(prev_val - sensorValue) > 10) {
      prev_val = sensorValue;
      pwm.setPWM(1, 0, prev_val);
      delay(10);
    }
  }
}
