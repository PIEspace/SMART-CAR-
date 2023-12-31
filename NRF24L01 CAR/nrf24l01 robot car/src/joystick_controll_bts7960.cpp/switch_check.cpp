// check the switch value 


#include<Arduino.h>


const int pushbutton = 6;

void setup(){
    Serial.begin(9600); //in this case i am using 9600 bits per second 
    pinMode(pushbutton , INPUT);

}

void loop(){
    int pushbuttonvalue = digitalRead(pushbutton);

    // print on the serial monitor 
    Serial.print("pushbutton = ");
    Serial.println(pushbuttonvalue);
    delay(15); //delay for 15 millisecond 

}