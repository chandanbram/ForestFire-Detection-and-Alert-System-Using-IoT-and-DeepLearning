#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
char firstLine[] = "   ECO-HARBOR";
char secondLine[] = "AN INTEGRATED APPROACH FOR FOREST FIRE DETECTION, MITIGATION, WILDLIFE RELOCATION, AND TRIBAL ALERT USING DEEP LEARNING AND IOT";
int secondLineLength;
int scrollSpeed = 200; // Adjust scroll speed as needed

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  int leadingSpaces = (16 - strlen(firstLine)) / 2;
  for (int i = 0; i < leadingSpaces; i++) {
    lcd.print(" ");
  }
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  secondLineLength = strlen(secondLine);
}

void loop() {
  for (int i = 0; i < secondLineLength + 16; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(firstLine);
    lcd.setCursor(0, 1);
    for (int j = i; j < i + 16; j++) {
      lcd.print(secondLine[j % secondLineLength]);
    }
    delay(scrollSpeed);
  }
}
