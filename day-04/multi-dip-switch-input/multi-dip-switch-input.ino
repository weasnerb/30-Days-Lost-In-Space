
/**
 * Day 04 - Multiple Inputs via dip switch
 */

#include "Arduino.h"


/*
 * Apparently #define is deprecated, so we should be using const
 */
const byte CABIN_LIGHTS_PIN = 10;
const byte STORAGE_LIGHTS_PIN = 11;
const byte COCKPIT_LIGHTS_PIN = 12;

const byte CABIN_LIGHTS_SWITCH_PIN = 2;
const byte STORAGE_LIGHTS_SWITCH_PIN = 3;
const byte COCKPIT_LIGHTS_SWITCH_PIN = 4;


/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);

  pinMode(STORAGE_LIGHTS_PIN, INPUT);
  pinMode(STORAGE_LIGHTS_SWITCH_PIN, OUTPUT);

  pinMode(COCKPIT_LIGHTS_PIN, INPUT);
  pinMode(COCKPIT_LIGHTS_SWITCH_PIN, OUTPUT);
}


/**
 * The loop function runs over and over again forever
 */
void loop() {
  // Could use if/else here, but because we want the state of our light to match
  // the state of the light switch, we can just pass the value in as a parameter.
  
  byte cabinLightSwitchState = digitalRead(CABIN_LIGHTS_SWITCH_PIN);
  digitalWrite(CABIN_LIGHTS_PIN, cabinLightSwitchState);

  byte storageLightSwitchState = digitalRead(STORAGE_LIGHTS_SWITCH_PIN);
  digitalWrite(STORAGE_LIGHTS_PIN, storageLightSwitchState);

  byte cockpitLightSwitchState = digitalRead(COCKPIT_LIGHTS_SWITCH_PIN);
  digitalWrite(COCKPIT_LIGHTS_PIN, cockpitLightSwitchState);

}
