#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // LCD pins

 
const int buttonPin = 2; 
const int irPin = 3; 
const int ledPin = 8;
const int echoPin = 9;    
const int triggerPin = 10;
  

volatile bool ledOn = false; 
volatile unsigned long detectionTime = 0; 
const unsigned long debounceDelay = 50; 
  
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH); 	// Enable pull-down resistor
  pinMode(irPin, INPUT);   
  pinMode(ledPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING); // Attach interrupt on button pin
  attachInterrupt(digitalPinToInterrupt(irPin), IR_ISR, FALLING);
  lcd.begin(16, 2); 
  Serial.begin(9600);
}

void loop() {
  if (millis()-detectionTime>3000){
    lcd.setCursor(0, 1);
  	lcd.print("                ");
  }

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure the duration of the pulse on echoPin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters (you can use inches by changing the conversion factor)
  float distance_cm = duration * 0.034 / 2;

  // Convert the float to a string
  char buffer[10]; // Adjust the buffer size as needed
  dtostrf(distance_cm, 5, 2, buffer); // 5 is the minimum width, 2 is the number of decimal places
  Serial.println(buffer);
  Serial.println(distance_cm);

  // Print the distance to the serial monitor
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("Distance: ");
  lcd.print(buffer);
  // Wait a bit before taking the next measurement
  delay(3000);
  
}
void buttonInterrupt() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // If interrupts come faster than debounceDelay, assume it's a bounce and ignore
  if (interruptTime - lastInterruptTime > debounceDelay) {
    if (ledOn) {
      ledOn = false;
      digitalWrite(ledPin, LOW);
    } else {
      ledOn = true;
      digitalWrite(ledPin, HIGH);
    }
  }
  lastInterruptTime = interruptTime;
}


void IR_ISR() {
  detectionTime = millis();
  lcd.setCursor(0,1); 
  lcd.print("Object Detected"); 
}


