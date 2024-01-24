
/**
 * Day 07 - Charging the battery
 */

#include "Arduino.h"

// A Pins are Analog pins, which we need for the photoresistor
const byte PHOTORESISTOR_PIN = A0;


const uint16_t BATTERY_CAPACITY = 50000;

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  pinMode(PHOTORESISTOR_PIN, INPUT);

  // Serial Setup
  Serial.begin(9600);
}

uint16_t batteryLevel = 0;  // Current battery charge level (set to 0 first time)

/**
 * The loop function runs over and over again forever
 */
void loop() {
  if (batteryLevel < BATTERY_CAPACITY) {
    continueCharging();
  }

  printCurrentChargeLevel();
}

void continueCharging() {
  // Read current photoresister value
  uint16_t lightAmount = analogRead(PHOTORESISTOR_PIN);
  batteryLevel += lightAmount;
  
  // Check if we charged over the battery level
  if (batteryLevel > BATTERY_CAPACITY) {
    batteryLevel = BATTERY_CAPACITY;
  }
}

void printCurrentChargeLevel() {
  if (batteryLevel < BATTERY_CAPACITY) {
    Serial.print(((double)batteryLevel / (double)BATTERY_CAPACITY) * 100);
    Serial.println('%');
  } else {
    Serial.println("FULLY CHARGED");
  }
}
