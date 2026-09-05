# 🚗 Object Avoidance Robot

An autonomous two-wheel-drive robot built with C++ that uses ultrasonic sensors to detect obstacles and navigate around them in real-time. 

## 🛠 Hardware Components
* 1x Microcontroller (e.g., Arduino Uno or ESP32)
* 1x HC-SR04 Ultrasonic Sensor
* 1x L298N Motor Driver
* 2x DC Gear Motors with Wheels
* 1x Robot Chassis
* 1x Battery Pack (e.g., 9V or 2x 18650 Li-ion)
* Jumper Wires

## 🔌 Wiring Guide

Make sure your hardware is wired exactly as shown below before powering on the robot.

| Component | Pin / Terminal | Microcontroller Pin |
| :--- | :--- | :--- |
| **Ultrasonic Sensor** | VCC | 5V (or 3.3V depending on board) |
| | GND | GND |
| | Trig | [Insert Trig Pin, e.g., Pin 9] |
| | Echo | [Insert Echo Pin, e.g., Pin 10] |
| **L298N Motor Driver**| ENA (Left Speed) | [Insert PWM Pin, e.g., Pin 5] |
| | IN1 (Left Forward) | [Insert Pin, e.g., Pin 6] |
| | IN2 (Left Reverse) | [Insert Pin, e.g., Pin 7] |
| | IN3 (Right Forward)| [Insert Pin, e.g., Pin 8] |
| | IN4 (Right Reverse)| [Insert Pin, e.g., Pin 9] |
| | ENB (Right Speed) | [Insert PWM Pin, e.g., Pin 10] |
| | 12V / VCC | Battery Positive (+) |
| | GND | Battery Negative (-) AND Microcontroller GND |

> **⚠️ Important Warning:** Always ensure that the ground (GND) of your motor driver, microcontroller, and battery are all connected together. 

## 💻 Software Setup

This project is built using **PlatformIO**. To run this code on your own robot:

1. Clone this repository:
   ```bash
   git clone [https://github.com/Brian44ki/object--avoidance--robot.git](https://github.com/Brian44ki/object--avoidance--robot.git)
