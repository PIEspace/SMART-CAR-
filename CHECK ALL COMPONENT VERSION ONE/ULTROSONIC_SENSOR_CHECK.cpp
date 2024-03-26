// Connect the ultrasonic sensor with Arduino mega . 

#include<Arduino.h>

//define the first ultrasonic sensor 
const int trigPin_ONE = 22;  // The trig pin is connected to pin number 22.
const int echoPin_ONE = 24;  // The echo pin is connected to pin number 24.

// define the second ultrasonic sensor 
const int trigPin_TWO = 26;  // The trig pin is connected to pin number 26.
const int echoPin_TWO = 28;  // The echo pin is connected to pin number 28.

//define the third ultrasonic sensor 
const int trigPin_THREE = 30;  // The trig pin is connected to pin number 30.
const int echoPin_THREE = 32;  // The echo pin is connected to pin number 32.

void setup() {
  Serial.begin(9600);

  // define the first ultrasonic sensor pinMode 
  pinMode(trigPin_ONE, OUTPUT);
  pinMode(echoPin_ONE, INPUT);
  
  // define the second ultrasonic sensor pinMode 
  pinMode(trigPin_TWO, OUTPUT);
  pinMode(echoPin_TWO, INPUT);
  
  // define the third ultrasonic sensor pinMode 
  pinMode(trigPin_THREE, OUTPUT);
  pinMode(echoPin_THREE, INPUT);
}

void loop() {

  
  long duration_ONE, distance_ONE;
  digitalWrite(trigPin_ONE, LOW);  // Ensure the trigger pin is low
  delayMicroseconds(2);

  digitalWrite(trigPin_ONE, HIGH);  // Send a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPin_ONE, LOW);

  duration_ONE = pulseIn(echoPin_ONE, HIGH);  // Measure the pulse
  distance_ONE = duration_ONE * 0.034 / 2;    // Calculate distance in cm


  
  long duration_TWO, distance_TWO;
  digitalWrite(trigPin_TWO, LOW);  // Ensure the trigger pin is low
  delayMicroseconds(2);

  digitalWrite(trigPin_TWO, HIGH);  // Send a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPin_TWO, LOW);

  duration_TWO = pulseIn(echoPin_TWO, HIGH);  // Measure the pulse
  distance_TWO = duration_TWO * 0.034 / 2;    // Calculate distance in cm



  long duration_THREE, distance_THREE;
  digitalWrite(trigPin_THREE, LOW);  // Ensure the trigger pin is low
  delayMicroseconds(2);

  digitalWrite(trigPin_THREE, HIGH);  // Send a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPin_THREE, LOW);

  duration_THREE = pulseIn(echoPin_THREE, HIGH);  // Measure the pulse
  distance_THREE = duration_THREE * 0.034 / 2;    // Calculate distance in cm

  // print on the serial monitor 

  Serial.print("Distance_ONE : ");
  Serial.print(distance_ONE);
  Serial.print(" cm");
  Serial.print(" , ");

  Serial.print("Distance_TWO : ");
  Serial.print(distance_TWO);
  Serial.print(" cm");
  Serial.print(" , ");

  Serial.print("Distance_THREE : ");
  Serial.print(distance_THREE);
  Serial.println(" cm");
  
  delay(100);
}
