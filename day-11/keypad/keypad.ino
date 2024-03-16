
/**
 * Day 11 - Into To Keypad and Keypad Library
 */

#include "Arduino.h"

// Add .zip Library to arduino ide (included in root of 30 days lost in space repo)
#include <Keypad.h>


// Setup number of Rows and Columns for Keypad (using 4x4)
const byte ROWS = 4;
const byte COLS = 4;

// Input pins for Keypad
const byte ROW_PINS[ROWS] = {5, 4, 3, 2};
const byte COL_PINS[COLS] = {6, 7, 8, 9};

// Array of Arrays.
// This makes a grid that corresponds to the buttons of the keypad
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { '*', '0', '#', 'D'},
};

Keypad keypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  // Pins get setup as a part of the Keypad initialization.

  // Serial Setup
  Serial.begin(9600);
}

/**
 * The loop function runs over and over again forever
 */
void loop() {
  // waitForKey() will wait here until any button is pressed and only after one is pressed will it return the character we defined in our BUTTONS array.
  char pressedButton = keypad.waitForKey();

  // Display the character returned for the button that was pressed.
  Serial.println(pressedButton);
}
