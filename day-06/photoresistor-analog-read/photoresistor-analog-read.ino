
/**
 * Day 06 - Photoresistor 
 */

#include "Arduino.h"

// A Pins are Analog pins, which we need for the photoresistor
const byte PHOTORESISTOR_PIN = A0;


const uint16_t MIN_DELAY = 50;
const uint16_t MAX_DELAY = 500;

/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Board Setup
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);       // output since we will control the built in LED
    // input value from analog pin connected to photoresistor

  /*
   * To show you the exact value being read on the analog pin we will print the exact number
   * using our Arduino IDE's "Serial Monitor".  This is a window displayed under the sketch that
   * can display text sent to it from the HERO.
   *
   * The speed that this data is sent/received must match between the Arduino IDE and HERO.  We
   * configure this speed for the HERO to send data using the Serial.begin() function.  Throughout
   * this course we will use a typical value of 9600 "baud", which is 9,600 bit of information per
   * second.
   */
  Serial.begin(9600);

}


/**
 * The loop function runs over and over again forever
 */
void loop() {
  // Read current photoresister value
  uint16_t lightAmount = analogRead(PHOTORESISTOR_PIN);

  // Log value to the serial console'
  // Better to not have string interpolation for memory and 
  Serial.print("Light Amount: ");
  Serial.print(lightAmount);


  /**
   * These values would normally be lost when each run of our loop() ends, but by adding
   * the "static" declaration we indicate that these local variables should maintain their
   * values between loop() runs. We do this instead of having global level variables so that they
   * are initialized with the first lightAmount that we retrieve.
   */
  static uint16_t darkestLight = lightAmount;
  static uint16_t brightestLight = lightAmount;

  /**
   * Adjust Darkest and Brightest light recorded with the current light amount if brigher or darker than previous value.
   */
  if (lightAmount < darkestLight) {
    darkestLight = lightAmount;
  }
  if (lightAmount > brightestLight) {
    brightestLight = lightAmount;
  }

  /**
   * Map current light amount from between our darkest and brightest values to max and min delay values.
   */
  uint16_t delayForTime = map(lightAmount, darkestLight, brightestLight, MAX_DELAY, MIN_DELAY);
  Serial.print(", Delay: ");
  Serial.println(delayForTime);

  // Now blink our built in LED using our delay_value.
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayForTime);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayForTime);

}
