#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>

// SPI1 Pin Definitions (adjust if needed)
#define BMP_CS     10  // Chip Select pin for BMP388
#define SPI1_SCK   27  // SPI1 Clock
#define SPI1_MISO  39  // SPI1 MISO
#define SPI1_MOSI  28  // SPI1 MOSI

// Define the altimeter object
extern Adafruit_BMP3XX altimeter;

// Ground-level pressure reference
extern double groundLevelPressure_hPa;

// Function to initialize the altimeter
bool setupAltimeter();

// Function to read altitude
float readAltitude();

// Function to set ground-level pressure before launch
void calibrateGroundLevelPressure();

// Function to deploy the parachute
void deploy_parachute();
