#ifndef WASD_JOYSTICK
#define WASD_JOYSTICK

/**
 * Setup the joysticks.
 */
void setupJoystick()
{
    for (int i = 0; i < 2; i++)
    {
        pinMode(joyPins1[i], INPUT_PULLUP);
    }
    for (int i = 0; i < 2; i++)
    {
        pinMode(joyPins2[i], INPUT_PULLUP);
    }

    // joystick select pins
    pinMode(20, INPUT_PULLUP);
    pinMode(23, INPUT_PULLUP);

    // start mouse
    Mouse.begin();
}

/**
 * Read values from the joysticks.
 */
void readJoystick()
{
    for (int i = 0; i < 2; i++)
    {
        joy1[i] = analogRead(joyPins1[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        joy2[i] = analogRead(joyPins2[i]);
    }
    // joystick 1 select
    select1 = digitalRead(20);

    // joystick 2 select
    select2 = digitalRead(23);
}

/**
 * Input WASD based on joystick 1.
 */
void WASD()
{
    if (joy1[1] < 20)
    {
        Keyboard.release('w');
        Keyboard.press('s');
    }
    else if (joy1[1] > 1000)
    {
        Keyboard.release('s');
        Keyboard.press('w');
    }
    else
    {
        Keyboard.release('s');
        Keyboard.release('w');
    }

    if (joy1[0] < 20)
    {
        Keyboard.release('d');
        Keyboard.press('a');
    }
    else if (joy1[0] > 1000)
    {
        Keyboard.release('a');
        Keyboard.press('d');
    }
    else
    {
        Keyboard.release('a');
        Keyboard.release('d');
    }
}

/**
 * Calculate the amount of movement of the mouse based on joystick 2.
 */
void calculateMovement()
{
    for (int i = 0; i < 2; i++)
    {
        reading = map(joy2[i], 0, 1023, 0, 12);
        movement = reading - mouse_center;

        if (abs(movement) < mouse_threshold)
        {
            distance[i] = 0;
        }
        else
        {
            distance[i] = movement;
        }
    }
}

/**
 * Move the mouse nonlinearly based on input from joystick 2. 
 */
void mouse()
{
    for (int i = 0; i < 2; i++)
    {
        if (distance[i] > 0)
            distance[i] = (int)pow(1.35, distance[i]);
        else if (distance[i] < 0)
            distance[i] = -(int)pow(1.35, -distance[i]);
    }

    Mouse.move(distance[0], -distance[1], 0);
}

/**
 * Click the mouse based on input from joystick 2.
 */
void mouseClick()
{
    if (select2 == LOW)
    {
        Mouse.press(MOUSE_LEFT);
    }
    else
    {
        Mouse.release(MOUSE_LEFT);
    }
}

/**
 * Final loop for both joystick's functionality.
 */
void Joystick()
{
    readJoystick();
    WASD();
    calculateMovement();
    mouse();
    mouseClick();
}

#endif