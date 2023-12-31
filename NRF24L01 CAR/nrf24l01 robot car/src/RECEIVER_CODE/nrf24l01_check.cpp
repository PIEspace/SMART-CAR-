// check the nrf24l01 module 
// this is  a receiver section 
#include<Arduino.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

// define the ce and cns pin 
const int CE = 7;
const int CNS = 8;
RF24 radio (CE , CNS);

// DEFINE THE ADDRESS 
const byte address[6] = "00001";

void setup(){
    Serial.begin(9600) ; //in this case i am using 9600 bits per second 
    radio.begin();
    radio.openReadingPipe(0,address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();

}

void loop(){

    if(radio.available()){
        char  text [32] = "";
        radio.read(&text , sizeof(text));
        // print on the serial monitor
        Serial.print("text = ");
        Serial.println(text);
    }

}