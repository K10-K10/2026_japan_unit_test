#include "usonicio.hpp"
#include <Arduino.h>

constexpr int trig1 = 18, echo1 = 19;
constexpr int trig2 = 33, echo2 = 23;
constexpr int trig3 = 26, echo3 = 27;

UltrasonicIO u1(trig1, echo1);
UltrasonicIO u2(trig2, echo2);
UltrasonicIO u3(trig3, echo3);

long values[3] = {0, 0, 0};
int idx = 0;

void setup() {
  Serial.begin(115200);
  u1.init();
  u2.init();
  u3.init();
}

void loop() {
  if (idx == 0)
    u1.readUsonic(values + 0);
  else if (idx == 1)
    u2.readUsonic(values + 1);
  else if (idx == 2)
    u3.readUsonic(values + 2);

  idx = (idx + 1) % 3;

  Serial.printf("U1:%ld U2:%ld U3:%ld\n", values[0], values[1], values[2]);

  delay(100);
}
