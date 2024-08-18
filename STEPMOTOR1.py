import lgpio
import time

# Define the GPIO pins (using Broadcom numbering, e.g., GPIO4 for physical pin 7)
control_pins = [4, 17, 27, 22]  # Pins 7, 11, 13, 15 in BCM numbering

# Initialize the GPIO chip and set pins as outputs
h = lgpio.gpiochip_open(0)

for pin in control_pins:
    lgpio.gpio_claim_output(h, pin)

# Define a sequence for a stepper motor half-step sequence
halfstep_seq = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1]
]

# Rotate the motor
for i in range(512):  # 512 steps for a full revolution
    for halfstep in range(8):
        for pin in range(4):
            lgpio.gpio_write(h, control_pins[pin], halfstep_seq[halfstep][pin])
        time.sleep(0.001)

# Clean up by setting pins to low and closing the GPIO chip
for pin in control_pins:
    lgpio.gpio_write(h, pin, 0)

lgpio.gpiochip_close(h)
