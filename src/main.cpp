#include <Arduino.h>
#include "altimeter.h"

void setup() {
    Serial.begin(115200);

    if (!setupAltimeter()) {
        Serial.println("Altimeter initialization failed!");
        while (1); // Halt if failed
    }

    Serial.println("Altimeter initialized successfully.");
    calibrateGroundLevelPressure();
}

void loop() {
    float last_altitude = readAltitude();
    float altitude = last_altitude;

    int dropCount = 0;
    const int requiredDrops = 3;

    while (dropCount < requiredDrops) {
        last_altitude = altitude;
        altitude = readAltitude();

        Serial.print("Altitude: ");
        Serial.println(altitude);

        if (altitude < last_altitude - 1) {
            dropCount++;
        } else {
            dropCount = 0;
        }

        delay(100);
    }

    Serial.println("Apogee detected! Deploying parachute.");
    Serial.flush();
    deploy_parachute();

    delay(5000);  // Prevent re-deployment
}
