/**
 * Day 01 - Blink
 * Additional changes based on comments to make it blink SOS
 *
 * Using timing information as described in wikipedia as of 2023-12-25
 * https://en.wikipedia.org/wiki/Morse_code#Representation,_timing,_and_speeds
 * 
 * - short mark, dot or dit (.): "dit duration" is one time unit long
 * - long mark, dash or dah (-): three time units long
 * - inter-element gap between the dits and dahs within a character: one dot duration or one unit long
 * - short gap (between letters): three time units long
 * - medium gap (between words): seven time units long (formerly five)
 * 
 * Specifying the dit duration is not the common practice. Usually, speeds are stated in words per minute.
 * This means we can specify a WPM and use it to calculate the short mark, long mark, inter-element gap, short gap, and medium gap.
 * According to wikipedia we can determine dit duration by solving for t in the folowing equation.
 * T = 1,200/WPM
 */

// Using define so that the usages of it are replaced with the value during compile time to save memory.
#define WORDS_PER_MINUTE 6;

int dotDuration;
int dashDuration;
int interElementGapDuration;
int shortGapDuration;
int mediumGapDuration;


/**
 *The setup function runs once when you press reset or power the board
 */
void setup() {
  // Global Variable Setup
  calculateMorseCodeDurations();
  
  // Board Setup
  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * The loop function runs over and over again forever
 */
void loop() {
  // blinkSOS();
  // delay(mediumGapDuration);

  // Could prompt user for what to message?
  String messageToBlink = "SOS";
  String morseCodeStr = convertToMorseCode(messageToBlink);
  
  for (int i = 0; i < morseCodeStr.length(); i++) {
    char currentChar = morseCodeStr.charAt(i);
    switch (currentChar) {
      case '.':
        ledOnForTime(dotDuration);
        break;
      case '-':
        ledOnForTime(dashDuration);
        break;
      case ' ':
        delay(dotDuration);
        break;
    }
  }

  delay(mediumGapDuration);
  
}

/**
 * Blink SOS
 */
void blinkSOS() {
  // S = ". . ."
  // 0 = "- - -"
  // Calculated (where a space is 1 time unit):
  // ". . .   - - -   . . ."

  // S
  ledOnForTime(dotDuration);
  delay(interElementGapDuration);
  ledOnForTime(dotDuration);
  delay(interElementGapDuration);
  ledOnForTime(dotDuration);
  // End S
  
  delay(shortGapDuration);
  
  // O
  ledOnForTime(dashDuration);
  delay(interElementGapDuration);
  ledOnForTime(dashDuration);
  delay(interElementGapDuration);
  ledOnForTime(dashDuration);
  // End O
  
  delay(shortGapDuration);

  // S
  ledOnForTime(dotDuration);
  delay(interElementGapDuration);
  ledOnForTime(dotDuration);
  delay(interElementGapDuration);
  ledOnForTime(dotDuration);
  // End S
}

void ledOnForTime(int timeOn) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(timeOn);
  digitalWrite(LED_BUILTIN, LOW);
}

/**
 * Calculate and set global duration variables for everything based on the defined WPM
 */
void calculateMorseCodeDurations() {
  dotDuration = 1200 / WORDS_PER_MINUTE;
  dashDuration = dotDuration * 3;
  interElementGapDuration = dotDuration;
  shortGapDuration = dotDuration * 3;
  mediumGapDuration = dotDuration * 7;
}

/**
 * Convert a string to morse code
 * - short mark: .
 * - longer mark: -
 * - intra-character gap: 1 space
 * - short gap: 3 spaces
 * - medium gap: 7 spaces
 */
String convertToMorseCode(String message) {
  String morseCode = "";
  for (int i = 0; i < message.length(); i++) {
    char currentChar = message.charAt(i);
    switch (currentChar) {
      case ' ':
        morseCode.concat("       ");
        break;
      case 'a':
      case 'A':
        morseCode.concat(". -");
        break;
      case 'b':
      case 'B':
        morseCode.concat("- . . .");
        break;
      case 'c':
      case 'C':
        morseCode.concat("- . - .");
        break;
      case 'd':
      case 'D':
        morseCode.concat("- . .");
        break;
      case 'e':
      case 'E':
        morseCode.concat(".");
        break;
      case 'f':
      case 'F':
        morseCode.concat(". . - .");
        break;
      case 'g':
      case 'G':
        morseCode.concat("- - .");
        break;
      case 'h':
      case 'H':
        morseCode.concat(". . . .");
        break;
      case 'i':
      case 'I':
        morseCode.concat(". .");
        break;
      case 'j':
      case 'J':
        morseCode.concat(". - - -");
        break;
      case 'k':
      case 'K':
        morseCode.concat("- . -");
        break;
      case 'l':
      case 'L':
        morseCode.concat(". - . .");
        break;
      case 'm':
      case 'M':
        morseCode.concat("- -");
        break;
      case 'n':
      case 'N':
        morseCode.concat("- .");
        break;
      case 'o':
      case 'O':
        morseCode.concat("- - -");
        break;
      case 'p':
      case 'P':
        morseCode.concat(". - - .");
        break;
      case 'q':
      case 'Q':
        morseCode.concat("- - . -");
        break;
      case 'r':
      case 'R':
        morseCode.concat(". - .");
        break;
      case 's':
      case 'S':
        morseCode.concat(". . .");
        break;
      case 't':
      case 'T':
        morseCode.concat("-");
        break;
      case 'u':
      case 'U':
        morseCode.concat(". . -");
        break;
      case 'v':
      case 'V':
        morseCode.concat(". . . -");
        break;
      case 'w':
      case 'W':
        morseCode.concat(". - -");
        break;
      case 'x':
      case 'X':
        morseCode.concat("- . . -");
        break;
      case 'y':
      case 'Y':
        morseCode.concat("- . - -");
        break;
      case 'z':
      case 'Z':
        morseCode.concat("- - . .");
        break;
      default:
        break;
    }
    int nextIndex = i + 1;
    if (currentChar != ' ' && nextIndex < message.length() && message.charAt(nextIndex) != ' ') {
      morseCode.concat("   ");
    }
  }

  return morseCode;
}
