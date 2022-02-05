#include <USB-MIDI.h>

USBMIDI_CREATE_DEFAULT_INSTANCE();

int leftBlue = A0; // left-blue
int rightRed = A1; // right-red
int rightBlue = A2; // right-blue
int leftRed = A3; // left-red

int pins[4] = {leftBlue, leftRed, rightRed, rightBlue};
uint8_t pinKey[4] = {40, 41, 42, 43};
int requireForces[4] = {80, 80, 80, 80}; // 0~1023

void setup() {
  MIDI.begin();
}

void loop() {
  int maxIndex = -1;
  int maxVal = 0;
  for (int i = 0; i < 4; i++) {
    int pinVal = analogRead(pins[i]);
    if (pinVal > requireForces[i] && pinVal > maxVal) {
      maxIndex = i;
      maxVal = pinVal;
    }
  }
  
  // TODO Async keyboard control
  if (maxIndex != -1) {
    uint8_t key = pinKey[maxIndex];
    MIDI.sendNoteOn(key, 127, 1);
    delay(30);
  }

}
