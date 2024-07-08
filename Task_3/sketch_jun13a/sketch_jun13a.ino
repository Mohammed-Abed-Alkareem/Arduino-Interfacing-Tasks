#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//***********************************
//  Qosay Rida - 1211553
//  Mohammed Abed Alkareem - 1210708
//  Ahmad Hamdan - 1210241
//  Mohammad Fareed - 1212387
//***********************************


// Pin definitions
const byte motorPin1 = 6;
const byte motorPin2 = 5;
const byte sensorPin1 = 2;
const byte sensorPin2 = 3;
const byte potPin1 = A0;

const float encoderValue = 6.2;
const int threshold = 512;

// Variables
byte motorDirection1 = 0;
bool motorStatus1 = false;
float targetSpeed1 = 0;
volatile long sensorCount1 = 0;
float rpm1 = 0;
float speedError;
long previousTime1 = 0;
bool motorRunning = true; // Variable to keep track of motor state
byte mode = 1; // 1: MODE1, 2: MODE2

// Function declarations
void sensorInterrupt1();
void calculateRPM();
void readPotentiometers();
void controlMotors();
void updateDisplay();
void handleSerialCommands();
void startMotor();
void stopMotor();
void setDirection(String dir);
void setSpeed(int speed);
void setMode(byte newMode);

void setup() {
  
  	  
  	lcd.init();
  	lcd.backlight();
  
    // Initialize the LCD
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("S=");

    lcd.setCursor(8, 0);
lcd.print("RPM=");

    lcd.setCursor(0, 1);
    lcd.print("CW ");
  	lcd.setCursor(11, 1);
    lcd.print("MODE1");
    
    Serial.begin(9600);
    
    // Configure sensor pins as input
    pinMode(sensorPin1, INPUT_PULLUP);
    pinMode(sensorPin2, INPUT_PULLUP);
  pinMode(potPin1, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
    // Attach interrupts for sensor pins
    attachInterrupt(digitalPinToInterrupt(sensorPin1), sensorInterrupt1, CHANGE);
}

void loop() {
    handleSerialCommands();
    if (motorRunning) {
        calculateRPM();
        if (mode == 1) {
            readPotentiometers();
        }
        controlMotors();
    }
}

void sensorInterrupt1() {
    sensorCount1++;
}

void calculateRPM() {
    unsigned long currentTime1 = millis();
    if ((currentTime1 - previousTime1) >= 100) {
        previousTime1 = currentTime1;

        if (motorDirection1 == 0) {
            rpm1 = sensorCount1 * 10 / encoderValue;
        } else {
            rpm1 = -sensorCount1 * 10 / encoderValue;
        }

    lcd.setCursor(12, 0);
    lcd.print("    ");
    lcd.setCursor(12, 0);
    lcd.print((int)abs(rpm1));
      
        sensorCount1 = 0;
    }
}

void readPotentiometers() {
    int potValue = analogRead(potPin1);

    if (potValue < threshold) {
        motorDirection1 = 1;
        lcd.setCursor(0, 1);
        lcd.print("CCW");
    } else {
        motorDirection1 = 0;
        lcd.setCursor(0, 1);
        lcd.print("CW ");
    }
  
 	if (abs(potValue - 511) < 11) {
    targetSpeed1 = 0;
  	} else if (potValue <= 511) {
    targetSpeed1 = map(potValue, 0, 511, 255, 0);
  } else if (potValue > 511) {
    targetSpeed1 = map(potValue, 512, 1023, 0, 255);
  }

  	
    lcd.setCursor(2, 0);
    lcd.print("    ");
    lcd.setCursor(2, 0);
    lcd.print((int)abs(targetSpeed1));
  
  
}

void controlMotors() {
    if (motorDirection1 == 0) {
        analogWrite(motorPin1, targetSpeed1);
        analogWrite(motorPin2, 0);
    } else {
        analogWrite(motorPin1, 0);
        analogWrite(motorPin2, targetSpeed1);
    }
}

void handleSerialCommands() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim(); // Remove any whitespace characters

        if (command == "START") {
            startMotor();
        } else if (command == "STOP") {
            stopMotor();
        } else if (command.startsWith("SET_DIR")) {
            String dir = command.substring(8);
            setDirection(dir);
        } else if (command.startsWith("SET_SPEED")) {
            int speed = command.substring(10).toInt();
            setSpeed(speed);
        } else if (command.startsWith("SET_MODE")) {
            byte newMode = command.substring(9).toInt();
            setMode(newMode);
        } else {
            Serial.println("Unknown command");
        }
    }
}

void startMotor() {
    motorRunning = true;
    Serial.println("Motor started");
}

void stopMotor() {
    motorRunning = false;
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    Serial.println("Motor stopped");
}

void setDirection(String dir) {
    if (dir == "CW") {
        motorDirection1 = 0;
        lcd.setCursor(0, 1);
        lcd.print("CW ");
        Serial.println("Direction set to CW");
    } else if (dir == "CCW") {
        motorDirection1 = 1;
        lcd.setCursor(0, 1);
        lcd.print("CCW");
        Serial.println("Direction set to CCW");
    } else {
        Serial.println("Invalid direction");
    }
}

void setSpeed(int speed) {
    if (speed >= 0 && speed <= 255) {
        targetSpeed1 = speed;
         lcd.setCursor(2, 0);
        lcd.print("    ");
        lcd.setCursor(2, 0);
       lcd.print((int)abs(targetSpeed1));
        Serial.print("Speed set to ");
        Serial.println(speed);
    } else {
        Serial.println("Invalid speed");
    }
}

void setMode(byte newMode) {
    if (newMode == 1 || newMode == 2) {
        mode = newMode;
        Serial.print("Mode set to ");
        Serial.println(newMode);
        if (mode == 2) {
            lcd.setCursor(11, 1);
            lcd.print("MODE2");
        } else {
            lcd.setCursor(11, 1);
            lcd.print("MODE1");
        }
    } else {
        Serial.println("Invalid mode");
    }
}
