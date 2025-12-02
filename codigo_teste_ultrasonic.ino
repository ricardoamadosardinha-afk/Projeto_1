const int trigPin = 4;
const int echoPin = 5;


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
void setup() {
 Serial.begin (115200);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 digitalWrite(trigPin, LOW);

}

void loop(){
  
    delay(100);
    long dist = measureDistance();
    Serial.println(dist);
   
}