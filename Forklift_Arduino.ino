#include <Stepper.h>

//DC Motor pins
#define pin1 8
#define pin2 9
#define pin3 10
#define pin4 11

//stepper motor pins
#define pin5 4
#define pin6 5
#define pin7 6
#define pin8 7

const int SR = 2048;
const int rpm = 6;

Stepper Mystepper = Stepper(SR,pin5,pin6,pin7,pin8);

void setup() {
    Serial.begin(9600);
    pinMode(pin1,OUTPUT);
    pinMode(pin2,OUTPUT);
    pinMode(pin3,OUTPUT);
    pinMode(pin4,OUTPUT);
    Mystepper.setSpeed(rpm);
}

void loop() {
    if (Serial.available() > 0) {
        char incomingByte = Serial.read();
        switch(incomingByte){
           case 'a' :forkliftMotor(1,0,1,0); //forward        
               break;
           case 'b' :forkliftMotor(0,1,0,1); //back        
               break;
           case 'c' :forkliftMotor(0,0,1,0); //RIGHT      
               break;
           case 'd' :forkliftMotor(1,0,0,0); //LEFT       
               break;
           case 'e' :forkliftMotor(1,0,0,0); //STOP car        
               break;
           case 'f' :fokliftHand(Mystepper,SR); //Top        
               break;
           case 'g' :fokliftHand(Mystepper,-SR); //bottom        
               break;
           case 'k' :fokliftHand(Mystepper,0); //STOP        
               break;
          }
    }
}

void forkliftMotor(int Mode1,int Mode2,int Mode3,int Mode4){
    digitalWrite(pin1,Mode1);
    digitalWrite(pin2,Mode2);
    digitalWrite(pin3,Mode3);
    digitalWrite(pin4,Mode4);
}

void fokliftHand(Stepper stepPer ,  int SR){ 
  stepPer.step(SR);
  delay(1);
  stepPer.step(SR);
}
