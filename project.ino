#include <Servo.h>

Servo gripperServo;
Servo rotationServo;

const int GRIPPER_PIN = 9;
const int ROTATION_PIN = 10;

const int GRIPPER_OPEN = 70;
const int GRIPPER_CLOSED = 120;
const int ROTATION_INITIAL = 120;
const int ROTATION_METAL = 50;    
const int ROTATION_NON_METAL = 20; 

const int MOTOR_IN1 = 5;
const int MOTOR_ENA = 6;  

const int IRpin = 2;       
const int metalpin = 3;    

bool lastIsMetal = false;


void setup() {
  
  gripperServo.attach(GRIPPER_PIN);
  rotationServo.attach(ROTATION_PIN);
  resetGripper();

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT);
  digitalWrite(MOTOR_IN1, HIGH);

  pinMode(IRpin, INPUT);
  pinMode(metalpin, INPUT);
}

void loop() {
  int metalRead = digitalRead(metalpin);
  int irRead = digitalRead(IRpin);

  if (metalRead == HIGH) {
    lastIsMetal = true;
  }

  if (irRead == LOW) {
    analogWrite(MOTOR_ENA, 0); 
    delay(300); 

    if (lastIsMetal) {
      sortObject(ROTATION_METAL);
    } else {
      sortObject(ROTATION_NON_METAL);
    }

    lastIsMetal = false;

    delay(500); 
  } else {
    
    analogWrite(MOTOR_ENA, 100);
  }
}

void sortObject(int rotationAngle) {
  gripperServo.write(GRIPPER_CLOSED); 
  delay(500);

  rotationServo.write(rotationAngle);
  delay(1000);

  gripperServo.write(GRIPPER_OPEN); 
  delay(500);

  resetGripper(); 
}

void resetGripper() {
  gripperServo.write(GRIPPER_OPEN);
  rotationServo.write(ROTATION_INITIAL);
  delay(500);
}
