#include <Servo.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
Servo windowServo;

void setup() {
  Serial.begin(9600); // Initialize serial communication with the computer
  SerialBT.begin("ESP32_BT"); // Initialize Bluetooth serial communication
  windowServo.attach(2); // Pin for servo control
  
  // Attempt to pair with the Arduino Bluetooth module
  if (!pairWithArduino()) {
    Serial.println("Failed to pair with Arduino!");
    while (1); // Stop execution if pairing fails
  }
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    if (command.equals("OPEN_WINDOWS")) {
      // Open the window by rotating the servo motor
      windowServo.write(90); // Adjust the angle as needed
      delay(2000); // Wait for the servo to reach the desired position
    }
  }
}

bool pairWithArduino() {
  Serial.println("Scanning for nearby devices...");
  
  // Scan for Arduino's Bluetooth module UUID
  int devicesFound = SerialBT.scanForUuid("00001101-0000-1000-8000-00805F9B34FB");
  
  if (devicesFound > 0) {
    Serial.println("Arduino Bluetooth module found. Initiating pairing...");
    
    // Initiate pairing with the Arduino's Bluetooth module
    bool paired = SerialBT.pair();
    
    if (paired) {
      Serial.println("Pairing successful!");
      return true;
    } else {
      Serial.println("Pairing failed.");
    }
  } else {
    Serial.println("No Arduino Bluetooth module found.");
  }
  
  return false;
}
