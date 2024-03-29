//define the smart car value and also transmitter value 

import processing.serial.*;

//Define the Serial Port Name 
Serial SerialPort;

//Define the Serial Com Port name 
String SerialPortName = "COM3";

//define the roll , pitch , yaw for transmitter 
float Roll_One , Pitch_One , Yaw_One;

int ColorValueOne;
int ColorValueTwo;
int ColorValueThree;
int ColorValueFour;



//define the joystick value 
int First_Joystick_Data_X;
int First_Joystick_Data_Y;
int Second_Joystick_Data_X;
int Second_Joystick_Data_Y;

//define the potentiometer 
int First_Pot_Data;
int Second_Pot_Data;

//define the pushbutton value 
int First_Push_Button_Data;
int Second_Push_Button_Data;
int Third_Push_Button_Data;
int Fourth_Push_Button_Data;

//define the accelerometer value 
int accx_value;
int accy_value;
int accz_value;




void setup(){
  //define the window
  size(1800 , 1000); // Width is 1800PX and Height is 1000 PX 
  //define the title
  surface.setTitle("SMART CAR BY PIE.SPACE");
  //Define the background Color 
  background(0); //background color is black 
  
  //define the serial monitor 
  SerialPort = new Serial(this , SerialPortName , 9600);
  


  noStroke();
  
  
}

void draw(){
  
  if(SerialPort.available() > 0){
    String data = SerialPort.readStringUntil('\n');
    if(data != null){
      String[] angles = data.trim().split(" , ");
      if(angles.length == 16){
        //define the roll , pitch , yaw 
        Roll_One = float(angles[0]);
        Pitch_One = float(angles[1]);
        Yaw_One = float(angles[2]);
        
        //define the joystick 
        First_Joystick_Data_X = int (angles[3]);
        First_Joystick_Data_Y = int (angles[4]);
        Second_Joystick_Data_X = int (angles[5]);
        Second_Joystick_Data_Y = int (angles[6]);
        
        //define the potentiometer
        First_Pot_Data = int (angles[7]);
        Second_Pot_Data = int (angles[8]);
        
        //define the pushbutton 
        First_Push_Button_Data = int (angles[9]);
        Second_Push_Button_Data = int (angles[10]);
        Third_Push_Button_Data = int (angles [11]);
        Fourth_Push_Button_Data  = int(angles[12]);
        
        accx_value = int(angles[13]);
        accy_value = int (angles[14]);
        accz_value = int (angles[15]);
        
        
  
      }
    }
  }
  
  Roll_Pitch_Yaw_Value_One();
  Display_Seprate();
  Display_For_Transmitter();
  Display_For_Receiver();
  Joystick_Data_Value_One();
  Joystick_Data_Value_Two();
  Potentiometer_Value();
  Pushbutton_Value();
  acceleration_value();
}

void acceleration_value(){
  fill(14, 9, 145);
  rect(10 , 260 , 200 , 200 ,5 );
  
  fill(255);
  textSize(18);
  text("AccX :- "+ accx_value + " Values" , 20 , 320 );
  text("AccY :- "+ accy_value + " Values" , 20 , 360);
  text("AccZ :- "+ accz_value + " Values" ,  20 , 400);
  
  fill(255 , 222 , 89);
  rect(13 , 263 , 194 , 30 , 5);
  fill(0);
  textSize(20);
  text("Accleration" , 50 , 285);
  
}


void Pushbutton_Value(){
  
 //define the pushbutton values 
 fill(14, 9, 145);
 rect(620 , 35 , 270 , 100 ,5 );
 
 fill(255);
 textSize(18);
 text("Push_Button_One:-" + First_Push_Button_Data , 630 , 60);
 text("Push_Button_Two:-" + Second_Push_Button_Data , 630 , 80);
 text("Push_Button_Three:-"+Third_Push_Button_Data , 630 , 100);
 text("Push_Button_Four:- "+Fourth_Push_Button_Data , 630 , 120);
 
 //define the first circle / first pushbutton 
 fill(ColorValueOne);
 circle(860 , 50 , 20);
 
 if(First_Push_Button_Data == 1){
   ColorValueOne = color(125 , 218 , 88); //circle color will we green 
 }
 else{
   ColorValueOne = color(210 , 1 , 3); //circle color is red 
 }
 
 //define the second circle / second pushbutton 
 fill(ColorValueTwo);
 circle(860 , 75 , 20);
 if(Second_Push_Button_Data == 1){
   ColorValueTwo = color(125 , 218 , 88); //circle color will we green 
 }
 else{
   ColorValueTwo = color(210 , 1 , 3); //circle color is red 
 }
 
 
 //define the   third circle / third  pushbutton 
 fill(ColorValueThree);
 circle(860 , 100 , 20);
 if(Third_Push_Button_Data == 1){
   ColorValueThree = color(125 , 218 , 88); //circle color will we green 
 }
 else{
   ColorValueThree = color(210 , 1 , 3); //circle color is red 
 }
 
 
 //define the fourth circle / fourth pushbutton 
 fill(ColorValueFour);
 circle(860 , 125 , 20);
 if(Fourth_Push_Button_Data == 1){
   ColorValueFour = color(125 , 218 , 88); //circle color will we green 
 }
 else{
   ColorValueFour = color(210 , 1 , 3); //circle color is red 
 }
 
 
 
 
}




void Potentiometer_Value(){
  //define the potentiometer  on the screen 
  fill(14, 9, 145);
  rect(10 , 150 , 200 , 100 ,5 );
  
  fill(255);
  textSize(18);
  text("Pot_One :-" + First_Pot_Data + " Values" , 20 , 210);
  text("Pot_Two :-" + Second_Pot_Data + " Values" , 20 , 240);
  
  fill(255 , 222 , 89);
  rect(13 , 153 , 194 , 30 , 5);
  fill(0);
  textSize(20);
  text("POT_VALUES" , 50 , 175);
}


void Joystick_Data_Value_One(){
  //define the first joystick value 
  
  fill(14, 9, 145);
  rect(200 , 35 , 200 , 100 ,5);
  
  fill(255);
  textSize(18);
  text("Throttle :- " + First_Joystick_Data_X + " Values", 210 , 90);
  text("Steering :- " + First_Joystick_Data_Y + " Values", 210 , 120);
  
  fill(255 , 222 , 89);
  rect(203 , 38 , 194 , 30 , 5);
  fill(0);
  textSize(20);
  text("CONTROL_BOX_ONE" , 213 , 60);
  
}

void Joystick_Data_Value_Two(){
  //define the second joystick value 
  fill(14, 9, 145);
  rect(410 , 35 , 200 , 100 ,5);
  
  fill(255);
  textSize(18);
  
  text("Throttle :- " + Second_Joystick_Data_X + " Values", 420 , 90);
  text("Steering :-" + Second_Joystick_Data_Y + " Values", 420 , 120);
  
  fill(255 , 222 , 89);
  rect(413 , 38 , 194 , 30 , 5);
  fill(0);
  textSize(20);
  text("CONTROL_BOX_TWO" , 420 , 60);
  
  
}



void Display_Seprate(){
  //draw a line for seprate the display
  //one for car and another for remote 
  stroke(255);
  line(900, 0 , 900 , 1000);  //x1 = 900px ,  y1 = 0 , x2 = 900px , y2 = 1000px 
}

void Display_For_Transmitter(){
  fill(255);
  textSize(20);
  text("TRANSMITTER" , 10 , 20);
  //Higlight the transmitter 
  stroke(255);
  line(10 , 25 , 140 , 25);
}

void Display_For_Receiver(){
  fill(255);
  textSize(20);
  text("SMART CAR " , 910 , 20);
  //Highlight the receiver 
  stroke(255);
  line(910 , 25 , 1010 , 25);
}

void Roll_Pitch_Yaw_Value_One(){
  background(0); //background color is black
  //display the roll and pitch  and yaw degree  b
  fill(14, 9, 145);
  rect(10 , 35 , 180 , 100 ,5);

  fill(255); //background color is white 
  textSize(18);
  text("Roll :-  " + Roll_One  + "  Degree ", 20, 60);
  text("Pitch  :- " + Pitch_One + "  Degree ", 20, 90);
  text("Yaw   :-   " + Yaw_One   + "  Degree ", 20 , 120);
}