#ifndef DEBOUNCE
#define DEBOUNCE

/**
 * Set up each input pin that is connected to a button
 */
void setupKeys()
{
  for (int i = 0; i < 6; i++)
  {
    pinMode(swArray[i], INPUT_PULLUP);
  }

  Keyboard.begin();
}

/**
 * Read the current state of each switch.
 */
void readButtons()
{
  for (int i = 0; i < 6; i++)
  {
    swReading[i] = digitalRead(swArray[i]);
  }
}

/**
 * If the most recent reading is different from the last reading, start the debounce timer.
 */
void setDebounceTimer()
{
  for (int i = 0; i < 6; i++)
  {
    if (swReading[i] != lastswReading[i])
    {
      // switch the flag for the key to true
      activated[i] = true;
      debounceTimer[i] = millis();
    }
  }
}

/**
 * Check to see if any two keys have been activated if a combo flag isn't already HIGH.
 */
void checkCombo()
{
  if (activated[0] == true && activated[1] == true)
  {
    combo[0] = true;
  }
  else if (activated[2] == true && activated[3] == true)
  {
    combo[1] = true;
  }
  else if (activated[0] == true && activated[2] == true)
  {
    combo[2] = true;
  }
  else if (activated[1] == true && activated[3] == true)
  {
    combo[3] = true;
  }
}

/**
 * Code to debounce all 6 of the buttons
 */
void debounce()
{
  // if a combo flag is high
  if (combo[0] == true || combo[1] == true || combo[2] == true || combo[3] == true)
  {

    // button 1 and button 2 - just debounce button 1 - write 'F'
    if (combo[0] == true)
    {
      if ((millis() - debounceTimer[0]) > debounceThreshold)
      {
        if (swReading[0] != intState[0])
        {
          intState[0] = swReading[0];

          if (intState[0] == HIGH)
          {
            activated[0] = false;
            activated[1] = false;
            combo[0] = false;
            for (int k = 0; k < 10; k++)
            {
              Keyboard.press('f');
            }
          }
        }
      }
    }

    // button 3 and button 4 - just debounce button 3 - write 'Y'
    else if (combo[1] == true)
    {
      if ((millis() - debounceTimer[2]) > debounceThreshold)
      {
        if (swReading[2] != intState[2])
        {
          intState[2] = swReading[2];

          if (intState[2] == HIGH)
          {
            activated[2] = false;
            activated[3] = false;
            combo[1] = false;
            for (int k = 0; k < 10; k++)
            {
              Keyboard.press('y');
            }
          }
        }
      }
    }

    // button 1 and button 3 - just debounce button 1 - write 'Tab'
    else if (combo[2] == true)
    {
      if ((millis() - debounceTimer[0]) > debounceThreshold)
      {
        if (swReading[0] != intState[0])
        {
          intState[0] = swReading[0];

          if (intState[0] == HIGH)
          {
            activated[0] = false;
            activated[2] = false;
            combo[2] = false;
            for (int k = 0; k < 10; k++)
            {
              Keyboard.press(KEY_TAB);
            }
          }
        }
      }
    }

    // button 2 and button 4 - just debounce button 2 - write 'F'
    else if (combo[3] == true)
    {
      if ((millis() - debounceTimer[1]) > debounceThreshold)
      {
        if (swReading[1] != intState[1])
        {
          intState[1] = swReading[1];

          if (intState[1] == HIGH)
          {
            activated[1] = false;
            activated[3] = false;
            combo[3] = false;
            for (int k = 0; k < 10; k++)
            {
              Keyboard.press('f');
            }
          }
        }
      }
    }
  }

  // if a combo flag isn't high
  else
  {
    for (int i = 0; i < 6; i++)
    {
      // check if the time for the debounce has passed
      if ((millis() - debounceTimer[i]) > debounceThreshold)
      {

        // check if the current state is different from the intermediate state
        if (swReading[i] != intState[i])
        {
          // set the intermediate state equal to the prior reading
          intState[i] = swReading[i];

          // if the intermediate state is HIGH continue writing the keys
          if (intState[i] == HIGH)
          {

            // switch the flag for the key to false
            activated[i] = false;
            switch (i)
            {
            default:
              for (int k = 0; k < 10; k++)
              {
                Keyboard.press(keys[i]);
              }
              break;
            case 4:
              if (incrementer != 0)
              {
                incrementer -= 1;
                for (int k = 0; k < 10; k++)
                {
                  Keyboard.press(items[incrementer]);
                }
                break;
              }
            case 5:
              if (incrementer != 11)
              {
                incrementer += 1;
                for (int k = 0; k < 10; k++)
                {
                  Keyboard.press(items[incrementer]);
                }
                break;
              }
            }
          }
        }
      }
    }
  }
}

/**
 * set the current reading as the last reading before beginning the loop again
 */
void reassignStates()
{
  for (int i = 0; i < 6; i++)
  {
    lastswReading[i] = swReading[i];
  }
}

void releaseKeys()
{
  Keyboard.release('f');
  Keyboard.release('y');
  Keyboard.release(KEY_TAB);
  Keyboard.release('c');
  for (int i = 0; i < 6; i++)
  {
    Keyboard.release(keys[i]);
  }
  for (int i = 0; i < 12; i++)
  {
    Keyboard.release(items[i]);
  }
}

/**
 * Final loop to debounce all of the buttons.
 */
void checkButton()
{
  readButtons();
  setDebounceTimer();
  checkCombo();
  debounce();
  reassignStates();
  releaseKeys();
}

#endif
