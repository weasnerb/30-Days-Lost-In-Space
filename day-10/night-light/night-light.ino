
/**
 * Day 10 - Night Light
 */

#include "Arduino.h"

// A Pins are Analog pins, which we need for the photoresistor
const byte PHOTORESISTOR_PIN = A0;

// We are calling dip switch positions from the labeling on the switch.
const byte DIP_SWITCH_1_PIN = 2;
const byte DIP_SWITCH_2_PIN = 3;
const byte DIP_SWITCH_3_PIN = 4;

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

enum Color { RED, BLUE, GREEN, YELLOW, CYAN, MAGENTA, WHITE, OFF };

const uint16_t BATTERY_CAPACITY = 50000;

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  pinMode(PHOTORESISTOR_PIN, INPUT);
  
  // Dip Switch
  pinMode(DIP_SWITCH_1_PIN, INPUT);
  pinMode(DIP_SWITCH_2_PIN, INPUT);
  pinMode(DIP_SWITCH_3_PIN, INPUT);

  // Rgb LED
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
  // Use a static value for intensity so that we don't get a flickering effect if the current
  // brightness is right at the threshold for on/off
  static uint8_t intensity = 0;

  if (shouldTurnOnNightLight()) {
    intensity = intensity < 255 ? intensity + 1 : intensity;
  } else {
    intensity = intensity > 0 ? intensity - 1 : intensity;
  }

  Color nightLightColor = getNightLightColor();
  setColor(nightLightColor, intensity);
}

/**
 * Determine whether we should turn on the night light based on the current photoresistor value
 */
bool shouldTurnOnNightLight() {
  // Read current photoresister value
  uint16_t lightAmount = analogRead(PHOTORESISTOR_PIN);
  // Print photoresister value to console
  Serial.println(lightAmount);

  return lightAmount < 15;
}

/**
 * One function to set all the values for RGB to the different RGB pins at the same time.
 */
void setRgbLevels(uint8_t red_intensity, uint8_t green_intensity, uint8_t blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}

/**
 * Set the Rgb Led to the specified color
 */
void setColor(Color color, uint8_t intensity) {
  // Need to use an Enum for "string" like values in switch statement.
  switch (color) {
    case RED:
      setRgbLevels(intensity, 0, 0);
      break;
    case GREEN:
      setRgbLevels(0, intensity, 0);
      break;
    case BLUE:
      setRgbLevels(0, 0, intensity);
      break;
    case YELLOW:
      setRgbLevels(intensity, intensity, 0);
      break;
    case CYAN:
      setRgbLevels(0, intensity, intensity);
      break;
    case MAGENTA:
      setRgbLevels(intensity, 0, intensity);
      break;
    case WHITE:
      setRgbLevels(intensity, intensity, intensity);
      break;
    case OFF:
    default:
      setRgbLevels(0, 0, 0);
  }
}

/**
 * Read the value from the dip switch to determine the color to make the led when the night light is on
 */
Color getNightLightColor() {

  char binarySwitchState[4];
  binarySwitchState[0] = digitalRead(DIP_SWITCH_1_PIN) == HIGH ? '1' : '0';
  binarySwitchState[1] = digitalRead(DIP_SWITCH_2_PIN) == HIGH ? '1' : '0';
  binarySwitchState[2] = digitalRead(DIP_SWITCH_3_PIN) == HIGH ? '1' : '0';
  // Add Null Terminating Char
  binarySwitchState[3] = '\0';
  
  if (0 == strcmp(binarySwitchState, "000")) {
    return Color::OFF;
  } else if (0 == strcmp(binarySwitchState, "001")) {
    return Color::BLUE;
  } else if (0 == strcmp(binarySwitchState, "010")) {
    return Color::GREEN;
  } else if (0 == strcmp(binarySwitchState, "011")) {
    return Color::CYAN;
  } else if (0 == strcmp(binarySwitchState, "100")) {
    return Color::RED;
  } else if (0 == strcmp(binarySwitchState, "101")) {
    return Color::MAGENTA;
  } else if (0 == strcmp(binarySwitchState, "110")) {
    return Color::YELLOW;
  } else if (0 == strcmp(binarySwitchState, "111")) {
    return Color::WHITE;
  }

}



