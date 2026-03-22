#include <Arduino.h>

constexpr int buttonPin = 25;

inline const char *buttonStateToString()
{
  return digitalRead(buttonPin) == HIGH ? "HIGH" : "LOW";
}

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  Serial.print("Button state: ");
  Serial.println(buttonStateToString());
  delay(1000);
}
