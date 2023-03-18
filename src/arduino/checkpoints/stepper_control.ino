// Software Developped for ME 380 Project at the University of Waterloo - Group 7

#include <AccelStepper.h>


AccelStepper myStepper(AccelStepper::FULL4WIRE, 8, 9, 10, 11);

const int FORW = 2;
const int BACK = 3;
const int LED_FORW = 4; 
const int LED_BACK = 5; 

int stateFORW;
int stateBACK;

void setup() {

  Serial.begin(9600);
  pinMode(FORW, INPUT_PULLUP);
  pinMode(BACK, INPUT_PULLUP);
  pinMode(LED_FORW, OUTPUT);        
  pinMode(LED_BACK, OUTPUT); 

  myStepper.setMaxSpeed(1200);
  
}

void loop() {
  
  myStepper.setAcceleration(5000);
  myStepper.stop();
  myStepper.runToPosition();

  while (digitalRead(FORW) == LOW){

    myStepper.setAcceleration(1000);
    myStepper.move(1000000);
    myStepper.run();
    digitalWrite(LED_FORW, HIGH);
    digitalWrite(LED_BACK, LOW);

  }

  while (digitalRead(BACK) == LOW){

    myStepper.setAcceleration(1000);
    myStepper.move(-1000000);
    myStepper.run();
    digitalWrite(LED_FORW, LOW);
    digitalWrite(LED_BACK, HIGH);

  }

  digitalWrite(LED_FORW, LOW);
  digitalWrite(LED_BACK, LOW);
  
  /*
  stateFORW = digitalRead(FORW);
  stateBACK = digitalRead(BACK);

  
  
  if (!stateFORW == LOW && !stateBACK == LOW){

    myStepper.stop();
    Serial.println("stop");
    digitalWrite(LED_FORW, LOW);
    digitalWrite(LED_BACK, LOW);
  }

  


  if (stateFORW == LOW){

    myStepper.move(100);
    //myStepper.run();
    digitalWrite(LED_FORW, HIGH);
    Serial.println("for");
  } else if (stateBACK == LOW)
  {

    myStepper.move(-10);
    //myStepper.run();
    Serial.println("back");
    digitalWrite(LED_BACK, HIGH);

  }  

  stateFORW = digitalRead(FORW);
  stateBACK = digitalRead(BACK);
  */
  

 
    
  
}