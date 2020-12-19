#ifndef GLOBAL_VAR
#define GLOBAL_VAR

#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// DEBOUNCE VARIABLES
// set up switch pins
int swArray[6] = {13, 12, 11, 10, 5, 6};

// reading variables
int swReading[6];

// intermediate button states
int intState[6];

// past state of each button set to HIGH intiially
int lastswReading[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

// debounce timer
unsigned long debounceTimer[6];

// threshold for debouncing
unsigned long debounceThreshold = 50;

// keys to press
int keys[6] = {'c', 'x', 'e', 'm', 0, 0};

int keyDelay = 500;

// setting up the variable that incrments and what it increments between
int items[12] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '='};
int incrementer = 0;

bool activated[6] = {false, false, false, false, false, false};
bool combo[4] = {false, false, false, false};


// BATTERY VARIABLES
#define VBATPIN A9
float measuredvbat = analogRead(VBATPIN);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// JOYSTICK VARIABLES
int joyPins1 [2] = {A0, A1};
int joyPins2 [2] = {A3, A4};

float joy1[2];
float joy2[2];

int select1;
int select2;

int distance[2];
int reading;
int movement;

int mouse_range = 12;
int mouse_responseDelay = 5;
int mouse_threshold = 3;
int mouse_center = 6;  

// ACCELEROMETER VARIABLES
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
sensors_event_t event;
int prevLis;
#define CLICKTHRESHHOLD 80

#endif
