#include <Arduino.h>
#include "i2cscanner.h"

#define SERIAL_SPEED 115200;

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println(F("I2C scanner"));
}

void loop() {
  i2c_scan();
  delay(1000);
}
