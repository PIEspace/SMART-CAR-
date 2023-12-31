// check the bts7960 motor driver 


#include<Arduino.h>

// define the first motor driver 
const int l_en = 2;
const int r_en = 3;
const int l_pwm = 4;
const int r_pwm = 5;


// define the second motor driver 
const int l_en_one = 8;
const int r_en_one = 9;
const int l_pwm_one = 10 ;
const int r_pwm_one = 11;


void setup(){
    pinMode(l_en , OUTPUT);
    pinMode(r_en , OUTPUT);
    pinMode(l_pwm , OUTPUT);
    pinMode(r_pwm , OUTPUT);

    pinMode(l_en_one , OUTPUT);
    pinMode(r_en_one , OUTPUT);
    pinMode(l_pwm_one , OUTPUT);
    pinMode(r_pwm_one , OUTPUT);

    // enable left and right pin 
    digitalWrite(l_en ,HIGH);
    digitalWrite(r_en , HIGH);

    // enable the second pin 
    digitalWrite(l_en_one , HIGH);
    digitalWrite(r_en_one , HIGH);
}

void loop(){

    // enable left and right pin 
    digitalWrite(l_en ,HIGH);
    digitalWrite(r_en , HIGH);
    digitalWrite(l_en_one , HIGH);
    digitalWrite(r_en_one , HIGH);


// define the left pin of the bts7960 motor driver 
    digitalWrite(l_pwm , HIGH);
    digitalWrite(l_pwm_one , HIGH);
    delay(1000);
    digitalWrite(l_pwm , LOW);
    digitalWrite(l_pwm_one , LOW);
    delay(1000);

    // define the right pin of the bts7960 motor driver 
    digitalWrite(r_pwm , HIGH);
    digitalWrite(r_pwm_one , HIGH);
    delay(1000);
    digitalWrite(r_pwm , LOW);
    digitalWrite(r_pwm_one , LOW);
    delay(1000);




}