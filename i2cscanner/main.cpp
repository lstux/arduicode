#include <Arduino.h>
#include <Wire.h>
#include "i2caddresses.h"

#define SERIAL_SPEED 115200;
//#define PIN_I2CSDA 21
//#define PIN_I2CSCL 22

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println(F("I2C scanner"));
#ifdef PIN_I2CSDA
  Wire.begin(PIN_I2CSDA, PIN_I2CSCL);
#endif
}

void loop() {
  int e;
  Serial.println(F("Scanning I2C bus..."));
  for (byte addr=1; addr<127; addr++) {
    Wire.beginTransmission(addr);
    e = Wire.endTransmission();
    switch(e) {
      case(0): Serial.printf("\n   x%02X %s\n", addr, i2caddresses[addr]); break;
      case(2): Serial.print(".");
      default: Serial.printf("\n  !x%02X Unknown error (%d)\n", addr, e); break;
    }
  }
  Serial.println();
  delay(10000);
}
