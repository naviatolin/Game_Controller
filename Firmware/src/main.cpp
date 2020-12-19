#include "header.h"
#include "debounce.h"
#include "battery.h"
#include "joystick.h"
#include "accelerometer.h"

void setup()
{
  Serial.begin(9600);

  setupKeys();
  checkAllocation();
  setupJoystick();
  setupAccelerometer();
}

void loop()
{
  checkButton();
  Joystick();
  batteryDisplay();
  accelerometer();
}
