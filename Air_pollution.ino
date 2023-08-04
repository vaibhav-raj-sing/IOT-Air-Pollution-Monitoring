#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Jio_fiber_5G";
const char* password = "1234";

// Cloud server details
const String serverURL = "https://yourserver.com/api"; // Replace with your cloud server endpoint

// Initialize the LCD object with the appropriate address
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int gasSensorPin = A0; // Arduino analog input pin connected to gas sensor

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Air Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");
  delay(2000);

  lcd.clear();
  lcd.print("Gas Concentration:");
  connectWiFi();
}

void loop() {
  // Read the analog value from the gas sensor
  int gasValue = analogRead(gasSensorPin);

  // Convert the analog value to gas concentration in ppm
  float gasConcentration = calculateGasConcentration(gasValue);

  // Display the gas concentration on the LCD
  lcd.setCursor(0, 1);
  lcd.print(gasConcentration);
  lcd.print(" ppm");

  // Send the data to the cloud server
  sendDataToCloud(gasConcentration);

  delay(2000); // Delay between each reading (adjust this based on your requirements)
}

// Function to connect to WiFi
void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

// Function to convert analog value to gas concentration
float calculateGasConcentration(int rawValue) {
  
  float calibrationFactor = 0.2; // Calibration factor to convert analog value to ppm
  float zeroPointVoltage = 400; // Sensor's zero point voltage (adjust this based on your sensor)

  // Calculate gas concentration in ppm
  float sensorVoltage = (rawValue / 1023.0) * 5.0; // Convert raw analog value to voltage
  float gasConcentration = (sensorVoltage - zeroPointVoltage) / calibrationFactor;

  return gasConcentration;
}

// Function to send data to the cloud server
void sendDataToCloud(float gasConcentration) {
  // Create an HTTPClient object
  HTTPClient http;

  // Construct the data to be sent
  String postData = "gas_concentration=" + String(gasConcentration);

  // Send the POST request to the server
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(postData);
  http.end();

  // Check the response from the server
  if (httpResponseCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.println("Error sending data to server!");
  }
}
