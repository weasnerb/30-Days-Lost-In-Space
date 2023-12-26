/**
 * Day 02 - Blink External LED
 */
// Arduino.h is included automatically by the arduino ide upon compilation.
#include "Arduino.h"

#define CABIN_LIGHTS_PIN 12

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {

  // Board Setup
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);
}


/**
 * The loop function runs over and over again forever
 */
void loop() {
  digitalWrite(CABIN_LIGHTS_PIN, HIGH);
  delay(1000);
  digitalWrite(CABIN_LIGHTS_PIN, LOW);
  delay(100);
}
