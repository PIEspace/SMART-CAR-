// THIS IS A RECEIVER CODE 
//CONTROL BOX VERSION TWO
//THIS IS A MAIN RECEIVER BOX TO SHOW THE PROCESSING CODE 


#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CNS pin
const int CE_PIN = 7;
const int CNS_PIN = 8;

// Define the radio
RF24 radio(CE_PIN, CNS_PIN);

// Define the address
const byte address[][7] = {"12345", "123456"};

struct data_package
{   //define the roll , pitch , yaw 
    float roll_value;
    float pitch_value;
    float yaw_value;
    
    //define the joystick 
    byte First_Joystick_Data_X;
    byte First_Joystick_Data_Y;
    byte Second_Joystick_Data_X;
    byte Second_Joystick_Data_Y;

    // DEFINE THE POTENTIOMETER DATA
    byte First_Pot_Data;
    byte Second_Pot_Data;

    // define the pushbutton value 
    byte First_Push_Butt_Data;
    byte Second_Push_Butt_Data;
    byte Third_Push_Butt_Data;
    byte Fourth_Push_Butt_Data;

    float AccX_value;
    float AccY_value;
    float AccZ_value;

    

    

};

data_package data;



void setup()
{
    // Define the baud rate
    Serial.begin(9600);

    // Define the radio
    radio.begin();
    radio.openWritingPipe(address[1]);
    radio.openReadingPipe(1, address[0]);
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();
}

void loop()
{
    if (radio.available())
    {
        radio.read(&data, sizeof(data_package));

        


        //DEFINE THE MPU6050
        Serial.print(data.roll_value);
        Serial.print(" , ");
        Serial.print(data.pitch_value);
        Serial.print(" , ");
        Serial.print(data.yaw_value);
        Serial.print(" , ");
        //DEFINE THE JOYSTICK
        Serial.print(data.First_Joystick_Data_X);
        Serial.print(" , ");
        Serial.print(data.First_Joystick_Data_Y);
        Serial.print(" , ");
        Serial.print(data.Second_Joystick_Data_X);
        Serial.print(" , ");
        Serial.print(data.Second_Joystick_Data_Y);
        Serial.print(" , ");
        //DEFINE THE POTENTIOMETER 
        Serial.print(data.First_Pot_Data);
        Serial.print(" , ");
        Serial.print(data.Second_Pot_Data);
        Serial.print(" , ");
        //define the pushbutton 
        Serial.print(data.First_Push_Butt_Data);
        Serial.print(" , ");
        Serial.print(data.Second_Push_Butt_Data);
        Serial.print(" , ");
        Serial.print(data.Third_Push_Butt_Data);
        Serial.print(" , ");
        Serial.print(data.Fourth_Push_Butt_Data);
        Serial.print(" , ");
        Serial.print(data.AccX_value);
        Serial.print(" , ");
        Serial.print(data.AccY_value);
        Serial.print(" , ");
        Serial.println(data.AccZ_value);
       

        

        
        


        
    }
}
