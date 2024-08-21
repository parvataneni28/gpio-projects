
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 or 0x3F depending on your I2C module and the size of the LCD (16x2 in this case)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
}

void loop() {
  // Print static text on the first row
  lcd.setCursor(4, 0);   // Set cursor to the first row, fifth column
  lcd.print("Welcome");  // Print static text on the first row

  // Prepare long text for the second row
  String scrollingText = "Welcome to my world people !!!!!!";

  // Loop through the scrolling text
  for (int i = 0; i < scrollingText.length() - 16; i++) {
    // Print a part of the text that fits the display
    lcd.setCursor(0, 1);  // Set cursor to the start of the second row
    lcd.print(scrollingText.substring(i, i + 16));  // Display only 16 characters at a time

    delay(250);  // Adjust the delay for scrolling speed

    // Reprint the first row to keep it static
    lcd.setCursor(4, 0);   // Set cursor to the first row, fifth column
    lcd.print("Welcome");  // Print static text on the first row
  }

  delay(1000);  // Delay before restarting the loop
}
