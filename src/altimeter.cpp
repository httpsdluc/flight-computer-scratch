#include "altimeter.h"

Adafruit_BMP3XX altimeter;
double groundLevelPressure_hPa = 1013.25; // Default sea level pressure

#define PARACHUTE_PIN 10

bool setupAltimeter() {
    Serial.begin(115200);
    if (!altimeter.begin_SPI(BMP_CS, SPI1_SCK, SPI1_MISO, SPI1_MOSI)) {
        Serial.println("Altimeter not found! Check wiring.");
        return false;
    }

    altimeter.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
    altimeter.setPressureOversampling(BMP3_OVERSAMPLING_2X);
    altimeter.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    altimeter.setOutputDataRate(BMP3_ODR_100_HZ);

    pinMode(PARACHUTE_PIN, OUTPUT);
    digitalWrite(PARACHUTE_PIN, LOW);

    Serial.println("Altimeter setup complete.");
    calibrateGroundLevelPressure();
    return true;
}

float readAltitude() {
    if (!altimeter.performReading()) {
        Serial.println("Failed to read from altimeter");
        return -1.0;
    }
    return altimeter.readAltitude(groundLevelPressure_hPa);
}

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

void deploy_parachute() {
    Serial.println("Activating parachute...");
    digitalWrite(PARACHUTE_PIN, HIGH);
    delay(1000);  // Activate deployment mechanism for 1 second
    digitalWrite(PARACHUTE_PIN, LOW);
    Serial.println("Parachute deployed.");
}
