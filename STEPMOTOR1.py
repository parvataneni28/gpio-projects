from gpiozero import OutputDevice
import time

# Define the GPIO pins connected to IN1, IN2, IN3, IN4
IN1 = OutputDevice(17)
IN2 = OutputDevice(18)
IN3 = OutputDevice(27)
IN4 = OutputDevice(22)

# Step sequence for half-stepping
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

# Function to set the GPIO pins according to the step sequence
def set_step(w1, w2, w3, w4):
    IN1.value = w1
    IN2.value = w2
    IN3.value = w3
    IN4.value = w4

# Function to rotate stepper motor by specified steps
def rotate_motor(steps, direction=1, delay=0.001):
    for _ in range(steps):
        for step in (step_sequence if direction == 1 else reversed(step_sequence)):
            set_step(*step)
            time.sleep(delay)

try:
    while True:
        print("Rotating Forward")
        rotate_motor(512, direction=1)  # One full rotation forward
        time.sleep(1)

        print("Rotating Backward")
        rotate_motor(512, direction=-1)  # One full rotation backward
        time.sleep(1)

except KeyboardInterrupt:
    print("Motor stopped.")
