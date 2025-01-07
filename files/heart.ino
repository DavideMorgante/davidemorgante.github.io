#include <Arduino.h>

// Pin definitions
#define dataPin    0  // PB0 on ATtiny85
#define clockPin   1  // PB1
#define latchPin   2  // PB2
#define buttonPin  4  // PB4 (with internal pull-up and button to GND)

// Simple macros for LED patterns
#define ALL_OFF 0x0000

// Sequence 0: All On
const uint16_t sequenceAllOn[] = {0xFEFE};
const uint8_t lengthAllOn = 1;
const uint16_t delayAllOn = 100;  // Not really used since only one step

// Sequence 1: Flashing (off, on)
const uint16_t sequenceFlashing[] = {
  ALL_OFF, 
  0xFEFE // all on
};
const uint8_t lengthFlashing = 2;
const uint16_t delayFlashing = 500;

// Sequence 2: Progressive On/Off
const uint16_t sequenceProgressive[] = {
  0x0000,
  0x0002,
  0x0006,
  0x000E,
  0x001E,
  0x003E,
  0x007E,
  0x00FE,
  0x80FE,
  0xC0FE,
  0xE0FE,
  0xF0FE,
  0xF8FE,
  0xFCFE,
  0xFEFE,

  0xFCFE,
  0xF8FE,
  0xF0FE,
  0xE0FE,
  0xC0FE,
  0x80FE,
  0x00FE,
  0x007E,
  0x003E,
  0x001E,
  0x000E,
  0x0006,
  0x0002,
  0x0000 
};

const uint8_t lengthProgressive = sizeof(sequenceProgressive)/sizeof(sequenceProgressive[0]); // should be 29 steps
const uint16_t delayProgressive = 100; // ms per step


// Sequence 3: Chaser of three LEDs
// Addressing positions for LEDs: 1-2-3-4-5-6-13-12-11-10-9-8-7
const uint16_t sequenceChaser[] = {
  0x000e,
  0x001c,
  0x0038,
  0x0070,
  0x00e0,
  0x80c0,
  0xc080,
  0xe000,
  0x7000,
  0x3800,
  0x1c00,
  0x0e00,
  0x0602,
  0x0206
};
const uint8_t lengthChaser = sizeof(sequenceChaser)/sizeof(sequenceChaser[0]);; // one step per LED in the circle
const uint16_t delayChaser = 50;

// Sequence 3: Progressive On/Off backwards
const uint16_t sequenceProgressiveBack[] = {
  0x0000,
  0x0002,
  0x0006,
  0x000E,
  0x001E,
  0x003E,
  0x007E,
  0x00FE,
  0x80FE,
  0xC0FE,
  0xE0FE,
  0xF0FE,
  0xF8FE,
  0xFCFE,
  0xFEFE, 

  0xfefc,
  0xfef8,
  0xfef0,
  0xfee0,
  0xfec0,
  0xfe80,
  0xfe00,
  0x7e00,
  0x3e00,
  0x1e00,
  0x0e00,
  0x0600,
  0x0200,
  0x0000  
};

const uint8_t lengthProgressiveBack = sizeof(sequenceProgressiveBack)/sizeof(sequenceProgressiveBack[0]); // should be 29 steps
const uint16_t delayProgressiveBack = 100; // ms per step

// Sequence 5: Book Horizontal
const uint16_t sequenceBook[] = {
  0x0000,
  0x1e1e,
  0xfefe,
  0xf0f0,
  0x0000
};
const uint8_t lengthBook = sizeof(sequenceBook)/sizeof(sequenceBook[0]);; // one step per LED in the circle
const uint16_t delayBook = 100;

// Sequence 5: Book Vertical
const uint16_t sequenceVBook[] = {
  0x0000,
  0x00fe,
  0xfefe,
  0xfe00,
  0x0000
};
const uint8_t lengthVBook = sizeof(sequenceVBook)/sizeof(sequenceVBook[0]);; // one step per LED in the circle
const uint16_t delayVBook = 100;

// Sequence 6: Message
const uint16_t sequenceMsg[] = {
  0x0000,
  0x10fe,
  0x3838,
  0x021e,
  0xc6fe,
  0xfefe,
};
const uint8_t lengthMsg = sizeof(sequenceMsg)/sizeof(sequenceMsg[0]);; // one step per LED in the circle
const uint16_t delayMsg = 500;

// Sequence 7: follower
const uint16_t sequenceFollow[] = {
  0x0002,
  0x0004,
  0x0008,
  0x0010,
  0x0020,
  0x0040,
  0x0080,
  0x8000,
  0x4000,
  0x2000,
  0x1000,
  0x0800,
  0x0400,
  0x0200,
};
const uint8_t lengthFollow = sizeof(sequenceFollow)/sizeof(sequenceFollow[0]); // one step per LED in the circle
const uint16_t delayFollow = 50;

// Structure to hold sequence info
struct Sequence {
  const uint16_t* patterns;
  uint8_t length;
  uint16_t stepDelay;
};

// Add sequences here
const Sequence sequences[] = {
  { sequenceAllOn, lengthAllOn, delayAllOn },
  { sequenceFlashing, lengthFlashing, delayFlashing },
  { sequenceProgressive, lengthProgressive, delayProgressive },
  { sequenceChaser, lengthChaser, delayChaser },
  { sequenceProgressiveBack, lengthProgressiveBack, delayProgressiveBack },
  { sequenceBook, lengthBook, delayBook },
  { sequenceVBook, lengthVBook, delayVBook },
  { sequenceFollow, lengthFollow, delayFollow},
  { sequenceMsg, lengthMsg, delayMsg },
  { NULL, 1, 200}
};

const uint8_t SEQUENCE_COUNT = sizeof(sequences)/sizeof(sequences[0]);

// State variables
uint8_t currentSequence = 0;
uint8_t currentStep = 0;
unsigned long sequenceTimer = 0;

// Debounce variables
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 
bool lastButtonStableState = HIGH;  
bool lastButtonReading = HIGH;

void write16Bits(uint16_t value) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, (uint8_t)(value >> 8));
  shiftOut(dataPin, clockPin, MSBFIRST, (uint8_t)value);
  digitalWrite(latchPin, HIGH);
}

void resetCurrentSequence() {
  currentStep = 0;
  write16Bits(ALL_OFF); // Start from off
  sequenceTimer = millis();
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  randomSeed(analogRead(A0));
  
  write16Bits(ALL_OFF);
  resetCurrentSequence();
}

void loop() {
  unsigned long now = millis();

  // Debounce button
  bool buttonReading = digitalRead(buttonPin);
  if (buttonReading != lastButtonReading) {
    lastDebounceTime = now;
  }

  if ((now - lastDebounceTime) > debounceDelay) {
    if (buttonReading != lastButtonStableState) {
      lastButtonStableState = buttonReading;
      if (lastButtonStableState == LOW) {
        // Button pressed, change sequence
        currentSequence = (currentSequence + 1) % SEQUENCE_COUNT;
        resetCurrentSequence();
      }
    }
  }
  lastButtonReading = buttonReading;

  // Handle current sequence
  const Sequence &seq = sequences[currentSequence];
  if (seq.patterns == NULL) {
    // Random Sequence
    if (now - sequenceTimer >= seq.stepDelay) {
      sequenceTimer = now;
      uint16_t pattern = (uint16_t)random(0x10000); // full 16-bit random pattern
      write16Bits(pattern);
    }
  } else {
    // Handle normal sequences
    if (seq.length > 1) {
      if (now - sequenceTimer >= seq.stepDelay) {
        sequenceTimer = now;
        currentStep = (currentStep + 1) % seq.length;
        write16Bits(seq.patterns[currentStep]);
      }
    } else {
      // Single-step sequence (like All On)
      write16Bits(seq.patterns[0]);
    }
  }
}

