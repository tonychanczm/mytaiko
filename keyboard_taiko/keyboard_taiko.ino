#include "Keyboard.h"

int leftBlue = A3; // left-blue
int rightRed = A2; // right-red
int rightBlue = A1; // right-blue
int leftRed = A0; // left-red

const int pins[4] = {leftBlue, leftRed, rightRed, rightBlue};
const uint8_t pinKey[4] = {'d', 'f', 'j', 'k'};
const int requireForces[4] = {55, 55, 55, 55}; // 0~1023
const int filter[4] = {55, 55, 55, 55};
const int sampleNum = 13;
const int sens[4] = {3,4,4,3};
int tmpVal[4] = {0, 0, 0, 0};

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  int maxIndex = -1;
  int flag = 0;
  int maxVal = 0;
  for (int i = 0; i < 4; i++) {
    int pinVal = analogRead(pins[i]);
    if (pinVal > requireForces[i]) {
      flag = 1;
    }
    if (pinVal < filter[i]) {
      continue;  
    }
    tmpVal[i] = pinVal;
  }

  if (flag > 0) {
    for (int i = 0; i < sampleNum - 1; i++) {
      int pinVal = analogRead(pins[i]);
      if (pinVal < filter[i]) {
        continue;  
      }
      tmpVal[i] += pinVal;
    }
    maxIndex = 0;
    maxVal = tmpVal[0];
    for (int i = 1; i < 4; i++) {
      int pinVal = tmpVal[i] * sens[i];
      if (pinVal > maxVal) {
        maxIndex = i;
        maxVal = tmpVal[i];
      }
    }
    for (int i = 0; i < 4; i++) {
      tmpVal[i] = 0;
    }
  }
  
  // TODO Async keyboard control
  if (maxIndex != -1) {
    uint8_t key = pinKey[maxIndex];
    Keyboard.press(key);
    delay(20);
    Keyboard.release(key);
  }

}
