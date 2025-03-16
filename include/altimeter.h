#pragma once

#include <Arduino.h>
#include <Adafruit_BMP3XX.h>

// Define the altimeter object
Adafruit_BMP3XX altimeter;

// Ground-level pressure reference
extern double groundLevelPressure_hPa;

// Function to initialize the altimeter
bool setupAltimeter();

// Function to read altitude
float readAltitude();

// Function to set ground-level pressure before launch
void calibrateGroundLevelPressure();
