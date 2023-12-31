// check the nrf24l01 module
// this is a transmitter section 
#include<Arduino.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

// define the ce and cns  pin 
const int CE = 7 ;
const int CNS = 6 ;

// define the radio 
RF24 radio (CE , CNS);

// define the address 
const byte address[][6] = {"00001" , "00002"};

unsigned char receiver_command = 0;

// define the motor driver 
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

    radio.begin();
    radio.openWritingPipe(address[1]); //0002
    radio.openReadingPipe(1,address[0]); //0001
    radio.setPALevel(RF24_PA_HIGH);
   

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

    radio.startListening();
    if(radio.available()){
        delay(10);
        radio.read(&receiver_command , sizeof(receiver_command));
        Serial.println(receiver_command);
    }

    if(receiver_command == 1){
        digitalWrite(r_pwm , HIGH);
        digitalWrite(r_pwm_one , HIGH);
    }
    else if (receiver_command ==2 )
    {
        digitalWrite(l_pwm , HIGH);
        digitalWrite(l_pwm_one , HIGH);
        
    }
    else if (receiver_command ==3 )
    {
        digitalWrite(l_pwm , HIGH);
        digitalWrite(r_pwm_one , HIGH);
    }
    else if (receiver_command ==4 )
    {
        digitalWrite(r_pwm , HIGH);
        digitalWrite(l_pwm_one , HIGH);
    }
    
    
    
    else if (receiver_command == 0  )
    {
        digitalWrite(l_pwm , LOW);
        digitalWrite(l_pwm_one , LOW);
        digitalWrite(r_pwm , LOW);
        digitalWrite(r_pwm_one , LOW);
    }
    else{
        digitalWrite(l_pwm , LOW);
        digitalWrite(l_pwm_one , LOW);
        digitalWrite(r_pwm , LOW);
        digitalWrite(r_pwm_one , LOW);

    }

}
    



    



    




