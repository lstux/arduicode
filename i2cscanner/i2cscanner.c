#include "i2cscanner.h"

//https://learn.adafruit.com/i2c-addresses/the-list
char *i2c_addr2name(byte addr) {
  char *name = (char *)calloc(32, 1);
  if (!strcmp("", i2caddresses[addr])) strcpy(name, "Unknown device");
  else strcpy(name, i2caddresses[addr]);
  return name;
}

void i2c_scan() {
  int e;
  Serial.println(F("Scanning I2C bus..."));
  for (byte addr=1; addr<127; addr++) {
    Wire.beginTransmission(addr);
    e = Wire.endTransmission();
    switch(e) {
      case(0): Serial.printf("\n   x%02X %s\n", addr, i2c_addr2name(addr)); break;
      case(2): Serial.print(".");
      default: Serial.printf("\n  !x%02X Unknown error (%d)\n", addr, e); break;
    }
  }
  Serial.println();
}
