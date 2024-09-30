int in1 = 13;  // IN1 connected to digital pin 13
int in2 = 12;  // IN2 connected to digital pin 12
int in3 = 11;  // IN3 connected to digital pin 11
int in4 = 10;  // IN4 connected to digital pin 10

void setup() {
  // put your setup code here, to run once:


  pinMode(in1, OUTPUT);  // Set IN1 as OUPUT
  pinMode(in2, OUTPUT);  // Set IN2 as OUPUT
  pinMode(in3, OUTPUT);  // Set IN3 as OUPUT
  pinMode(in4, OUTPUT);  // Set IN4 as OUPUT

  // disable motor output by setting all INx pins high
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void loop() {
  // // Rotate motor forward for 3 seconds
  // digitalWrite(in1, LOW);  // Turn on motor in direction 1
  // digitalWrite(in2, HIGH);
  // digitalWrite(in3, LOW);  
  // digitalWrite(in4, HIGH);
  // delay(3000);  // Run motor for 3 seconds
  
  // // Stop motor for a moment before reversing
  // digitalWrite(in1, HIGH);  // Turn off motor
  // digitalWrite(in2, HIGH);
  // digitalWrite(in3, HIGH);
  // digitalWrite(in4, HIGH);
  // delay(500);  // Short delay to avoid abrupt change

  // // Reverse motor for 3 seconds
  // digitalWrite(in1, HIGH);  
  // digitalWrite(in2, LOW);   // Reverse motor direction
  // digitalWrite(in3, HIGH);  
  // digitalWrite(in4, LOW);
  // delay(3000);  // Run motor in reverse for 3 seconds
  
  // // Stop motor again before the next cycle
  // digitalWrite(in1, HIGH);  
  // digitalWrite(in2, HIGH);
  // digitalWrite(in3, HIGH);
  // digitalWrite(in4, HIGH);
  // delay(500);  // Short delay before repeating
}

