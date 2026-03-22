#include "armio.hpp"
#include <Arduino.h>

ARMIO arm(17, 34, 19);

constexpr int targets[] = {
    1000,
    1720,
    3072,
    1720,
    1000,
};

constexpr int target_count = sizeof(targets) / sizeof(targets[0]);

int index_pos = 0;
bool wire = true;
unsigned long last_update_time = 0;

void setup()
{
  Serial.begin(115200);
  if (!arm.init_pwm())
  {
    Serial.println("Failed to initialize PWM for arm control.");
    while (true)
    {
      // Halt execution if initialization fails
    }
  }

  arm.arm_set_position(targets[index_pos], wire);
  last_update_time = millis();
}

void loop()
{
  arm.updatePID();
  unsigned long current_time = millis();
  if (current_time - last_update_time >= 3000)
  {
    index_pos++;
    if (index_pos >= target_count)
    {
      index_pos = 0;
      wire = !wire; // Toggle wire state after completing a cycle
    }
    arm.arm_set_position(targets[index_pos], wire);

    Serial.print("target: ");
    Serial.print(targets[index_pos]);
    Serial.print(" wire: ");
    Serial.println(wire);
    Serial.print("current: ");
    Serial.println(arm.getCurrentPosition());

    last_update_time = millis();
  }
}
