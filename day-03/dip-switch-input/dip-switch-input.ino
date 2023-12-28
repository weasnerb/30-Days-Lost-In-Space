
/**
 * Day 03 - Input via dip switch
 */

#include "Arduino.h"

#define CABIN_LIGHTS_PIN 12
#define CABIN_LIGHTS_SWITCH_PIN 2


/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);
}


/**
 * The loop function runs over and over again forever
 */
void loop() {
  byte cabinLightSwitchState = digitalRead(CABIN_LIGHTS_SWITCH_PIN);
  // Could use if/else here, but because we want the state of our cabin light to match
  // the state of the light switch, we can just input it.
  digitalWrite(CABIN_LIGHTS_PIN, cabinLightSwitchState);

}
