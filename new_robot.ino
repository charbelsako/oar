#include <Servo.h>

Servo ServoOne;
int SrvPin=8;

// Left motor pins
#define motor1_neg 7
#define motor1_pos 6

// Right Motor pins
#define motor2_neg 5
#define motor2_pos 4

#define trigPin 9
#define echoPin 10

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ServoOne.attach(SrvPin);

  pinMode(motor1_neg, OUTPUT);
  pinMode(motor1_pos, OUTPUT);
  
  pinMode(motor2_pos, OUTPUT);
  pinMode(motor2_neg, OUTPUT);

  // Why??
  pinMode(8,OUTPUT);
  
}

void goForward(){
  digitalWrite(motor1_pos,LOW);
  digitalWrite(motor1_neg,HIGH);
  
  digitalWrite(motor2_pos,HIGH);
  digitalWrite(motor2_neg,LOW);
}


void turnLeft(){
  digitalWrite(motor1_pos,HIGH);
  digitalWrite(motor1_neg,LOW);
  
  digitalWrite(motor2_pos,HIGH);
  digitalWrite(motor2_neg,LOW);
  delay(500);
  stopMotors();
}

void turnRight(){
  digitalWrite(motor1_pos, LOW);
  digitalWrite(motor1_neg, HIGH);
  
  digitalWrite(motor2_pos, LOW);
  digitalWrite(motor2_neg, HIGH);
  delay(500);
  stopMotors();
}

void stopMotors(){
  digitalWrite(7,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(4,LOW); 
}

void lookRight(){
  ServoOne.write(0);
  delay(500);
}

void lookLeft(){
  ServoOne.write(180);
  delay(500);
}

void lookForward(){
  ServoOne.write(90);
  delay(500);
}

double getDistance(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ( duration / 2 ) / 29.1;
  return distance;
}

void loop()
{
  double distance = getDistance();
  if(distance > 20){
    lookForward();
    goForward();  
  }else{
    stopMotors();
    lookRight();
    distance = getDistance();
    if(distance > 20){
      turnRight();
    }else{
      stopMotors();
      lookLeft();
      distance = getDistance();
      if(distance > 20){
        turnLeft();
      }
    }
  }
}    
