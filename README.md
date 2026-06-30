# smart-parking-system
this project is the demonstration of a smart parking system using iot
# IoT-Enabled Smart Parking Node

This project features an ESP32-based smart parking system designed to monitor vehicle presence in parking bays with high accuracy, even in fluctuating outdoor temperatures.

## 🚀 Overview
The system uses an **HC-SR04 ultrasonic sensor** to detect vehicle proximity and an **NTC thermistor** to perform atmospheric compensation, ensuring the distance measurements remain reliable despite changes in air temperature.

## 🛠️ Key Features
* **Atmospheric Compensation:** Dynamically adjusts the speed of sound calculations based on ambient temperature.
* **Real-time Alerts:** Uses a Red LED and Piezo buzzer to warn drivers when they are within 30 cm of a structural boundary.
* **Status Indication:** A Green LED provides visual feedback for vacant parking slots.
* **IoT Connectivity:** Integrated Wi-Fi capability allows the node to stream telemetry data for municipal management and automated gating systems.

## 📋 Component Inventory
| Component | Function |
| :--- | :--- |
| **ESP32 DevKit C V4** | Central microcontroller with Wi-Fi |
| **HC-SR04** | Ultrasonic sensor for proximity gauging |
| **NTC Thermistor** | Ambient temperature sensor for compensation |
| **LEDs (Red/Green)** | Visual status indicators |
| **Piezo Buzzer** | Acoustic proximity alert |

## ⚙️ How It Works
1. **Telemetry Processing:** The ESP32 reads the NTC thermistor to calculate the current speed of sound.
2. **Sensor Ping:** The HC-SR04 emits an ultrasonic pulse; the system measures the time-of-flight and adjusts the result using the calibrated sound speed.
3. **State Machine:**
    * **Distance > 30 cm:** Vacant (Green LED ON).
    * **Distance < 30 cm:** Occupied/Alert (Red LED and Buzzer ON).
4. **Data Transmission:** Telemetry logs are sent via Serial and Wi-Fi for monitoring and diagnostics.

## ⚡ Deployment
Upload the provided firmware to an **ESP32 DevKit C** using the Wokwi simulation environment or the Arduino IDE with the Wi-Fi framework enabled. Ensure all GPIO pins are mapped as specified in the blueprint.
