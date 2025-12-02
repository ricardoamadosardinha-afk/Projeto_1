// On ESP32-C6, we use the GPIO number directly.
const int ldrPin = 6;  

void setup() {
  Serial.begin(115200); // ESP32 usually works best at higher baud rates
  
  // Optional: Explicitly set resolution to 12-bit (0-4095)
  // This is the default, but good to be sure.
  analogReadResolution(12);
}

void loop() {
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