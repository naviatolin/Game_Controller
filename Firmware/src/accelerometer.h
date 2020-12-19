#ifndef ACCELEROMETER
#define ACCELEROMETER
/**
 * Set up accelerometer. 
*/
void setupAccelerometer()
{
  display.clearDisplay();
  lis.setRange(LIS3DH_RANGE_4_G);
  lis.setClick(1, CLICKTHRESHHOLD);
}

/**
 * Check to see if the accelerometer is being moved to trigger an action in Stardew Valley.
*/
void accelerometer()
{
  uint8_t click = lis.getClick();
  if (click & 0x10)
  {
    for (int i = 0; i < 10; i++)
    {
      Keyboard.press('c');
    }
    Keyboard.release('c');
  }
  return;
}

#endif
