# IOT Based Air Pollution Monitoring System

### Introduction:
The improved IoT-based Air Pollution Monitoring System prototype now includes an ESP8266 WiFi module for data communication with a cloud server. The system measures the concentration of air pollutants using an MQ135 gas sensor and displays the data on an LCD screen. It also sends the data to a cloud platform for remote monitoring and visualization.

### Components Used:

Arduino board (e.g., Arduino Uno)
MQ135 Gas Sensor
LCD display (16x2 or 20x4)
ESP8266 WiFi module (e.g., NodeMCU)
Breadboard and jumper wires
Working Principle:
The MQ135 gas sensor provides analog output based on the concentration of air pollutants it detects. The analog output is read by the Arduino using an analog input pin. The Arduino then converts this analog value to gas concentration in ppm using a calibration function. The LCD screen displays the real-time gas concentration, and the ESP8266 WiFi module sends the data to a cloud server for remote monitoring and visualization.

### Setup:

Connect the gas sensor's analog output pin to the Arduino's analog input pin (A0).
Connect the LCD to the Arduino using the I2C interface.
Connect the ESP8266 module to the Arduino.
Replace the "YourWiFiSSID" and "YourWiFiPassword" placeholders with your WiFi credentials.
Replace "https://yourserver.com/api" with the endpoint of your cloud server.
Upload the provided Arduino code to the board using the Arduino IDE.
Power on the system.

### Usage:

Once powered on, the system will display "Air Quality Monitoring..." for two seconds, followed by "Gas Concentration:" on the LCD screen.
The LCD will continuously show the real-time gas concentration in ppm.
The data will be sent to the cloud server via the WiFi module for remote monitoring and visualization.

### Customization:

The calibrationFactor and zeroPointVoltage variables in the calculateGasConcentration function need to be adjusted based on the specifications of your specific gas sensor. Refer to the sensor datasheet for calibration values.
You can customize the cloud server endpoint to match your server's API for data storage and visualization.