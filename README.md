# IoT-Based Low-Cost Multi-Vital Sign Monitoring Device for Rural Telemedicine

![Project](https://img.shields.io/badge/Project-IoT%20Healthcare-blue)
![Controller](https://img.shields.io/badge/Controller-ESP32-green)
![Language](https://img.shields.io/badge/Language-Embedded%20C%2B%2B-orange)
![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-purple)

## 📌 Project Overview

This project presents a low-cost, portable and IoT-based multi-vital sign monitoring device designed to support rural telemedicine.

The system uses biomedical sensors interfaced with an ESP32 microcontroller to monitor important physiological parameters and transmit the collected information to the ThingSpeak cloud platform for remote monitoring.

## 🎯 Objectives

- Develop an affordable health monitoring device.
- Monitor multiple vital health parameters.
- Display readings using an OLED display.
- Transmit health data to the ThingSpeak cloud.
- Support remote patient monitoring in rural areas.

## 🔧 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 Dev Board | Main controller and Wi-Fi |
| MAX30100 | Heart rate and SpO₂ |
| AD8232 | ECG monitoring |
| DS18B20 | Temperature measurement |
| 0.96-inch OLED | Local display |
| 18650 Li-ion Battery | Power supply |
| TP4056 | Battery charging |
| Jumper Wires | Connections |

## 💻 Software Requirements

- Arduino IDE
- Embedded C/C++
- ESP32 Board Package
- MAX30100 Library
- Adafruit GFX Library
- Adafruit SSD1306 Library
- OneWire Library
- DallasTemperature Library
- ThingSpeak IoT Cloud

## ⚙️ Working Principle

1. Biomedical sensors collect physiological signals.
2. ESP32 receives and processes sensor data.
3. The OLED displays the measured parameters.
4. ESP32 connects to Wi-Fi.
5. Data is transmitted to ThingSpeak.
6. Doctors or caregivers can remotely view the uploaded information.

## 📊 Parameters Monitored

- Heart Rate (BPM)
- Blood Oxygen Saturation (SpO₂)
- ECG Signal
- Body Temperature (°C)

## ☁️ IoT Cloud Platform

**ThingSpeak**

The ThingSpeak platform is used to store, visualize and monitor the collected health parameters remotely.

Suggested channel fields:

- Field 1: Heart Rate
- Field 2: SpO₂
- Field 3: Temperature
- Field 4: ECG (if ECG samples are uploaded)

## 📁 Repository Structure

```text
IoT-Based-Low-Cost-Multi-Vital-Sign-Monitoring-Device-for-Rural-Telemedicine/
│
├── README.md
├── LICENSE
├── Code/
│   └── health_monitoring.ino
├── Hardware/
│   ├── Block_Diagram.png
│   └── Circuit_Diagram.png
├── Documentation/
│   └── Project_Report.pdf
├── Cloud/
│   └── ThingSpeak_Setup.md
├── Images/
└── Testing/
    └── Test_Results.md
```

## 💰 Project Cost

**Approximate reported cost: ₹1,600**

## 🌍 Applications

- Rural healthcare centres
- Remote patient monitoring
- Home healthcare
- Telemedicine support
- Primary Health Centres

## 🚀 Future Scope

- Android application integration
- AI-based health data analysis
- SMS and email alerts
- Additional biomedical sensors
- Improved patient data security
- Wearable health monitoring

## 👨‍💻 Project Team

**Department:** Electronics & Telecommunication Engineering

**Institute:** V.V.P. Institute of Engineering & Technology, Solapur

**University:** Dr. Babasaheb Ambedkar Technological University, Lonere

**Academic Year:** 2025–26

**Project Guide:** Prof. G. Bhavani

## ⚠️ Disclaimer

This project is an academic prototype and is not a certified medical diagnostic device. Its readings should not be used as a substitute for professional medical equipment or clinical advice.

## 📜 License

This project is licensed under the MIT License.

---

**Developed as an IoT-based healthcare engineering project.**
