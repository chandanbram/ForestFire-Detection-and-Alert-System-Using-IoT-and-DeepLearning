#include <Servo.h>

#define SERVO_PIN D1 // Define the pin for servo motor

Servo servoMotor; // Create a servo object

void setup() {
  servoMotor.attach(SERVO_PIN); // Attach the servo to the pin
}

void loop() {
  for (int angle = 0; angle <= 230; angle++) { // Rotate from 0 to 115 degrees
    servoMotor.write(angle/2); // Set the servo position
    delay(45); // Adjust this delay to control the speed of rotation
  }
  
  delay(1000); // Wait for 1 second
  
  for (int angle = 230; angle >= 0; angle--) { // Rotate from 115 to 0 degrees
    servoMotor.write(angle/2); // Set the servo position
    delay(45); // Adjust this delay to control the speed of rotation
  }
  
  delay(1000); // Wait for 1 second
}
