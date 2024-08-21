#define NUMSTEPPERS 1

#define LEFTSTEPPER 0 

int stepperArrayPos[NUMSTEPPERS];

int stepperPins[NUMSTEPPERS][4] = {
  { 4, 5, 6, 7 }   //stepper pins
};

//timing for steppers needs to be in microseconds as steps are very fast
unsigned long currentMicros;
unsigned long stepperMicros[NUMSTEPPERS];
int stepperSpeed[NUMSTEPPERS] = { 25000 };

int stepPos[NUMSTEPPERS];
int stepTarget[NUMSTEPPERS];


const int leftButtonPin = 2;
const int redLedPin = 12;

unsigned long currentMillis;
unsigned long ledMillis;
int ledTimer = 1000;  //led will change state every 1000 millis...1 second
byte ledState;        //stores the ledState

unsigned long buttonMillis;  //debounce timer
int buttonTimer = 350;       //debounce time


void setup() {
  // put your setup code here, to run once:
int q;  //extra variable required
  int w;
  Serial.begin(9600);
  Serial.println("stepperV5");

  pinMode(leftButtonPin, INPUT);

  pinMode(redLedPin, OUTPUT);

  //work through the 2 dimensional array of pins
  for (w = 0; w < NUMSTEPPERS; w++) {  //work through the stepper motors
    for (q = 0; q < 4; q++) {          //now set pin modes for each stepper
      pinMode(stepperPins[w][q], OUTPUT);
    }
  }

  // for(q=0;q<4;q++){
  //   pinMode(leftStepperPins[q], OUTPUT);
  //   pinMode(rightStepperPins[q], OUTPUT);
  // }
}

void loop() {
  // put your main code here, to run repeatedly:
int leftButton;   //button state
  int q;
  int w;  //new variable to count thrugh steppers
  //stepper code
  //this example will just move the left stepper 1000 steps in each direction.
  currentMicros = micros();  //same as usuakl currentMillis but using microseconds

  for (w = 0; w < NUMSTEPPERS; w++) {//work through each stepper to check if it needs to move
    if (stepPos[w] != stepTarget[w]) {                            //does the left stepper still need to move to reach target postion
      if (currentMicros - stepperMicros[w] >= stepperSpeed[w]) {  //if yes is it time for next step
        stepperMicros[w] = currentMicros;                          //rest the timer for the next step

        if (stepPos[w] < stepTarget[w]) {
          stepPos[w]++;                  // increase value as another step closer
                                          //move to next position in the array
          if (stepperArrayPos[w] > 2) {  //once value gets greater than 2 next step to the start position again
            stepperArrayPos[w] = 0;
          } else {
            stepperArrayPos[w]++;
          }
        } else {          //if it's not greater must be smaller
          stepPos[w]--;  // increase value as another step closer
          //move to next position in the array
          if (stepperArrayPos[w] < 1) {  //once value gets below 1 nbext step move back to other end of array
            stepperArrayPos[w] = 3;
          } else {
            stepperArrayPos[w]--;
          }
        }
        //now do the actual movement
        digitalWrite(stepperPins[w][stepperArrayPos[w]], HIGH);
        for (q = 0; q < 4; q++) {
          if (q != stepperArrayPos[w]) {
            digitalWrite(stepperPins[w][q], LOW);
          }
        }
      }
    }
  }


  //code below here has been used in previous lessons and is just to demonstrate that code is non blocking as
  //buttons and led flash continues to run while stepper moves

  //code that just flashes the LED without using delay();
  currentMillis = millis();
  if (currentMillis - ledMillis >= ledTimer) {  //usual millis based timer code
    ledMillis = currentMillis;
    if (ledState > 0) {
      ledState = 0;
    } else {
      ledState = 1;
    }
    digitalWrite(redLedPin, ledState);
  }

  if (currentMillis - buttonMillis >= buttonTimer) {
    //check the buttons states and serial print
    leftButton = digitalRead(leftButtonPin);
    if (leftButton > 0) {
      Serial.println("Left Button Targets set");
      stepTarget[LEFTSTEPPER] = 1000;       //definitions make it easy to understand which stepper is being referenced
      buttonMillis = currentMillis;
    }

  }
}
