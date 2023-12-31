// lets check the bts7960 motor driver 

#include<Arduino.h>

// define the enable and pwm pins 
const int l_en = 2;
const int r_en = 3;
const int r_pwm = 4;
const int l_pwm = 5;

void setup(){
    // define the bud rate 
    // so in this case i am using 9600 bits per second 
    Serial.begin(9600);

    pinMode(l_en , OUTPUT);
    pinMode(r_en , OUTPUT);
    pinMode(l_pwm , OUTPUT);
    pinMode(r_pwm , OUTPUT);


    // TURN ON LEFT AND RIGHT ENABLE PIN 
    digitalWrite(l_en , HIGH);
    digitalWrite(r_en , HIGH);

}

void loop(){

    if(Serial.available()){
        char character = Serial.read();

        if(character == 'a' || character == 'A'){
            digitalWrite(l_pwm , HIGH);
            Serial.println("TURN ON LEFT SIDE MOTOR ! ");
        }
        else if (character == 'b' || character =='B')
        {
            digitalWrite(l_pwm , LOW);
            Serial.println("TURN OFF LEFT SIDE MOTOR !");
        }

        else if (character == 'c' || character =='C')
        {
            digitalWrite(r_pwm , HIGH);
            Serial.println("TURN ON RIGHT SIDE MOTOR !");
        }
        else if (character =='d' ||character =='D')
        {
            digitalWrite(r_pwm , LOW);
            Serial.println("TURN OFF RIGHT SIDE MOTOR ! ");
        }
        
        
        
    }

}