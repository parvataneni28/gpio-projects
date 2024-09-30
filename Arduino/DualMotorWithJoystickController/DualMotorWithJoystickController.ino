int in1 = 13;  // IN1 connected to digital pin 13
int in2 = 12;  // IN2 connected to digital pin 12
int in3 = 11;  // IN3 connected to digital pin 11
int in4 = 10;  // IN4 connected to digital pin 10

int joyX = A0; // Joystick X-axis
int joyY = A1; // Joystick Y-axis

int xValue;
int yValue;

void setup() {
  Serial.begin(9600);

  // Set IN pins as OUTPUT
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);  
  pinMode(in3, OUTPUT);  
  pinMode(in4, OUTPUT);  

  // Initialize motor off
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void loop() {
  xValue = analogRead(joyX);  // Read X-axis value
  yValue = analogRead(joyY);  // Read Y-axis value

  // Print joystick values for debugging
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print("\tY: ");
  Serial.println(yValue);

  // Control motor based on both X and Y-axis
  if (yValue > 600) {
    // Move motor forward
    digitalWrite(in1, LOW);  // Set motor direction forward
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    Serial.println("Moving Forward");
  }
  else if (yValue < 400) {
    // Move motor backward
    digitalWrite(in1, HIGH);  
    digitalWrite(in2, LOW);   // Reverse motor direction
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    Serial.println("Moving Backward");
  }
  else if (xValue > 600) {
    // Move motor right
    digitalWrite(in1, LOW);  // Right side wheels move forward
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);  // Left side wheels stop or move backward
    digitalWrite(in4, LOW);
    Serial.println("Moving Right");
  }
  else if (xValue < 400) {
    // Move motor left
    digitalWrite(in1, HIGH);  // Right side wheels stop or move backward
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);   // Left side wheels move forward
    digitalWrite(in4, HIGH);
    Serial.println("Moving Left");
  }
  else {
    // Stop the motor
    digitalWrite(in1, HIGH);  
    digitalWrite(in2, HIGH);  
    digitalWrite(in3, HIGH);  
    digitalWrite(in4, HIGH);
    Serial.println("Motor Stopped");
  }

  delay(100);  // Small delay for stability
}
