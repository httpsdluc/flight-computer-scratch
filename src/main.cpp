// The Boss's instructions for the whole flight

#include <Arduino.h>   // Basic robot toolkit
#include "altimeter.h" // Our special height instructions

// SETUP (What to do when we turn on)
void setup() {
    Serial.begin(115200); // Start talking to computer

    // Try waking up the height sensor
    if (!setupAltimeter()) {
        Serial.println("Altimeter initialization failed!"); // Uh oh!
        while (1); // Freeze and do nothing (like panicking)
    }

    Serial.println("Altimeter initialized successfully."); // Yay!
    calibrateGroundLevelPressure(); // Measure ground air pressure
}

// LOOP (What to do over and over during flight)
void loop() {
    static float last_altitude = readAltitude(); // Remember last height
    float altitude = readAltitude();             // Measure new height
    static int dropCount = 0;                   // Start "going down" counter at 0

    // Tell us the current height
    Serial.print("Altitude: ");
    Serial.println(altitude);

    // Check if it's time to pop parachute
    if (detect_apogee(altitude, last_altitude, &dropCount)) {
        Serial.println("Apogee detected! Deploying parachute."); // DECISION TIME!
        Serial.flush();  // Finish talking to computer
        deploy_parachute(); // POP!
        delay(5000);    // Wait 5 seconds so we don't pop twice
    }

    last_altitude = altitude; // Remember this height for next time
    delay(100); // Wait 1/10th second before checking again
}