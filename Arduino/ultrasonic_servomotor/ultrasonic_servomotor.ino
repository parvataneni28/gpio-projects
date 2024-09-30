#include <Servo.h>

Servo servo1;
int servoPin = 3;
int servoPos = 0;
int servoTargetPos = 179;  // Start by moving to 179°
int servoTimer = 10;  // Reduced timer for faster servo movement
unsigned long servoMillis;
unsigned long currentMillis;

// Ultrasonic sensor pins
const int trigPin = 8;  // Trig pin connected to digital pin 8
const int echoPin = 9;  // Echo pin connected to digital pin 9

long duration;
int distance;
int distanceThreshold = 30;  // Minimum distance to detect an obstacle (in cm)

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Servo and Obstacle Detection");

  // Attach the servo to pin 3
  servo1.attach(servoPin);

  // Set trigPin as OUTPUT and echoPin as INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Get the current time
  currentMillis = millis();

  // Measure the distance using the ultrasonic sensor
  distance = getDistance();

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Servo rotates fast if obstacle is within range
  if (distance <= distanceThreshold) {
    Serial.println("Obstacle detected within range. Servo rotating...");

    // Move the servo based on the timer
    if (currentMillis - servoMillis >= servoTimer) {
      servoMillis = currentMillis;

      // Move the servo towards the target position
      if (servoPos < servoTargetPos) {
        servoPos += 5;  // Move the servo faster by increasing steps
      } else if (servoPos > servoTargetPos) {
        servoPos -= 5;  // Move the servo back faster
      }

      // Write the new position to the servo
      Serial.print("Servo Position: ");
      Serial.println(servoPos);
      servo1.write(servoPos);

      // If the servo reaches the max or min position, reverse direction
      if (servoPos >= 179) {
        servoTargetPos = 0;  // Reset to move back to 0°
      } else if (servoPos <= 0) {
        servoTargetPos = 179;  // Reset to move to 179°
      }
    }
  } else {
    Serial.println("No obstacle detected within range.");
    // Optionally stop the servo if no obstacle is found
    // servo1.write(servoPos);  // Servo remains in the last position
  }

  delay(50);  // Small delay for stability
}

// Function to measure distance using HC-SR04
int getDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  int distance = duration * 0.034 / 2;

  return distance;
}
