#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create an instance of the PWM driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo min/max pulse lengths
#define SERVOMIN 150   // Minimum pulse length (out of 4096) for 0 degrees
#define SERVOMAX 600   // Maximum pulse length (out of 4096) for 90 degrees
#define SERVO_FREQ 50  // Servos run at ~50 Hz

// Step size for smooth movement
int stepSize = 5;

// Gets the pulse width for 50 degrees
int angleToPulse(int angle) {
  return SERVOMIN + (SERVOMAX - SERVOMIN) * angle / 90;
}

// Function to rotate a specified motor between 0 and 90 degrees
void rotateMotor(int motorIndex) {
  static int position = SERVOMIN;  // Start position at 0 degrees
  static bool increasing = true;   // Direction of movement

  // Rotate motor between 0 and 90 degrees
  if (increasing) {
    position += stepSize;
    if (position >= SERVOMAX) {
      position = SERVOMAX;  // Set to maximum position
      increasing = false;   // Reverse direction
    }
  } else {
    position -= stepSize;
    if (position <= SERVOMIN) {
      position = SERVOMIN;  // Set to minimum position
      increasing = true;    // Reverse direction
    }
  }

  // Set the specified motor's position
  pwm.setPWM(motorIndex, 0, position);
}

// function to rotate a specified motor between 30 and 70 degrees
void rotateMotorBetween30And70(int motorIndex) {
  // Calculate pulse lengths for 30 and 70 degrees
  int pulse30 = SERVOMIN + (SERVOMAX - SERVOMIN) * 30 / 90;
  int pulse70 = SERVOMIN + (SERVOMAX - SERVOMIN) * 70 / 90;

  static int position = pulse30;  // Start at 30 degrees
  static bool increasing = true;  // Direction of movement

  // Move motor between 30 and 70 degrees
  if (increasing) {
    position += stepSize;
    if (position >= pulse70) {
      position = pulse70;  // Set to 70 degrees
      increasing = false;  // Reverse direction
    }
  } else {
    position -= stepSize;
    if (position <= pulse30) {
      position = pulse30;  // Set to 30 degrees
      increasing = true;   // Reverse direction
    }
  }

  // Set the specified motor's position
  pwm.setPWM(motorIndex, 0, position);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setting motor 0 to 90 degrees, motor 2 to 90 degrees, motor 3 to 90 degrees, and motor 4 to 45 degrees");

  // Initialize the PWM driver
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // Set oscillator frequency
  pwm.setPWMFreq(SERVO_FREQ);            // Set PWM frequency to 50Hz for servos

  // Set motor 4 to approximately 45 degrees
  int pulse45 = angleToPulse(45);

  int pulse50 = angleToPulse(50);


  delay(10);

  // Set motor 0 to 90 degrees (fixed position)
  pwm.setPWM(0, 0, SERVOMAX);  // Set motor 0 (index 0) to 90 degrees

  // Set motor 2 to 90 degrees (fixed position)
  pwm.setPWM(1, 0, angleToPulse(70));  // Set motor 2 (index 1) to 90 degrees

  // Set motor 3 to 90 degrees (fixed position)
  pwm.setPWM(2, 0, SERVOMAX);  // Set motor 3 (index 2) to 90 degrees

  pwm.setPWM(3, 0, angleToPulse(45));  // Set motor 4 (index 3) to 45 degrees
}

void loop() {
  // Example: Rotate motor 4 between 0 and 90 degrees
  rotateMotorBetween30And70(0);  // Call the function with motor index 3 (motor 4)

  delay(20);  // Small delay for smooth movement
}
