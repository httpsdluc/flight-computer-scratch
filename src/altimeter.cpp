#include "altimeter.h"

// Define the ground-level pressure variable
double groundLevelPressure_hPa = 1013.25; // Default sea level pressure

// Initialize the altimeter
bool setupAltimeter() {
    Serial.begin(115200);
    if (!altimeter.begin_SPI(BMP_CS, SPI1_SCK, SPI1_MISO, SPI1_MOSI)) {
        Serial.println("Altimeter not found! Check wiring.");
        return false;
    }

    // Configure sensor settings
    altimeter.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
    altimeter.setPressureOversampling(BMP3_OVERSAMPLING_2X);
    altimeter.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    altimeter.setOutputDataRate(BMP3_ODR_100_HZ);
    
    Serial.println("Altimeter setup complete.");
    calibrateGroundLevelPressure();
    return true;
}

// Read altitude from the altimeter
float readAltitude() {
    if (!altimeter.performReading()) {
        Serial.println("Failed to read from altimeter");
        return -1.0;
    }
    return altimeter.readAltitude(groundLevelPressure_hPa);
}

// Calibrate ground-level pressure before flight
void calibrateGroundLevelPressure() {
    double pressureSum = 0;
    for (int i = 0; i < 100; i++) {
        if (altimeter.performReading()) {
            pressureSum += altimeter.pressure / 100.0;
        }
        delay(10);
    }
    groundLevelPressure_hPa = pressureSum / 100.0;
    Serial.print("Calibrated Ground Level Pressure: ");
    Serial.println(groundLevelPressure_hPa);
}
