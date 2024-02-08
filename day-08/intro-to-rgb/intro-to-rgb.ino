
/**
 * Day 08 - Intro to Rgb
 */

#include "Arduino.h"

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


const uint16_t BATTERY_CAPACITY = 50000;

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

}

uint16_t batteryLevel = 0;  // Current battery charge level (set to 0 first time)

/**
 * The loop function runs over and over again forever
 */
void loop() {
  for (uint8_t colorIndex = 0; colorIndex < 7; colorIndex++) {
    int8_t brightnessDirection = 1;
    for (int16_t brightnessIndex = 0; brightnessIndex > -1; brightnessIndex = brightnessIndex + brightnessDirection) {
      switch (colorIndex) {
        case 0:
          // Increase Red
          setRgbLevels(brightnessIndex, 0, 0);
          break;
        case 1:
          // Increase Green
          setRgbLevels(0, brightnessIndex, 0);
          break;
        case 2:
          // Increase Blue
          setRgbLevels(0, 0, brightnessIndex);
          break;
        case 3:
          // Increase Yellow
          setRgbLevels(brightnessIndex, brightnessIndex, 0);
          break;
        case 4:
          // Increase Cyan
          setRgbLevels(0, brightnessIndex, brightnessIndex);
          break;
        case 5:
          // Increase Magenta
          setRgbLevels(brightnessIndex, 0, brightnessIndex);
          break;
        case 6:
          // Increase White
          setRgbLevels(brightnessIndex, brightnessIndex, brightnessIndex);
          break;
      }

      if (brightnessIndex >= 255) {
        // Switch direction back to 0
        brightnessDirection = -1;
      }

      delay(10);
    }
  }
  
}

void setRgbLevels(uint8_t red_intensity, uint8_t green_intensity, uint8_t blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}


