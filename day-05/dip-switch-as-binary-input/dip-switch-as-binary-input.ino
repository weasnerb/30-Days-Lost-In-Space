
/**
 * Day 05 - Creative Day. 
 * Taking in dip switch inputs as binary.
 * 
 * There are 3 switches, each binary, so we can use the state of all the switches to turn on a light
 * 000 - No lights
 * 001 - Light 1
 * 010 - Light 2
 * 011 - Light 3
 * 100 - Light 4
 * 101 - Light 5
 * 110 - Light 6
 * 111 - Light 7
 */

#include "Arduino.h"


/*
 * Apparently #define is deprecated, so we should be using const
 */
// We are calling dip switch positions from the labeling on the switch, not 
const byte DIP_SWITCH_1_PIN = 2;
const byte DIP_SWITCH_2_PIN = 3;
const byte DIP_SWITCH_3_PIN = 4;
 
const byte LIGHT_1_PIN = 7;
const byte LIGHT_2_PIN = 8;
const byte LIGHT_3_PIN = 9;
const byte LIGHT_4_PIN = 10;
const byte LIGHT_5_PIN = 11;
const byte LIGHT_6_PIN = 12;
const byte LIGHT_7_PIN = 13;

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  // Dip Switch
  pinMode(DIP_SWITCH_1_PIN, INPUT);
  pinMode(DIP_SWITCH_2_PIN, INPUT);
  pinMode(DIP_SWITCH_3_PIN, INPUT);

  // Lights
  pinMode(LIGHT_1_PIN, OUTPUT);
  pinMode(LIGHT_2_PIN, OUTPUT);
  pinMode(LIGHT_3_PIN, OUTPUT);
  pinMode(LIGHT_4_PIN, OUTPUT);
  pinMode(LIGHT_5_PIN, OUTPUT);
  pinMode(LIGHT_6_PIN, OUTPUT);
  pinMode(LIGHT_7_PIN, OUTPUT);
}


/**
 * The loop function runs over and over again forever
 */
void loop() {
  char binarySwitchState[4];
  binarySwitchState[0] = digitalRead(DIP_SWITCH_1_PIN) == HIGH ? '1' : '0';
  binarySwitchState[1] = digitalRead(DIP_SWITCH_2_PIN) == HIGH ? '1' : '0';
  binarySwitchState[2] = digitalRead(DIP_SWITCH_3_PIN) == HIGH ? '1' : '0';
  // Add Null Terminating Char
  binarySwitchState[3] = '\0';

  byte light1State = LOW;
  byte light2State = LOW;
  byte light3State = LOW;
  byte light4State = LOW;
  byte light5State = LOW;
  byte light6State = LOW;
  byte light7State = LOW;
  
  if (0 == strcmp(binarySwitchState, "000")) {
    // All lights off.
  } else if (0 == strcmp(binarySwitchState, "001")) {
    light1State = HIGH;
  } else if (0 == strcmp(binarySwitchState, "010")) {
    light2State = HIGH;
  } else if (0 == strcmp(binarySwitchState, "011")) {
    light3State = HIGH;
  } else if (0 == strcmp(binarySwitchState, "100")) {
    light4State = HIGH;
  } else if (0 == strcmp(binarySwitchState, "101")) {
    light5State = HIGH;
  } else if (0 == strcmp(binarySwitchState, "110")) {
    light6State = HIGH;
  } else if (0 == strcmp(binarySwitchState, "111")) {
    light7State = HIGH;
  }

  digitalWrite(LIGHT_1_PIN, light1State);
  digitalWrite(LIGHT_2_PIN, light2State);
  digitalWrite(LIGHT_3_PIN, light3State);
  digitalWrite(LIGHT_4_PIN, light4State);
  digitalWrite(LIGHT_5_PIN, light5State);
  digitalWrite(LIGHT_6_PIN, light6State);
  digitalWrite(LIGHT_7_PIN, light7State);

}
