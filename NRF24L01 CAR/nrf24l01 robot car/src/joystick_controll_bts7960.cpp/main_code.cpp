// controll the bts7960 motor driver using joystick 

#include<Arduino.h>

// define the joystick pot value 
const int POTX = A0;
const int POTY = A1;

// define the bts7960 pin 
const int l_en = 2;
const int r_en = 3;
const int l_pwm = 4;
const int r_pwm = 5;

int potxvalue = LOW;
int potyvalue = LOW;

void setup(){
    // define the bud rate so in this case i am using 9600 bits per second 
    Serial.begin(9600);

    pinMode(POTX , INPUT);
    pinMode(POTY , INPUT);

    pinMode(l_en , OUTPUT);
    pinMode(r_en , OUTPUT);
    pinMode(l_pwm , OUTPUT);
    pinMode(r_pwm , OUTPUT);

    // ENABLE THE LEFT AND RIGHT PIN 
    digitalWrite(l_en , HIGH);
    digitalWrite(r_en , HIGH);

    digitalWrite(l_pwm , HIGH);
    delay(1000); //delay for 1000 millisecond 
    digitalWrite(l_pwm , LOW);
    delay(1000); //delay for 1000 millisecond 
    digitalWrite(r_pwm , HIGH);
    delay(1000) ; //delay for 1000 millisecond  
    digitalWrite(r_pwm , LOW);
    delay(1000); //delay for 1000 millisecond 


}

void loop(){

    potxvalue = analogRead(POTX);
    potyvalue = analogRead(POTY);

    // lets map
    int potxmap = map(potxvalue , 0 , 1023 , 0, 255 );
    int potymap = map(potyvalue , 0 , 1023 , 0 , 255);
    
    if(potxmap >= 130){
        // int potxmapvalue = map(potxvalue , 500 , 1023 , 130 , 255);
        // analogWrite(l_pwm , potxmapvalue);
        digitalWrite(l_pwm , HIGH);
        digitalWrite(r_pwm , LOW);
    }
    else if (potxmap <= 120)
    {
        digitalWrite(l_pwm , LOW);
        digitalWrite(r_pwm , HIGH);
    }
    
    else{
        digitalWrite(l_pwm , LOW);
        digitalWrite(r_pwm , LOW);
    }
    
    


    // print on the serial monitor
    Serial.print("POTX = ");
    Serial.print(potxmap);
    Serial.print(",");

    Serial.print("POTY = ");
    Serial.println(potymap);

    delay(15);
    

}