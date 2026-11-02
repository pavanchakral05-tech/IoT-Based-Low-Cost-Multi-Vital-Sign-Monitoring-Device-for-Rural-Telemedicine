# Working Principle

## IoT-Based Low-Cost Multi-Vital Sign Monitoring Device for Rural Telemedicine

### 1. Sensor Data Acquisition

The system uses three biomedical sensors to collect patient health parameters:

- MAX30100: Measures heart rate and blood oxygen saturation (SpO2).
- AD8232: Captures the electrical activity of the heart as an ECG signal.
- DS18B20: Measures body temperature.

### 2. Data Processing

The ESP32 microcontroller receives the sensor data through I2C, analog and OneWire interfaces. It processes the readings and prepares them for display and cloud transmission.

### 3. Local Display

The SSD1306 OLED display provides local visualization of:
- Heart rate (BPM)
- SpO2 (%)
- Body temperature (°C)
- ECG signal information

### 4. Wireless Communication

The ESP32 uses its built-in Wi-Fi connectivity to connect to the internet and transmit the processed sensor readings.

### 5. Cloud Monitoring

ThingSpeak receives and stores the uploaded measurements. Its dashboard provides graphical visualization of the available health parameters.

### 6. Overall System Operation

1. Power ON the device.
2. Initialize ESP32 and connected sensors.
3. Acquire physiological data.
4. Process the sensor measurements.
5. Display readings on the OLED.
6. Connect to Wi-Fi.
7. Upload available readings to ThingSpeak.
8. Repeat the monitoring process.

### 7. Application

The system demonstrates the use of IoT technology for affordable remote health monitoring and rural telemedicine applications.

### Disclaimer

This academic prototype is not a certified medical diagnostic device. Its measurements should not replace professional medical assessment.
