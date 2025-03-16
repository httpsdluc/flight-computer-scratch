#include <Arduino.h>
#include "altimeter.h"

// when it boots up, it will run the setup function at least once
void setup() {
    Serial.begin(115200); // Start serial communication for debugging
    
    // Initialize the altimeter
    if (!setupAltimeter()) {
        Serial.println("Altimeter initialization failed!");
    } else {
        Serial.println("Altimeter initialized successfully.");
    }
    
    // Set ground level pressure for accurate altitude calculations
    calibrateGroundLevelPressure();
}

void loop() {
    // Read altitude from the altimeter
    float last_altitude = readAltitude();
    float altitude = readAltitude();
    
    Serial.print("Current Altitude: ");
    Serial.println(altitude);

    // Loop to detect apogee (highest point of flight)
    while (altitude >= last_altitude - 1) {
        last_altitude = altitude;
        altitude = readAltitude();
        Serial.print("Altitude: ");
        Serial.println(altitude);
    }

    // Once apogee is reached, deploy the parachute
    Serial.println("Apogee detected! Deploying parachute.");
    deploy_parachute();
    
    // Delay before restarting the loop to avoid multiple deployments
    delay(5000);
}

// Explanation:
// - `setup()` initializes the altimeter and verifies connection.
// - `calibrateGroundLevelPressure()` establishes a baseline pressure reading.
// - `loop()` continuously reads altitude and determines when apogee occurs.
// - Apogee is detected when altitude starts decreasing consistently.
// - When apogee is reached, `deploy_parachute()` is called to trigger parachute deployment.
// - Added `Serial.print` statements for debugging altitude readings.

/*
#include <Arduino.h> 
#include "altimeter.h"


// when it boots, up will run the setup function at least one
void setup() {

  // put your setup code here, to run once:
  // once power us uspplied to the board, the setup() function is called automatically

  // Initialization - What do we need to initialize?
  // set the altitude to 0
  // check that the altimiter is connected

  // print whether the altimeter is connected or not

  // Calibration - How does caliration work?
  // 



}

void loop() {
  // put your main code here, to run repeatedly:

  // read data
  // callibrate the data

  // read altitude from the altimeter
  // check what state of flight we're in 

  float last_altitude = sample_altimeter();
  float altitude = sample_altimeter();
  while (altitude >= last_altitude - 1){
    last_altitude = altitude;
    altitude = sample_altimeter();

  }

  deploy_parachute();

  // multiple decreases in a row
  // if altitude decrease in a certain amount (% or hardcoded value)

  // how do we determine if apogee has occurred?
  // if we're apogee deploy parachuete

  // only thing we have access to is altitude

  // if current altitude is lower than prior measurement, apogee has been reached

  // if agogee_has_been_reached, deploy parachute


}





// each file should be designated to each indiviual task
// should not be much branching 

*/