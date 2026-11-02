# ThingSpeak Cloud Integration

## 1. Introduction

ThingSpeak is an IoT cloud platform used to collect, store, visualize and analyze sensor data from the ESP32 health monitoring device.

## 2. Channel Configuration

Create a new channel named:

**IoT-Based Multi-Vital Sign Monitoring System**

Enable the following fields:

| Field | Parameter | Unit |
|---|---|---|
| Field 1 | Heart Rate | BPM |
| Field 2 | SpO2 | % |
| Field 3 | Body Temperature | °C |
| Field 4 | ECG ADC Value | ADC |
| Field 5 | ECG Lead Status | 0 / 1 |

## 3. ESP32 Connectivity

The ESP32 connects to the internet using its built-in Wi-Fi module.

The firmware sends sensor measurements to ThingSpeak using HTTP-compatible cloud communication over HTTPS.

## 4. Data Transmission

The system uploads:
- Heart rate
- Oxygen saturation
- Body temperature
- Latest ECG ADC sample
- ECG electrode lead status

The configured firmware upload interval is 20 seconds.

## 5. Dashboard Visualization

Create five ThingSpeak visualizations:

1. Heart Rate Graph
2. SpO2 Graph
3. Body Temperature Graph
4. ECG ADC Value Graph
5. ECG Lead Status Graph

## 6. API Configuration

Obtain the Write API Key from:

ThingSpeak → Channels → API Keys

Configure the key privately in the ESP32 firmware.

Never publish the Write API Key or Wi-Fi password in a public GitHub repository.

## 7. Expected Output

The ThingSpeak dashboard provides graphical representation of uploaded measurements, enabling remote observation of recorded health parameters.

## 8. Important Note

Field 4 in the current firmware represents the latest ECG ADC sample, not a continuous ECG waveform.

The system is an academic prototype and is not intended to replace certified medical monitoring equipment.
