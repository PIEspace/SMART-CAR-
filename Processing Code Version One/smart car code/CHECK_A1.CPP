// SMART CAR 

// define the  transmitter code in this code
// i am using arduino mega . 
// This is the code, you will get it easily on github. https://github.com/PIEspace?tab=repositories
// You can also follow me on Instagram? https://www.instagram.com/creativeindia__/?hl=en

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// define the CE and CNS pin
const int CE_PIN = 11;
const int CNS_PIN = 12;
// define the radio
RF24 radio(CE_PIN, CNS_PIN);
// define the address
const byte address[][7] = {"12345", "123456"};



// define the fist motor driver
const int L_EN_ONE = 6;
const int R_EN_ONE = 5;
const int LPWM_ONE = 4;
const int RPWM_ONE = 3;
// define the second motor driver
const int L_EN_TWO = 10;
const int R_EN_TWO = 9;
const int LPWM_TWO = 8;
const int RPWM_TWO = 7;

// max size of this structure is 32 bytes
struct Data_Package
{
    // DEFINE THE MPU6050 DATA
    float roll_value;
    float pitch_value;
    float yaw_value;
    // DEFINE THE JOYSTICK DATA
    byte First_Joystick_Data_X;
    byte First_Joystick_Data_Y;
    byte Second_Joystick_Data_X;
    byte Second_Joystick_Data_Y;
};

Data_Package data; // create a variable with the above structure

int  Steering, Throttle;
int motorSpeedA = 0;
int motorSpeedB = 0;

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

void setup()
{

    // define the bud rate
    // in this case i am using 9600 bits per second
    Serial.begin(9600);

    radio.begin();
    radio.openWritingPipe(address[1]);    // the address is = 123456
    radio.openReadingPipe(1, address[0]); // the address is 12345
    radio.setPALevel(RF24_PA_HIGH);


    // define the pinMode function for motor driver
    // DEFINE THE FIRST MOTOR DRIVER 
    pinMode(L_EN_ONE, OUTPUT);
    pinMode(R_EN_ONE, OUTPUT);
    pinMode(LPWM_ONE, OUTPUT);
    pinMode(RPWM_ONE, OUTPUT);

    // DEFINE THE SECOND MOTOR DRIVER 
    pinMode(L_EN_TWO, OUTPUT);
    pinMode(R_EN_TWO, OUTPUT);
    pinMode(LPWM_TWO, OUTPUT);
    pinMode(RPWM_TWO, OUTPUT);

}

void loop()
{

    radio.startListening();

    currentTime = millis();
    if(currentTime - lastReceiveTime > 1000){
        resetData();
    }

    if (radio.available())
    {
        radio.read(&data, sizeof(Data_Package));
        lastReceiveTime = millis();
        
    }

    // receive the data from the joystic in the left_right_value and FORWARD_BACKWARD_VALUE to store the data
    Throttle = data.First_Joystick_Data_X;
    Steering = data.First_Joystick_Data_Y;



    if (Throttle < 110)
    {
        digitalWrite(LPWM_ONE, HIGH);
        digitalWrite(RPWM_ONE, LOW);

        digitalWrite(LPWM_TWO, HIGH);
        digitalWrite(RPWM_TWO, LOW);

        motorSpeedA = map(Throttle , 110 , 0 , 0 , 255);
        motorSpeedB = map(Throttle , 110 , 0 , 0 , 255);
    }

    else if (Throttle > 140)
    {
        digitalWrite(LPWM_ONE, LOW);
        digitalWrite(RPWM_ONE, HIGH);

        digitalWrite(LPWM_TWO, LOW);
        digitalWrite(RPWM_TWO, HIGH);

        motorSpeedA = map(Throttle , 140 , 255  , 0 , 255);
        motorSpeedB = map(Throttle , 140 , 255 , 0 , 255);
    }

    else if(Steering < 110){

        digitalWrite(LPWM_ONE, HIGH);
        digitalWrite(RPWM_ONE, LOW);

        digitalWrite(LPWM_TWO, LOW);
        digitalWrite(RPWM_TWO, HIGH);

        motorSpeedA = map(Steering , 110 , 0 , 0 , 255);
        motorSpeedB = map(Steering , 110 , 0 , 0 , 255);

    }

    else if (Steering > 140){

        digitalWrite(LPWM_ONE, LOW);
        digitalWrite(RPWM_ONE, HIGH);

        digitalWrite(LPWM_TWO, HIGH);
        digitalWrite(RPWM_TWO, LOW);

        motorSpeedA = map(Steering , 140 , 255  , 0 , 255);
        motorSpeedB = map(Steering , 140 , 255 , 0 , 255);

    }

    else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }


  analogWrite(L_EN_ONE, motorSpeedA); // Send PWM signal to motor A
  analogWrite(R_EN_ONE, motorSpeedB); // Send PWM signal to motor B

  analogWrite(L_EN_TWO, motorSpeedA); // Send PWM signal to motor A
  analogWrite(R_EN_TWO, motorSpeedB); // Send PWM signal to motor B



}

void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.First_Joystick_Data_X = 127;
  data.First_Joystick_Data_Y = 127;

}