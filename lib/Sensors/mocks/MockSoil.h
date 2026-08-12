#ifndef MOCK_SOIL_H
#define MOCK_SOIL_H

#include "../SensorInterface.h"

// ============================================================================
// SIMULATION CAPTEUR D'HUMIDITÉ DU SOL (CAPACITIF)
// ============================================================================
// Simule l'évaporation progressive de l'eau dans le terreau d'une plante.
class MockSoil : public SensorInterface {
private:
    float moisture = 80.0f; // Démarrage avec une terre bien arrosée (80%)

public:
    bool begin() override {
        Serial.println(F("[MOCK SOIL] Initialisation de la broche ADC virtuelle... OK"));
        return true;
    }

    // Simule le séchage de la terre au fil des cycles de mesure
    bool read(SensorData &data) override {
        // La terre perd 0.5% d'humidité à chaque réveil du système
        moisture -= 0.5f;

        // Simulation d'un arrosage automatique si le sol devient trop sec (< 15%)
        if (moisture < 15.0f) {
            Serial.println(F("[MOCK SOIL] 💦 Arrosage détecté ! Remise à niveau de l'humidité à 80%."));
            moisture = 80.0f;
        }

        data.soilMoisture = moisture;
        return true;
    }
};

#endif // MOCK_SOIL_H