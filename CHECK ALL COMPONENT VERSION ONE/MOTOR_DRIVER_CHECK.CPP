// check the motor driver 
// in this case i am using bts7960 motor driver 

#include<Arduino.h>

// define the motor pins 
// DEFINE THE FIRST MOTOR DRIVER 
const int  R_PWM_ONE =  3 ;
const int  L_PWM_ONE =  4 ;
const int  R_EN_ONE =  5 ;
const int  L_EN_ONE =  6 ;

// DEFINE THE SECOND MOTOR DRIVER 
const int  R_PWM_TWO =  7 ;
const int  L_PWM_TWO =  8 ;
const int  R_EN_TWO =  9 ;
const int  L_EN_TWO =  10 ;

void setup(){
    // define the bud rate so in this case i am using 9600 bits per second (BPS)
    Serial.begin(9600);
    
    //DEFINE THE FIRST MOTOR pinMode
    pinMode(R_PWM_ONE , OUTPUT);
    pinMode(L_PWM_ONE , OUTPUT);
    pinMode(R_EN_ONE , OUTPUT);
    pinMode(L_EN_ONE , OUTPUT);

    //DEFINE THE SECOND MOTOR pinMode
    pinMode(R_PWM_TWO , OUTPUT);
    pinMode(L_PWM_TWO , OUTPUT);
    pinMode(R_EN_TWO , OUTPUT);
    pinMode(L_EN_TWO , OUTPUT);
    
    //high both left and right enable pins 
    digitalWrite(R_EN_ONE , HIGH);
    digitalWrite(L_EN_ONE , HIGH);

    digitalWrite(R_EN_TWO , HIGH);
    digitalWrite(L_EN_TWO , HIGH);
}

void loop(){

    digitalWrite(R_EN_ONE , HIGH);
    digitalWrite(L_EN_ONE , HIGH);

    digitalWrite(R_EN_TWO , HIGH);
    digitalWrite(L_EN_TWO , HIGH);


    // TURN ON RIGHT FOR 5 SECOND 
    digitalWrite(R_PWM_ONE , HIGH);
    digitalWrite(R_PWM_TWO , HIGH);
    delay(3000);

    digitalWrite(R_PWM_ONE , LOW);
    digitalWrite(R_PWM_TWO , LOW);
    delay(1000);

    // TURN ON LEFT FOR 5 SECOND 
    digitalWrite(L_PWM_ONE , HIGH);
    digitalWrite(L_PWM_TWO , HIGH);
    delay(3000);

    digitalWrite(L_PWM_ONE , LOW);
    digitalWrite(L_PWM_TWO , LOW);
    delay(1000);




}