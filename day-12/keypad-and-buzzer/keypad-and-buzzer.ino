
/**
 * Day 12 - Into To Buzzer!
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

const uint16_t TONES[ROWS][COLS] = {
  { 31, 93, 147, 208 },
  { 247, 311, 370, 440 },
  { 523, 587, 698, 880 },
  { 1397, 2637, 3729, 0 }  // Use frequency of 0 for bottom right key to end tone.
};

const byte BUZZER_PIN = 10;

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  // Keypad Pins get setup as a part of the Keypad initialization.
  pinMode(BUZZER_PIN, OUTPUT);

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
  Serial.print("Key: ");
  Serial.print(pressedButton);

  // Unfortunately we cannot use keypad.findInList to get the index of the pressed key in the list of ALL keys, because it only gets the index
  // of the char in the array of ACTIVE keys, so if it's the only button pressed, the returned index will always be 0.
  uint16_t toneFrequency = getToneFromButton(pressedButton);

  // Display the character returned for the button that was pressed.
  Serial.print("\tFreq: ");
  Serial.println(toneFrequency);

  if (toneFrequency > 0) {
    tone(BUZZER_PIN, toneFrequency);
  } else {
    noTone(BUZZER_PIN);
  }
}


uint16_t getToneFromButton(char button) {
  for (byte rowIndex = 0; rowIndex < ROWS; rowIndex++) {
    for (byte colIndex = 0; colIndex < COLS; colIndex++) {
      if (BUTTONS[rowIndex][colIndex] == button) {
        return TONES[rowIndex][colIndex];
      }
    }
  }
  return 0;
}
