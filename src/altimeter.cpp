// This is the robot's brain with all the actual instructions

#include "altimeter.h"  // Get our instruction book

// Our tools:
Adafruit_BMP3XX altimeter;                     // The height-measurer
double groundLevelPressure_hPa = 1013.25;      // Normal sea-level air pressure
#define PARACHUTE_PIN 10                       // Parachute button is on pin 10

// WAKE UP THE HEIGHT SENSOR
bool setupAltimeter() {
    Serial.begin(115200);  // Start talking to computer (fast speed)
    
    // Check if height sensor is plugged in
    if (!altimeter.begin_SPI(BMP_CS, SPI1_SCK, SPI1_MISO, SPI1_MOSI)) {
        Serial.println("Altimeter not found! Check wiring."); // Cry for help
        return false;
    }

    // Set how carefully to measure:
    altimeter.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);       // Don't overwork
    altimeter.setPressureOversampling(BMP3_OVERSAMPLING_2X);          // Double-check pressure
    altimeter.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);             // Smooth measurements
    altimeter.setOutputDataRate(BMP3_ODR_100_HZ);                     // Check 100x per second

    // Prepare parachute button
    pinMode(PARACHUTE_PIN, OUTPUT);    // Make pin 10 a "push button"
    digitalWrite(PARACHUTE_PIN, LOW);  // Start with button not pushed

    Serial.println("Altimeter setup complete."); // Success!
    calibrateGroundLevelPressure();    // Measure ground air pressure
    return true;
}

// ASK "HOW HIGH ARE WE NOW?"
float readAltitude() {
    if (!altimeter.performReading()) {          // If sensor isn't answering
        Serial.println("Failed to read from altimeter"); // Say "I can't hear you!"
        return -1.0;                           // Return error number
    }
    return altimeter.readAltitude(groundLevelPressure_hPa); // Calculate height
}

// MEASURE GROUND AIR PRESSURE
void calibrateGroundLevelPressure() {
    double pressureSum = 0;                    // Start counting at zero
    
    // Take 100 measurements (like counting to 100 slowly)
    for (int i = 0; i < 100; i++) {
        if (altimeter.performReading()) {      // If measurement worked
            pressureSum += altimeter.pressure / 100.0; // Add to our total
        }
        delay(10); // Wait 1/100th of a second between measurements
    }
    
    groundLevelPressure_hPa = pressureSum;     // Save the average
    Serial.print("Calibrated Ground Level Pressure: ");
    Serial.println(groundLevelPressure_hPa);   // Tell us the number
}

// POP THE PARACHUTE!
void deploy_parachute() {
    Serial.println("Activating parachute...");  // Say what we're doing
    digitalWrite(PARACHUTE_PIN, HIGH);         // Push the button (send electricity)
    delay(1000);                               // Keep it pushed for 1 second
    digitalWrite(PARACHUTE_PIN, LOW);          // Let go of the button
    Serial.println("Parachute deployed.");     // Confirm it's done
}

// IS IT TIME TO POP? (Apogee detector)
bool detect_apogee(float current_altitude, float last_altitude, int* drop_count, int required_drops) {
    // If we're going down more than 1 meter:
    if (current_altitude < last_altitude - 1.0f) {
        (*drop_count)++;  // Add 1 to our "going down" counter
    } else {
        *drop_count = 0;  // Reset counter if we're not going down
    }
    // If we've gone down enough times in a row, say "POP NOW!"
    return (*drop_count >= required_drops);
}