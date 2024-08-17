import RPi.GPIO as GPIO
import time

# GPIO pin setup for ULN2003 inputs
IN1 = 17  # GPIO pin 11
IN2 = 18  # GPIO pin 12
IN3 = 27  # GPIO pin 13
IN4 = 22  # GPIO pin 15

# Time delay between steps
delay = 0.001

# Step sequence for 28BYJ-48 (half-stepping)
step_sequence = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1]
]

# Setup GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)
GPIO.setup(IN3, GPIO.OUT)
GPIO.setup(IN4, GPIO.OUT)

# Function to set the GPIO pins according to the step sequence
def set_step(w1, w2, w3, w4):
    GPIO.output(IN1, w1)
    GPIO.output(IN2, w2)
    GPIO.output(IN3, w3)
    GPIO.output(IN4, w4)

# Function to rotate stepper motor by specified steps
def rotate_motor(steps, direction=1):
    for _ in range(steps):
        for step in (step_sequence if direction == 1 else reversed(step_sequence)):
            set_step(*step)
            time.sleep(delay)

try:
    while True:
        # Rotate 512 steps forward (one full rotation)
        print("Rotating Forward")
        rotate_motor(512, direction=1)
        time.sleep(1)
        
        # Rotate 512 steps backward (one full rotation)
        print("Rotating Backward")
        rotate_motor(512, direction=-1)
        time.sleep(1)

except KeyboardInterrupt:
    print("Motor stop")
    GPIO.cleanup()
