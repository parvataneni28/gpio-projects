/*  lesson11servoV3
    15/06/2024

    Controlling servos with buttons and potentiometer

   

  pins used

  2 servo 1
  3 servo 2
  4 servo 3
  5 servo 4

  8 left button
  9 right button

  A0 potentiometer

*/
#include <Servo.h>  //include the servo library

//Definitions can make reading code much easier, especially when using arrays
//These work like search and replace in a word processor
//Whenever the compiler sees NUMSERVOS it replaces it with it's definition 4
#define NUMSERVOS 1  //change this value to the number of servos you are using

#define SERVO1 0    //create a definition with the name SERVO1 that has a value of 0 (anywhere in code SERVO1)


//Pick a name that is useful in your code...so if building a set of robot arms
// #define LEFTELBOWSERVO 0
// #define LEFTHANDSERVO 1
// #define RIGHTELBOWSERVO 2
// #define RIGHTHANDSERVO 3

Servo myServos[NUMSERVOS];                  //Creates an array of servo objects
int servoPins[NUMSERVOS] = { 8 };  //prefill pin numbers
int servoPos[NUMSERVOS];
int servoTargetPos[NUMSERVOS];
int servoTimer[NUMSERVOS] = { 30 };  //prefill speeds
unsigned long servoMillis[NUMSERVOS];

//set up the pins
const int leftButtonPin = 3;   //button pin
const int rightButtonPin = 2;  //button pin
const int potPin = A0;  //Potentiometer analog pin

//button debounce
unsigned long buttonMillis;
int buttonTimer = 350;

unsigned long currentMillis;



void setup() {
  Serial.begin(9600);
  Serial.println("lesson11servoV3");

  int q;
  for (q = 0; q < NUMSERVOS; q++) {    // work through the array of servo objects
    myServos[q].attach(servoPins[q]);  //attatch each servo to it's pin

  }

  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
}

void loop() {

  int buttonState;
  int potReading;

  currentMillis = millis();  //update currentMillis

  servoMovementControl();//call function that controls servo movement 

  if(currentMillis - buttonMillis >= buttonTimer){

    //button 1 controls servo 1, changes direction at each press
    //digitalRead covered in Lesson 5
    // buttonState = digitalRead(leftButtonPin);
    // if(buttonState > 0){//if button pressed
    //   buttonMillis = currentMillis;//set the debounce timer to prevent multipl presses
    //   if(servoTargetPos[SERVO1] > 0){
    //     servoTargetPos[SERVO1] = 0; //set a target of 0
    //     servoTimer[SERVO1] = 0; //move servo as fast as possible
    //   }else{
    //     servoTargetPos[SERVO1] = 179; //set a target of 179
    //     servoTimer[SERVO1] = 50; //move servo slowly
    //   }
    // }
    //end of button 1


    //button 2 controls servo 2 & 3, changes direction at each press
    //Servos move in opposite direction
    // buttonState = digitalRead(rightButtonPin);
    // if(buttonState > 0){//if button pressed
    //   buttonMillis = currentMillis;//set the debounce timer to prevent multipl presses
    //   if(servoTargetPos[SERVO2] > 0){
    //     servoTargetPos[SERVO2] = 0; //set a target of 0
    //     servoTimer[SERVO2] = 30; //move servo as fast as possible
    //     servoTargetPos[SERVO3] = 179; //set a target of 179
    //     servoTimer[SERVO3] = 30; //move servo as fast as possible
    //   }else{
    //     servoTargetPos[SERVO2] = 179; //set a target of 179
    //     servoTimer[SERVO2] = 30; //move servo slowly
    //     servoTargetPos[SERVO3] = 0; //set a target of 0
    //     servoTimer[SERVO3] = 30; //move servo as fast as possible
    //   }
    // }
    //end of button 2
    

  }
  //potentiometer moving servo 4
  // //analogread was covered in Lesson 6
  potReading = analogRead(potPin);//this gives a value between 0 - 1023
  // //Serial.println(potReading);
  // //Map was covered in lesson 6
  potReading = map(potReading, 0, 1023, 0, 179); //remap that value to one between 0 - 179
  //Serial.println(potReading);
    servoTargetPos[SERVO1] = potReading;// if the servo hasn't reached old target it will instantly start moving to new target
  
  

}

//This function is called in the main loop and will move any servo 1 step as required.
void servoMovementControl(){
  int q;
  //This bit of code will control all servo movement
  for (q = 0; q < NUMSERVOS; q++) {//work through all the servos in the array
    //This line is compared 1st is it's fast being 2 ints
    //This is changed because in a normal project the servos are not constantly moving
    if (servoPos[q] != servoTargetPos[q]) {                   //does the servo still need to move
      //this line is slightly slower to compare as it's 2 unsigned longs
      if (currentMillis - servoMillis[q] >= servoTimer[q]) {  //if it does is it time to move
        servoMillis[q] = currentMillis;                       //update the timer for this servo
        if (servoPos[q] < servoTargetPos[q]) {                //if it's smaller
          servoPos[q]++;                                      //move one step closer
        } else {                                              //else it's larger
          servoPos[q]--;                                      //move one step closer in other direction
        }
        myServos[q].write(servoPos[q]);  //move this servo to it's new position
      }
    }
  }
}
