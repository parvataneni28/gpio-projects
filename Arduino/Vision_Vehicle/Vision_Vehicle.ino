#include <Servo.h>

// Motor control pins for two motors
const int input1 = 7;   // Motor 1 (right) forward
const int input2 = 10;  // Motor 1 (right) backward
const int input3 = 6;   // Motor 2 (left) forward
const int input4 = 5;   // Motor 2 (left) backward

Servo servo1;
int servoPin = 3;
int servoPos = 0;
int servoTargetPos = 179;  // Start by moving to 179°
int servoTimer = 10;       // Reduced timer for faster servo movement
unsigned long servoMillis;
unsigned long currentMillis;

// Ultrasonic sensor pins
const int trigPin = 8;     // Trig pin connected to digital pin 8
const int echoPin = 9;     // Echo pin connected to digital pin 9

long duration;
int distance;
int distanceThreshold = 30;  // Minimum distance to detect an obstacle (in cm)

// Movement flags and speed
boolean goesForward = false;

// Function prototypes
int getDistance();
void moveForward();
void moveBackward();
void stopVehicle();
void turnLeft();
void turnRight();
int lookRight();
int lookLeft();

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Servo and Obstacle Detection");

  // Attach the servo to pin 3
  servo1.attach(servoPin);

  // Set trigPin as OUTPUT and echoPin as INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set motor control pins as OUTPUT
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);

  delay(2000);  // Let everything initialize

  // Start by moving the vehicle forward
  moveForward();
}

void loop() {
  int distanceR = 0;
  int distanceL = 0;

  // Get the current time
  currentMillis = millis();

  // Measure the distance using the ultrasonic sensor
  distance = getDistance();

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the obstacle is within range
  if (distance <= distanceThreshold) {
    Serial.println("Obstacle detected. Stopping and scanning...");

    // Stop the vehicle when obstacle is detected
    stopVehicle();
    delay(1000);

    // Move backward slightly to avoid the obstacle
    moveBackward();
    delay(1500);
    stopVehicle();
    delay(1000);

    // Look right and left using the servo to find the direction with more space
    distanceR = lookRight();
    delay(500);
    distanceL = lookLeft();
    delay(500);

    // Decide which direction to turn based on the distances
    if (distanceR > distanceL) {
      Serial.println("More space on the right. Turning right...");
      turnRight();
    } else if (distanceL > distanceR) {
      Serial.println("More space on the left. Turning left...");
      turnLeft();
    } else {
      Serial.println("Equal space on both sides. Defaulting to right turn...");
      turnRight();  // Default to turning right in case of equal distances
    }

    // After turning, move forward in the new direction
    moveForward();
  } else {
    // No obstacle, keep moving forward
    moveForward();
  }

  delay(500);  // Small delay for stability
}

// Look to the right
int lookRight() {
  servo1.write(50);  // Turn servo to the right
  delay(500);        // Wait for the servo to settle
  int distance = getDistance();
  delay(100);
  servo1.write(115);  // Reset servo to center
  return distance;
}

// Look to the left
int lookLeft() {
  servo1.write(170);  // Turn servo to the left
  delay(500);         // Wait for the servo to settle
  int distance = getDistance();
  delay(100);
  servo1.write(115);  // Reset servo to center
  return distance;
}

// Function to measure distance using the HC-SR04
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Move the vehicle forward (both motors forward)
void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(input1, LOW);  // Right motor forward
    digitalWrite(input2, HIGH);  // Right motor stop backward
    digitalWrite(input3, LOW);  // Left motor forward
    digitalWrite(input4, HIGH);  // Left motor stop backward
  }
  Serial.println("Moving Forward");
}

// Move the vehicle backward (both motors backward)
void moveBackward() {
  goesForward = false;
  digitalWrite(input1, HIGH);  // Right motor backward
  digitalWrite(input2, LOW);   // Right motor stop forward
  digitalWrite(input3, HIGH);  // Left motor backward
  digitalWrite(input4, LOW);   // Left motor stop forward
  Serial.println("Moving Backward");
}

// Stop the vehicle (stop both motors)
void stopVehicle() {
  digitalWrite(input1, HIGH);
  digitalWrite(input2, HIGH);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, HIGH);
  Serial.println("Stopping Vehicle");
}

// Turn the vehicle left (right motor forward, left motor backward)
void turnLeft() {
  digitalWrite(input1, LOW);  // Right motor forward
  digitalWrite(input2, HIGH); // Right motor stop backward
  digitalWrite(input3, HIGH); // Left motor backward
  digitalWrite(input4, LOW);  // Left motor stop forward
  delay(500);  // Turn for 500ms
  Serial.println("Turning Left");
}

// Turn the vehicle right (left motor forward, right motor backward)
void turnRight() {
  digitalWrite(input1, HIGH); // Right motor backward
  digitalWrite(input2, LOW);  // Right motor stop forward
  digitalWrite(input3, LOW);  // Left motor forward
  digitalWrite(input4, HIGH); // Left motor stop backward
  delay(500);  // Turn for 500ms
  Serial.println("Turning Right");
}
