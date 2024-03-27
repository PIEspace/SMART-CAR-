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


// define the ultrasonic sensor 
const int Trig_Pin_One = 22;
const int Echo_Pin_One = 24;

long Distance_One ;
long Duration_One ;

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
struct data_package
{
    byte First_Joystick_X;
    byte First_Joystick_Y;
    byte Second_Joystick_X;
    byte Second_Joystick_Y;
    byte First_Potentiometer;
    byte Second_Potentiometer;
    byte First_Button;
    byte Second_Button;
    byte Third_Button;
    byte Fourth_Button;

};
data_package data; // create a variable with the above structure

int  steering, throttle;
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
    radio.startListening();

    // define the pinMode function for motor driver
    pinMode(L_EN_ONE, OUTPUT);
    pinMode(R_EN_ONE, OUTPUT);
    pinMode(LPWM_ONE, OUTPUT);
    pinMode(RPWM_ONE, OUTPUT);

    pinMode(L_EN_TWO, OUTPUT);
    pinMode(R_EN_TWO, OUTPUT);
    pinMode(LPWM_TWO, OUTPUT);
    pinMode(RPWM_TWO, OUTPUT);

    // define the ultrasonic sensor 
    pinMode(Trig_Pin_One , OUTPUT);
    pinMode(Echo_Pin_One , INPUT);

}

void loop()
{
    currentTime = millis();
    if(currentTime - lastReceiveTime > 1000){
        resetData();
    }

    if (radio.available())
    {
        radio.read(&data, sizeof(data_package));
        lastReceiveTime = millis();
        
    }

    // receive the data from the joystic in the left_right_value and FORWARD_BACKWARD_VALUE to store the data
    throttle = data.First_Joystick_X;
    steering = data.First_Joystick_Y;



    if (throttle < 110)
    {
        digitalWrite(LPWM_ONE, HIGH);
        digitalWrite(RPWM_ONE, LOW);

        digitalWrite(LPWM_TWO, HIGH);
        digitalWrite(RPWM_TWO, LOW);

        motorSpeedA = map(throttle , 110 , 0 , 0 , 255);
        motorSpeedB = map(throttle , 110 , 0 , 0 , 255);
    }

    else if (throttle > 140)
    {
        digitalWrite(LPWM_ONE, LOW);
        digitalWrite(RPWM_ONE, HIGH);

        digitalWrite(LPWM_TWO, LOW);
        digitalWrite(RPWM_TWO, HIGH);

        motorSpeedA = map(throttle , 140 , 255  , 0 , 255);
        motorSpeedB = map(throttle , 140 , 255 , 0 , 255);
    }

    else if(steering < 110){

        digitalWrite(LPWM_ONE, HIGH);
        digitalWrite(RPWM_ONE, LOW);

        digitalWrite(LPWM_TWO, LOW);
        digitalWrite(RPWM_TWO, HIGH);

        motorSpeedA = map(steering , 110 , 0 , 0 , 255);
        motorSpeedB = map(steering , 110 , 0 , 0 , 255);

    }

    else if (steering > 140){

        digitalWrite(LPWM_ONE, LOW);
        digitalWrite(RPWM_ONE, HIGH);

        digitalWrite(LPWM_TWO, HIGH);
        digitalWrite(RPWM_TWO, LOW);

        motorSpeedA = map(steering , 140 , 255  , 0 , 255);
        motorSpeedB = map(steering , 140 , 255 , 0 , 255);

    }

    else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

    analogWrite(L_EN_ONE, motorSpeedA); // Send PWM signal to motor A
    analogWrite(R_EN_ONE, motorSpeedB); // Send PWM signal to motor B

    analogWrite(L_EN_TWO, motorSpeedA); // Send PWM signal to motor A
    analogWrite(R_EN_TWO, motorSpeedB); // Send PWM signal to motor B


 //   ultrasonic();







  



}

void ultrasonic(){
    
    digitalWrite(Trig_Pin_One , LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Pin_One , HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Pin_One , LOW);

    Duration_One = pulseIn(Echo_Pin_One , HIGH);
    Distance_One = Duration_One * 0.034 /2 ;

    if(Distance_One <= 15){
        digitalWrite(LPWM_ONE, HIGH);
        digitalWrite(RPWM_ONE, LOW);

        digitalWrite(LPWM_TWO, LOW);
        digitalWrite(RPWM_TWO, HIGH);
    }

    else {
        digitalWrite(LPWM_ONE, LOW);
        digitalWrite(RPWM_ONE, LOW);

        digitalWrite(LPWM_TWO, LOW);
        digitalWrite(RPWM_TWO, LOW);

    }

}

void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.First_Joystick_X = 127;
  data.First_Joystick_Y = 127;

}