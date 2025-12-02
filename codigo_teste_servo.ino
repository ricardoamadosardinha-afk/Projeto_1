#include <ESP32Servo.h> // Requires "ESP32Servo" library by Kevin Harrington

Servo myServo;  // Create a servo object

// PIN DEFINITION
// We use GPIO 5, which is a safe, generic PWM-capable pin on the ESP32-C6.
#define SERVO_PIN 5 

int pos = 0;    // Variable to store the servo position

// USER SETTING: Change this value to control speed
// Low number (e.g., 5) = FAST
// High number (e.g., 50) = SLOW
int stepDelay = 50; 

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  // Standard servos usually operate between 500us and 2400us pulse width
  myServo.setPeriodHertz(50);    // Standard 50hz servo
  myServo.attach(SERVO_PIN, 500, 2400); 
}

void loop() {
  // SWEEP FROM 0 TO 180
  for (pos = 0; pos <= 180; pos += 1) { 
    myServo.write(pos);              
    delay(stepDelay);                
  }
  
  delay(1000); // Wait 1 second

  // SWEEP FROM 180 BACK TO 0
  for (pos = 180; pos >= 0; pos -= 1) { 
    myServo.write(pos);              
    delay(stepDelay);
  }

  delay(1000); // Wait 1 second
}