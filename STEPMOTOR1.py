import gpiod
import time

# Define the GPIO chip and the GPIO pins connected to the stepper motor
chip = gpiod.Chip('gpiochip0')  # Use gpiochip0, adjust if needed

# Define the GPIO lines (adjust based on your wiring)
pins = [14, 15, 18, 23]  # Example GPIO pins connected to IN1, IN2, IN3, IN4

# Request access to GPIO lines
lines = chip.get_lines(pins)
lines.request(consumer='stepper', type=gpiod.LINE_REQ_DIR_OUT)

# Define the sequence for the 28BYJ-48 stepper motor
step_sequence = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1],
]

def set_pins(sequence):
    values = [int(x) for x in sequence]
    lines.set_values(values)

def rotate_stepper(steps, delay):
    for _ in range(steps):
        for step in step_sequence:
            set_pins(step)
            time.sleep(delay)

# Example usage: rotate the motor 512 steps (one revolution for 28BYJ-48), with a delay of 0.01s
try:
    rotate_stepper(512, 0.01)
finally:
    # Turn off all pins after the movement
    set_pins([0, 0, 0, 0])
    print("Stepper motor movement completed.")