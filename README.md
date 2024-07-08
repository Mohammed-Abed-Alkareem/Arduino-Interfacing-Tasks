# Arduino-Interfacing-

# Task 1: Distance Measurement System with Arduino and Ultrasonic Sensors

## Overview

This project uses an Arduino, an ultrasonic sensor, and LEDs to measure distance. The closer an object is to the sensor, the more LEDs light up.

## Components

- Arduino
- HC-SR04 Ultrasonic Sensor
- 3 LEDs
- Jumper wires



## Circuit Diagram

Connect the components as shown in the circuit diagram:

<div align="center">
      <img src="/Task_1/Task_1.png" alt="Task 1 Circuit Diagram" width="500">
    </div>

## Code

Upload the code to your Arduino:


You can find the full code [here](./Task_1/sketch_apr29a/sketch_apr29a.ino).




## Functionality

1. **Measure Distance:**
   - The ultrasonic sensor measures the distance to an object.
   - The distance is calculated based on the time it takes for an ultrasonic pulse to travel to the object and back.

2. **LED Indicators:**
   - If the distance is less than 10 cm, all three LEDs light up.
   - If the distance is between 10 cm and 20 cm, two LEDs light up.
   - If the distance is between 20 cm and 30 cm, one LED lights up.
   - If the distance is 30 cm or more, the LEDs blink.

<div align="center">
      <img src="/Task_1/Task_1.gif" alt="Task 1 Circuit Diagram" width="300">
    </div>
    
# Task 2: Distance Measurement and Motion Detection System with Arduino

## Overview

This Task uses an Arduino, an ultrasonic sensor, an IR sensor, an LCD display, and LEDs to measure distance, detect motion, and respond to a button press. The system displays distance measurements on an LCD and detects object motion using an IR sensor. It also includes a push button to toggle an LED.

## Components

- Arduino
- HC-SR04 Ultrasonic Sensor
- Keyestudio KY-032 IR Sensor
- HD44780 LCD
- Push Button
- LED
- Jumper wires
- Breadboard

## Circuit Diagram

Connect the components as shown in the circuit diagram:


<div align="center">
      <img src="/Task_2/Task_2.png" alt="Task 1 Circuit Diagram" width="600">
    </div>

## Code

Upload the code to your Arduino:

You can find the full code [here](./Task_2/sketch_jun13a/sketch_jun13a.ino).

## Functionality

1. **Measure Distance:**
   - The ultrasonic sensor measures the distance to an object.
   - The distance is calculated based on the time it takes for an ultrasonic pulse to travel to the object and return.

2. **LED Indicators:**
   - The push button toggles the LED on and off.
   
3. **Motion Detection:**
   - The IR sensor detects the motion of an object and updates the LCD display.

4. **LCD Display:**
   - Displays the measured distance.
   - Displays "Object Detected" when motion is detected.



# Task: DC Motors with Encoders & Serial Communication

## Overview

This project demonstrates using an encoder with a DC motor controlled by an Arduino, utilizing a joystick for speed and direction. Real-time feedback on motor position, speed, and direction is displayed on an LCD.

## Components

- Arduino
- DC Motor with Encoder
- Joystick (Potentiometer)
- LCD
- Jumper wires

## Circuit Diagram

Connect the components as shown in the circuit diagram:

<div align="center">
      <img src="/Task_3/Task%203_use_I2C.png" alt="Task 1 Circuit Diagram" width="600">
    </div>

## Code

Upload the code to your Arduino:

You can find the full code [here](./Task_3/sketch_jun13a/sketch_jun13a.ino).

## Functionality

1. **Control DC Motor:**
   - The motor speed and direction are controlled using a joystick.
   - The motor’s speed and direction are displayed on the LCD.

2. **Serial Communication:**
   - The motor can be controlled using serial commands.
   - Commands include starting/stopping the motor, setting speed, and setting direction.

## Commands

- **START:** Start the motor.
- **STOP:** Stop the motor.
- **SET_MODE 2:** Switch to mode 2 (control via serial commands).
- **SET_SPEED [value]:** Set the motor speed (0-255).
- **SET_DIR [CW/CCW]:** Set the motor direction (Clockwise/Counter-Clockwise).


