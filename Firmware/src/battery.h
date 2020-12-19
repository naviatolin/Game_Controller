#ifndef BATTERY
#define BATTERY

/**
 * Calculate battery voltage
 */
int batteryVoltage()
{
  measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;   // multiply by 2 due to the voltage divider
  measuredvbat *= 3.3; // multiply by reference voltage
  measuredvbat /= 1024;
  return measuredvbat;
}

/**
 * Setup for the OLED display.
 */
void checkAllocation()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(("SSD1306 allocation failed"));
    for (;;)
      ;
  }
}

/**
 * Display the battery voltage on the OLED display.
 */
void batteryDisplay()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(batteryVoltage());
  display.display();
}

#endif