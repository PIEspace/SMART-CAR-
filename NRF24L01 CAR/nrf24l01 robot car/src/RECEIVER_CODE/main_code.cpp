// check the nrf24l01 module 
// this is  a receiver section 
#include<Arduino.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27 , 16 , 2);

// define the ce and cns pin 
const int CE = 7;
const int CNS = 8;
RF24 radio (CE , CNS);

// DEFINE THE ADDRESS 
const byte address[][6] = {"00001" , "00002"};

// define the joystick 
const int anglex = A0;
const int angley = A3;

unsigned char transmitter_command = 0;



// define the buzzer 
const int buzzer = 9;


void buzzer_tone (){
    

     int frequency[] = {400,800,1200,1600,2000,2400,2800,3200,3600,4000};

     for (int  i = 0; i <= 10; i++)
     {
        tone(buzzer , frequency[i] , 100 );
        delay(50);
     }

     digitalWrite(buzzer , LOW);
}




void setup(){
    Serial.begin(9600) ; //in this case i am using 9600 bits per second 
    radio.begin();
    radio.openWritingPipe(address[0]) ; //00001
    radio.openReadingPipe(1 , address[1]); //00002
    radio.setPALevel(RF24_PA_HIGH);
    

    pinMode(anglex , INPUT);
    pinMode(angley , INPUT);

    pinMode(buzzer , OUTPUT);

    buzzer_tone();

    lcd.init();
    lcd.backlight();
    lcd.setCursor(4,0);
    lcd.print("PIE.SPACE");
    


}

void loop(){
    radio.stopListening();
    radio.write(&transmitter_command , sizeof(transmitter_command));

    // define the pot x 
    int potxvalue = analogRead(anglex);
    int potyvalue = analogRead(angley);

    if(potxvalue < 100){
        lcd.clear();
        lcd.setCursor(4,1);
        lcd.print("BACKWARD");
        delay(100);
        transmitter_command = 1;
    }
    else if (potxvalue > 900)
    {
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("FORWORD");
        delay(100);
        transmitter_command = 2;
    }

    else if (potyvalue <100)
    {
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("LEFT");
        delay(100);
        transmitter_command = 3;
    }
    else if (potyvalue >900)
    {
        lcd.clear();
        lcd.setCursor(4,1);
        lcd.print("RIGHT");
        delay(100);
        transmitter_command = 4;
    }
    else{
        transmitter_command = 0 ;
        lcd.setCursor(4,0);
        lcd.print("PIE.SPACE");
    }



    
    



    

    // print the joystick value 

}