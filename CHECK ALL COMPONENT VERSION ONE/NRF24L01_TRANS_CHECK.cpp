// check the nrf24l01 module
// this is a transmitter section i am using arduino mega 
#include<Arduino.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

// define the ce and cns  pin 
const int CE = 11 ;
const int CNS = 12 ;

// define the radio 
RF24 radio (CE , CNS);

// define the address 
const byte address[6] = "00001";

void setup(){

    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();



}

void loop(){

    const char text[] = "Car is now connected";
    radio.write(&text , sizeof(text));
    delay(100);

}