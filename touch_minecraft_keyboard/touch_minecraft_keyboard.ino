#include <Keyboard.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

const int num_keys = 6;
const int repeat_rate = 100;

int keys[num_keys] = {119 /*w*/, 97 /*a*/, 115 /*s*/, 100 /*d*/, 129 /*L-SHIFT*/, 32 /* */};
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
//      Serial.print(keys[i]);
//      Serial.println(" key pressed");
      Keyboard.write(keys[i]);
      delay(repeat_rate);
    }
  }

  // reset our state
  lasttouched = currtouched;

  // put a delay so it isn't overwhelming
  delay(1);
}
