import gpiod
import time

# Define the GPIO pin for the LED (BCM GPIO number)
LED_PIN = 18

# Initialize the GPIO
chip = gpiod.Chip('gpiochip0')  # Adjust to your system, typically 'gpiochip0' on Raspberry Pi
led_line = chip.get_line(LED_PIN)
led_line.request(consumer='LED', type=gpiod.LINE_REQ_DIR_OUT)

try:
    while True:
        # Turn the LED on
        led_line.set_value(1)
        time.sleep(1)  # Wait for 1 second
        
        # Turn the LED off
        led_line.set_value(0)
        time.sleep(1)  # Wait for 1 second

except KeyboardInterrupt:
    # Clean up when the user interrupts the script
    led_line.set_value(0)
    chip.close()
    print("Cleaned up and exiting.")
