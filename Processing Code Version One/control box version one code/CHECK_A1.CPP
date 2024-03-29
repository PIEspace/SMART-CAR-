// this is a transmitter code 
// CONTROL BOX VERSION ONE 


#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <MPU6050.h>
#include<SimpleKalmanFilter.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>


// DEFINE THE OLED DISPLAY 
#define SCREEN_WIDTH 128 //DEFINE THE WIDTH OF  OLED DISPLAY IN PIXELS
#define SCREEN_HEIGHT 64 //DEFINE THE HEIGHT OF OLED DISPLAY IN PIXELS
// DEFINE THE SSD1306 DISPLAY FOR I2C CONNECTION (SCL , SDA)
#define OLED_RESET  -1 
Adafruit_SSD1306 display (SCREEN_WIDTH , SCREEN_HEIGHT , &Wire , OLED_RESET);


//DEFINE THE BUZZER 
const int Buzzer = 10 ; //ATTACH THE BUZZER ON PIN NUMBER D10 

// DEFINE THE JOYSTICK
const int First_Joystick_x = A0;
const int First_Joystick_Y = A1;
const int Second_Joystick_X = A2;
const int Second_Joystick_Y = A3;

// DEFINE THE POTENTIOMETER 
const int First_Potentiometer = A6;
const int Second_Potentiometer = A7;

// DEFINE THE PUSHBUTTON 
const int First_Push_Button = 2 ;
const int Second_Push_Button = 3;
const int Third_Push_Button = 4;
const int Four_Push_Button = 5;

// DEFINE THE GLOBAL VARIABLES 

// DEFINE THE JOYSTICK GLOBAL VARIABLES 
int FIRST_JOYSTICK_X_VALUE = 0;
int FIRST_JOYSTICK_Y_VALUE = 0;
int SECOND_JOYSTICK_X_VALUE = 0;
int SECOND_JOYSTICK_Y_VALUE = 0;


// DEFINE THE POTENTIOMETER GLOBAL VARIABLES 
int FIRST_POT_VALUE = 0;
int SECOND_POT_VALUE = 0;


// DEFINE THE PUSHBUTTON GLOBAL VARIABLES 
int FIRST_BUTTON_VALUE = 0;
int SECOND_BUTTON_VALUE = 0;
int THIRD_BUTTON_VALUE = 0;
int FOURTH_BUTTON_VALUE = 0;


// DEFINE THE MPU6050 SENSOR 
MPU6050 mpu;
int16_t ax, ay, az; // Accelerometer raw data
int16_t gx, gy, gz; // Gyroscope raw data
float AccX, AccY, AccZ;    // Accelerometer scaled data
float GyroX, GyroY, GyroZ; // Gyroscope scaled data
float roll, pitch, yaw; // Calculated roll and pitch angles
// Define Kalman filter parameters
SimpleKalmanFilter kalmanPitch(2, 2, 0.15); // Q, R, initial estimate
SimpleKalmanFilter kalmanRoll(2, 2, 0.15);  // Q, R, initial estimate
SimpleKalmanFilter kalmanYaw(2, 2, 0.15);   // Q , R , initial estimate






// DEFINE THE NRF24L01 MODULE 
// Define the CE and CNS pin
const int CE_PIN = 7;
const int CNS_PIN = 8;
// Define the radio
RF24 radio(CE_PIN, CNS_PIN);
// Define the address
const byte address[][7] = {"12345", "123456"};


// DEFINE THE DATA PACKAGE FOR NRF24L01 MODULE 
struct data_package
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
    // DEFINE THE POTENTIOMETER DATA
    byte First_Pot_Data;
    byte Second_Pot_Data;
    // DEFINE THE BUTTON DATA
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
    radio.openWritingPipe(address[0]);
    radio.openReadingPipe(1, address[1]);
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();

    // Define the MPU6050
    Wire.begin();
    mpu.initialize();
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);


    //define the pinMode for buzzer 
    pinMode(Buzzer , OUTPUT);
    //define the pinMode for joystick 
    pinMode(First_Joystick_x , INPUT);
    pinMode(First_Joystick_Y , INPUT);
    pinMode(Second_Joystick_X , INPUT);
    pinMode(Second_Joystick_Y , INPUT);
    //define the pinMode for potentiometer 
    pinMode(First_Potentiometer , INPUT);
    pinMode(Second_Potentiometer  , INPUT);
    //define the pinMode for button 
    pinMode(First_Push_Button , INPUT);
    pinMode(Second_Push_Button , INPUT);
    pinMode(Third_Push_Button , INPUT);
    pinMode(Four_Push_Button , INPUT);


    // DEFINE THE ALL INITIAL VALUE 
    data.First_Joystick_Data_X = 127;
    data.First_Joystick_Data_Y = 127;
    data.Second_Joystick_Data_X= 127;
    data.Second_Joystick_Data_Y = 127;

    data.First_Pot_Data = 0 ;
    data.Second_Pot_Data= 0;

    data.First_Push_Butt_Data = 0 ;
    data.Second_Push_Butt_Data = 0;
    data.Third_Push_Butt_Data = 0;
    data.Fourth_Push_Butt_Data = 0;


    // DEFINE THE SSD1306 DISPLAY

    // Initialize with the I2C addr 0x3C (for the 128x64)
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    // Clear the buffer
    display.clearDisplay();

    // Set text color to white
    display.setTextColor(SSD1306_WHITE);

    // Set text size
    display.setTextSize(1);

    // Set cursor position
    display.setCursor(0, 0);

    // Print "Hello, World!"
    display.println("Connection....");

    // Display the message
    display.display();

    delay(1000);
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,3);
    display.println("Connected....");
    display.display();



}

void loop()
{

    data.First_Joystick_Data_X = map(analogRead(First_Joystick_x) , 0 , 1023 , 0 , 255);
    data.First_Joystick_Data_Y = map(analogRead(First_Joystick_Y) , 0 , 1023 , 0 , 255);

    data.Second_Joystick_Data_X = map(analogRead(Second_Joystick_X) , 0 , 1023 , 0 , 255);
    data.Second_Joystick_Data_Y = map(analogRead(Second_Joystick_Y) , 0 , 1023 , 0 , 255);

    data.First_Pot_Data = map(analogRead(First_Potentiometer) , 0 , 1023 , 0 , 255);
    data.Second_Pot_Data = map(analogRead(Second_Potentiometer) , 0 , 1023 , 0 , 255);

    data.First_Push_Butt_Data = digitalRead(First_Push_Button);
    data.Second_Push_Butt_Data = digitalRead(Second_Push_Button);
    data.Third_Push_Butt_Data = digitalRead(Third_Push_Button);
    data.Fourth_Push_Butt_Data = digitalRead(Four_Push_Button);




    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // Get raw sensor data

    // Convert raw accelerometer data to G's
    AccX = (float)ax / 16384.0;
    AccY = (float)ay / 16384.0;
    AccZ = (float)az / 16384.0;

    // Convert raw gyroscope data to degrees/second
    GyroX = (float)gx / 131.0;
    GyroY = (float)gy / 131.0;
    GyroZ = (float)gz / 131.0;

    // Calculate roll, pitch, and yaw angles
    roll = atan2(AccY, AccZ) * 180.0 / M_PI;
    pitch = atan(-AccX / sqrt(AccY * AccY + AccZ * AccZ)) * 180.0 / M_PI;
    yaw = atan2(-GyroX, sqrt(GyroY * GyroY + GyroZ * GyroZ)) * 180.0 / M_PI;

    // Apply Kalman filter to smooth pitch and roll angles
    pitch = kalmanPitch.updateEstimate(pitch);
    roll = kalmanRoll.updateEstimate(roll);
    yaw = kalmanYaw.updateEstimate(yaw);



    // Send these values using NRF24L01
    data.roll_value = roll;
    data.pitch_value = pitch;
    data.yaw_value = yaw;

    data.AccX_value = AccX;
    data.AccY_value = AccY;
    data.AccZ_value = AccZ;

   



    radio.write(&data, sizeof(data_package));


    // print all data on oled display 
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Pitch:-");
    display.println(pitch);

    display.setCursor(0 , 10);
    display.print("Roll:-");
    display.println(roll);

    display.setCursor(0, 20);
    display.print("Yaw:-");
    display.println(yaw);

    display.setCursor(0 , 30 );
    display.print("J1_X:- ");
    display.println(data.First_Joystick_Data_X);

    display.setCursor(65 , 30);
    display.print("J1_Y:- ");
    display.println(data.First_Joystick_Data_Y);

    display.setCursor(0 , 40 );
    display.print("J2_X:- ");
    display.println(data.Second_Joystick_Data_X);

    display.setCursor(65 , 40);
    display.print("J2_Y:- ");
    display.println(data.Second_Joystick_Data_Y);

    display.setCursor(0 , 50);
    display.print("P1:-");
    display.println(data.First_Pot_Data);

    display.setCursor(65 , 50);
    display.print("P2:-");
    display.println(data.Second_Pot_Data);

    display.setCursor(80 , 0);
    display.print("B1:-");
    display.println(data.First_Push_Butt_Data);

    display.display();

    delay(10); // Add a small delay to prevent overwhelming the receiver
}
