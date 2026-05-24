 # Servo Radar Scanner

## Overview
This project is an Arduino-based radar scanning system that uses an ultrasonic sensor mounted to a servo motor to scan the surrounding environment. The system detects nearby objects and displays the object angle and distance on a 16x2 LCD display.

## Features
- Real-time object scanning
- Servo motor sweep system
- Ultrasonic distance measurement
- LCD angle and distance display
- Serial monitor integration
- Resettable scanning system

## Components Used
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- LCD1602 Display
- Potentiometer
- Breadboard
- Jumper Wires

## Technologies Used
- Arduino C++
- Embedded Systems
- Sensor Integration
- Servo Motor Control
- Real-Time Monitoring

## How It Works
The ultrasonic sensor is mounted onto a servo motor that sweeps across a defined angular range. During the sweep, the system continuously measures object distance using ultrasonic pulses. When an object is detected within the specified detection range, the servo stops and the object angle and distance are displayed on the LCD.

## Future Improvements
- ESP32 WiFi dashboard integration
- OLED radar graphics
- Multiple object tracking
- Mobile application support
- Data logging and analytics

## Images
Project images are stored in the images folder.

## Wiring Diagram
Wiring diagrams are stored in the wiring-diagram folder.
