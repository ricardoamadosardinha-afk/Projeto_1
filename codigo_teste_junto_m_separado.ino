const int trigPin = 4;
const int echoPin = 5;
const int ldrPin = 6; 
#define SERVO_PIN 14 

#include <ESP32Servo.h>
Servo myServo;
int pos = 0;
int stepDelay = 50;


long measureDistance() {
 long duration, distance;

 //Send pulse
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 //Wait for echo and measure time until it happens
 duration = pulseIn(echoPin, HIGH);
 //Compute distance
 distance = duration/58;
 return distance;
}

void sensorLDR() {
  int sensorValue = analogRead(ldrPin);
  
  Serial.print("Analog Value: ");
  Serial.println(sensorValue);
  
  // ESP32 ADC is 12-bit (0-4095), so the values are roughly 4x higher 
  // than an Arduino Uno (0-1023).
  
  if (sensorValue < 800) {  
    Serial.println("Status: Bright");
  
  } else {
    Serial.println("Status: Dark");
  }

  Serial.println("---"); 
  delay(500); 
}

void servoMovement() {
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



void setup() {
 Serial.begin (115200);   

 pinMode(trigPin, OUTPUT);        //ultrasonic
 pinMode(echoPin, INPUT);
 digitalWrite(trigPin, LOW);

 analogReadResolution(12);     

 // Allow allocation of all timers      //setup servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  // Standard servos usually operate between 500us and 2400us pulse width
  myServo.setPeriodHertz(50);    // Standard 50hz servo
  myServo.attach(SERVO_PIN, 500, 2400); 

}

void loop(){
    sensorLDR();
    servoMovement();
    long dist = measureDistance();
    Serial.println(dist);
    delay(200);
}