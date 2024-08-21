#include <Servo.h>

Servo servo1;
int servoPin = 8;
int servoPos;
int servoTargetPos;
int servoTimer = 60;
unsigned long servoMillis;

unsigned currentMillis;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println('Servo Test');

  servo1.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  if (currentMillis - servoMillis >= servoTimer) {
    servoMillis = currentMillis;

    if (servoPos != servoTargetPos) {
      if (servoPos < servoTargetPos) {
        servoPos++;
      } else {
        servoPos--;
      }
      Serial.print('Servo1 Pos :');
      Serial.println(servoPos);
      servo1.write(servoPos);
    }

    if (servoPos == servoTargetPos) {
      if (servoPos < 179) {
        servoTargetPos = 179;
      } else {
        servoTargetPos = 0;
      }
    }
  }
  }
