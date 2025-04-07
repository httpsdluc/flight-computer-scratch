// This is like the cover of our instruction book
#ifndef ALTIMETER_H  
#define ALTIMETER_H

// Include the special height-measuring tool manual
#include <Adafruit_BMP3XX.h>

// WIRING DIAGRAM (where to plug the wires)
#define BMP_CS 10       // Plug the white wire into hole #10 (like a "talk button")
#define SPI1_SCK 13     // Plug the yellow wire into hole #13 (clock signal)
#define SPI1_MISO 12    // Plug the green wire into hole #12 (sensor talking to computer)
#define SPI1_MOSI 11    // Plug the blue wire into hole #11 (computer talking to sensor)

// Our two special tools we'll use everywhere:
extern Adafruit_BMP3XX altimeter;          // The height-measuring robot
extern double groundLevelPressure_hPa;     // Remembers air pressure at ground level

// LIST OF WHAT OUR ROBOT CAN DO:
bool setupAltimeter();                     // Wake up the height sensor
float readAltitude();                      // Ask "how high are we?"
void calibrateGroundLevelPressure();       // Measure ground air pressure
void deploy_parachute();                   // POP the parachute!
bool detect_apogee(float current, float last, int* drops, int needed=3); // Is it time to pop?

// End of the instruction book
#endif