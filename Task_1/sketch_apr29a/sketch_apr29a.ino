const int trigPin = 7; 
const int echoPin = 6; 
const int led1Pin = 8; 
const int led2Pin = 10; 
const int led3Pin = 12; 

unsigned long previousMillis = 0;
const long interval = 500; 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < 10) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
  } else if (distance >= 10 && distance < 20) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, LOW);
  } else if (distance >= 20 && distance < 30) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
  } else {
    
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (digitalRead(led1Pin) == HIGH) {
    	digitalWrite(led1Pin, LOW);
    	digitalWrite(led2Pin, LOW);
        digitalWrite(led3Pin, LOW);
      }
      else{
        digitalWrite(led1Pin, HIGH);
    	digitalWrite(led2Pin, HIGH);
    	digitalWrite(led3Pin, HIGH);
      }
    }
    
  }
   
}
