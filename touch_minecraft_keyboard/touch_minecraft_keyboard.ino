#include <Keyboard.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

const int num_keys = 9;
const int repeat_rate = 150;

int keys[num_keys] = {113 /*q*/, 119 /*w*/, 101 /*e*/, 97 /*a*/, 115 /*s*/, 100 /*d*/,  32 /* */, 102 /*f*/, 129 /*L-SHIFT*/};
bool key_pressed[num_keys] = {0, 0, 0, 0, 0, 0};
Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  // Serial.begin(115200);
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
}

void loop() {
  currtouched = cap.touched();
  for (uint8_t i = 0; i < num_keys; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if (keys[i] <= 128) {
        key_pressed[i] = true;
      } else {
        Keyboard.press(keys[i]);
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      if (keys[i] <= 128) {
        key_pressed[i] = false;
      } else {
        Keyboard.release(keys[i]);
      }
    }
    if (key_pressed[i]) {
      Keyboard.write(keys[i]);
    }
  }

  // reset our state
  lasttouched = currtouched;

  // put a delay so it isn't overwhelming
  delay(repeat_rate);
}
