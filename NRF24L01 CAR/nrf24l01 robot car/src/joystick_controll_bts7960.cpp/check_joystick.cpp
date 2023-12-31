// check the joystick 

#include<Arduino.h>

const int potx = A0;
const int poty = A1;

void setup(){
    Serial.begin(9600) ; //define the bud rate in this case i am using 9600 bits per second 

    pinMode(potx , INPUT);
    pinMode(poty , INPUT);
}

void loop(){

    int potxvalue = analogRead(potx);
    int potyvalue = analogRead(poty);


    // print on the serial monitor
    Serial.print("POTX = ");
    Serial.print(potxvalue);
    Serial.print(",");
    Serial.print("POTY = ");
    Serial.println(potyvalue);

    delay(15); //delay for 15 millisecond 

}