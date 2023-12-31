// check the joystic 

#include<Arduino.h>

const int anglex = A0;
const int angley = A1;


void setup(){
    // define the bud rate known as 9600 bits per second (bps)
    Serial.begin(9600);
    pinMode(anglex , INPUT);
    pinMode(angley , INPUT);
}

void loop(){
    int anglexValue = analogRead(anglex);
    int angleyValue = analogRead(angley);

    // print on the serial monitor 
    Serial.print("anglex = ");
    Serial.print(anglexValue);
    Serial.print(",");

    Serial.print("angley = ");
    Serial.println(angleyValue);


}
