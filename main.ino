#include <Servo.h>

const int numDots = 6;
const int servoPins[numDots] = {2, 3, 4, 5, 6, 7}; // Pins for Braille dots 1–6
Servo brailleServos[numDots];

// Servo positions
const int dotUp = 90;    // "Raised" dot
const int dotDown = 0;   // "Lowered" dot

// Braille pattern mapping
struct Braille {
  char character;
  byte pattern;
};

const Braille brailleMap[] = {
  {'a', B000001}, {'b', B000011}, {'c', B001001}, {'d', B011001},
  {'e', B010001}, {'f', B001011}, {'g', B011011}, {'h', B010011},
  {'i', B001010}, {'j', B011010}, {'k', B000101}, {'l', B000111},
  {'m', B001101}, {'n', B011101}, {'o', B010101}, {'p', B001111},
  {'q', B011111}, {'r', B010111}, {'s', B001110}, {'t', B011110},
  {'u', B100101}, {'v', B100111}, {'w', B111010}, {'x', B101101},
  {'y', B111101}, {'z', B110101},
  {'.', B010011}, {',', B000011}, {';', B000111}, {':', B010011},
  {'!', B010111}, {'?', B010110}, {'-', B000100}, {'\'', B000010},
  {'"', B000110}, {'(', B011110}, {')', B011110}, {' ', B000000}
};

const int brailleCount = sizeof(brailleMap) / sizeof(Braille);

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numDots; i++) {
    brailleServos[i].attach(servoPins[i]);
    brailleServos[i].write(dotDown); // Start with all dots lowered
  }
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      // For each character in the input line
      for (int i = 0; i < line.length(); i++) {
        char c = tolower(line.charAt(i));
        byte pattern = getBraillePattern(c);

        for (int j = 0; j < numDots; j++) {
          if ((pattern >> j) & 1) {
            brailleServos[j].write(dotUp);
          } else {
            brailleServos[j].write(dotDown);
          }
        }

        delay(1500); // Pause to allow tactile reading, adjust as needed
      }
      // After a full line, lower all dots before next line
      for (int i = 0; i < numDots; i++) {
        brailleServos[i].write(dotDown);
      }
      delay(1000); // Short pause before next line
    }
  }
}

byte getBraillePattern(char c) {
  for (int i = 0; i < brailleCount; i++) {
    if (brailleMap[i].character == c) {
      return brailleMap[i].pattern;
    }
  }
  return B000000; // Default: no dots raised
}