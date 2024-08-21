/* Lesson 5
   24/05/2024
   
    Using digital pins as Inputs
    pinmode()
    digitalRead()
    debouncing buttons

  Pins Used

  A0 Potentiometer

  2 Right Button
  3 Left button

  5 Right Blue LED
  6 Right Red LED
  7 Right Yellow LED
  8 Right Green LED
  9 Left Blue LED
  10 Left Red LED
  11 Left Yellow LED
  12 Left Green LED


*/

int rightBlueLED = 8;
byte rightBlueLEDState;
int leftYellowLED = 9;
byte yellowLEDState;

int leftButton = 3;
int rightButton = 2;

unsigned long currentMillis;  //stores the board time in milliseconds
unsigned long buttonMillis;
int buttonDebounceTime = 350;  //350 milliseconds

int potPin = A0;


void setup() {
  Serial.begin(9600);
  Serial.println("Lesson 5");
  pinMode(rightBlueLED, OUTPUT);
  pinMode(leftYellowLED, OUTPUT);
}


void loop() {
  int potOutput;
  int outputVolts;


  potOutput = analogRead(potPin);

  outputVolts = map(potOutput, 0 , 1023, 0, 5);
  
  Serial.print(potOutput);
  Serial.print(":");
  Serial.println(outputVolts);
 
   switch (outputVolts) {//compares the value of outputVolts)
    case 1:             //Is it equal to 1
      digitalWrite(rightBlueLED, HIGH);
      digitalWrite(leftYellowLED, LOW);
      break;
    case 2:           //is it equal to 2
      digitalWrite(leftYellowLED, HIGH);
      digitalWrite(rightBlueLED, LOW);
      break;
    default:
      digitalWrite(rightBlueLED, LOW);
      digitalWrite(leftYellowLED, LOW);
      break;
  }
}


