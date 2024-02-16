
/**
 * Day 08 - Intro to Rgb
 */

#include "Arduino.h"

// A Pins are Analog pins, which we need for the photoresistor
const byte PHOTORESISTOR_PIN = A0;

/*
 * Each color in an RGB LED is controlled with a different pin
 *
 * NOTE: Only pins 3, 5, 6, 9, 10 and 11 on the HERO board support PWM which is
 *       indicated on the board by preceding those pin numbers on the HERO board
 *       with a tilde ('~') character.  Only those pins support PWM and analogWrite().
 */
const byte RED_PIN = 9;
const byte GREEN_PIN = 10;
const byte BLUE_PIN = 11;

enum Color { RED, BLUE, GREEN, YELLOW, CYAN, MAGENTA, WHITE };

const uint16_t BATTERY_CAPACITY = 50000;

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  pinMode(PHOTORESISTOR_PIN, INPUT);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Serial Setup
  Serial.begin(9600);

}



/**
 * The loop function runs over and over again forever
 */
void loop() {
  float batteryPercentage = getCurrentBatteryChargePercentage();
  
  // Print percentage to console
  Serial.print(batteryPercentage);
  Serial.println('%');

  // time per loop is used to calculate the total delay we can have per loop.
  // Note: The higher this is, the longer it will take to "charge" the battery, due to the amount of readings over time decreasing.
  uint16_t timePerLoop = 2000;

  if (batteryPercentage >= 100) {
    // Steady Green at 100%
    setRgbLevels(0, 255, 0);
    delay(timePerLoop);
  } else if (batteryPercentage > 25) {
    // Slow pulse
    uint8_t pulsesPerLoop = 1;
    for (uint8_t pulseIndex = 0; pulseIndex < pulsesPerLoop; pulseIndex++) {
      pulseColor(GREEN, timePerLoop / pulsesPerLoop);
    }
  } else {
    // Fast pulse
    uint8_t pulsesPerLoop = 2;
    for (uint8_t pulseIndex = 0; pulseIndex < pulsesPerLoop; pulseIndex++) {
      pulseColor(RED, timePerLoop / pulsesPerLoop);
    }
  }
}

/**
 * Update the current battery level and return the current charge as a percentage
 */
float getCurrentBatteryChargePercentage() {
  // Static to make the value persist between function calls.
   // Current battery charge level (set to 0 first time)
  static uint16_t batteryLevel = 0; 
  
  // Read current photoresister value
  // Doubling the incomming value to make charging appear faster
  uint16_t lightAmount = analogRead(PHOTORESISTOR_PIN) * 2;
  batteryLevel += lightAmount;
  
  // Check if we charged over the battery level
  if (batteryLevel > BATTERY_CAPACITY) {
    batteryLevel = BATTERY_CAPACITY;
  }

  return ((float)batteryLevel / (float)BATTERY_CAPACITY) * 100;
}


void setRgbLevels(uint8_t red_intensity, uint8_t green_intensity, uint8_t blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}

void pulseColor(Color color, uint16_t totalTimeToPulseFor) {
  uint8_t MAX_BRIGHTNESS = 255;
  uint16_t delayTime = totalTimeToPulseFor / (MAX_BRIGHTNESS * 2);

  int8_t brightnessDirection = 1;
  for (int16_t brightnessIndex = 0; brightnessIndex > -1; brightnessIndex = brightnessIndex + brightnessDirection) {
    // Need to use an Enum for "string" like values in switch statement.
    switch (color) {
      case RED:
        setRgbLevels(brightnessIndex, 0, 0);
        break;
      case GREEN:
        setRgbLevels(0, brightnessIndex, 0);
        break;
      case BLUE:
        setRgbLevels(0, 0, brightnessIndex);
        break;
      case YELLOW:
        setRgbLevels(brightnessIndex, brightnessIndex, 0);
        break;
      case CYAN:
        setRgbLevels(0, brightnessIndex, brightnessIndex);
        break;
      case MAGENTA:
        setRgbLevels(brightnessIndex, 0, brightnessIndex);
        break;
      case WHITE:
        setRgbLevels(brightnessIndex, brightnessIndex, brightnessIndex);
        break;
      default:
        setRgbLevels(0, 0, 0);
    }

    if (brightnessIndex >= MAX_BRIGHTNESS) {
      // Switch direction back to 0
      brightnessDirection = -1;
    }

    delay(delayTime);
  }
}


