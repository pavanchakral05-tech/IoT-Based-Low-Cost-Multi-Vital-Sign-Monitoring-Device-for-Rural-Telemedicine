# Hardware Components – IoT Health Monitoring System

## 1. ESP32 Development Board
- Function: Main processing and Wi-Fi communication.
- Interface: GPIO, ADC and I2C.
- Purpose: Processes sensor readings and transmits data to ThingSpeak.

## 2. MAX30100 Pulse Oximeter
- Function: Heart rate and blood oxygen monitoring.
- Interface: I2C.
- Purpose: Measures pulse rate and SpO2 using optical sensing.

## 3. AD8232 ECG Sensor
- Function: ECG signal acquisition.
- Interface: Analog output and digital lead-off detection.
- Purpose: Captures electrical activity of the heart.

## 4. DS18B20 Temperature Sensor
- Function: Temperature measurement.
- Interface: OneWire.
- Purpose: Measures temperature digitally.

## 5. OLED Display
- Type: 0.96-inch SSD1306.
- Interface: I2C.
- Purpose: Displays sensor readings locally.

## 6. Power Supply
- Battery: 18650 Li-ion.
- Charging module: TP4056.
- Purpose: Provides rechargeable portable power.

## 7. Interconnection Summary

| Component | ESP32 Pin |
|---|---|
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| MAX30100 SDA | GPIO 21 |
| MAX30100 SCL | GPIO 22 |
| DS18B20 DATA | GPIO 23 |
| AD8232 OUTPUT | GPIO 34 |
| AD8232 LO+ | GPIO 32 |
| AD8232 LO- | GPIO 33 |

**Note:** Use a 4.7 kΩ pull-up resistor between DS18B20 DATA and its supply. Check module voltage compatibility before connecting. Do not connect a 5 V analog output directly to an ESP32 ADC pin.

## 8. Hardware Safety

- Verify all power connections before switching on.
- Use a regulated supply appropriate for each module.
- Use a common ground for the electronic modules.
- Never connect the device to a patient while it is connected to unsafe mains-powered equipment.
- This prototype is not a certified medical device.

---
