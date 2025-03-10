#include <Arduino.h>

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