#ifndef MOCK_SHT31_H
#define MOCK_SHT31_H

#include "../SensorInterface.h"

// ============================================================================
// SIMULATION CAPTEUR SHT31 (TEMPÉRATURE & HUMIDITÉ AIR)
// ============================================================================
// Simule le comportement d'une sonde I2C Sensirion SHT31 sans matériel.
class MockSHT31 : public SensorInterface {
private:
    float currentTemp = 21.5f; // Température de départ simulée (°C)
    float currentHum = 55.0f;  // Humidité de l'air de départ simulée (%)

public:
    // Simule la détection du composant sur le bus I2C
    bool begin() override {
        Serial.println(F("[MOCK SHT31] Détection virtuelle de la sonde I2C (Adresse 0x44)... OK"));
        return true; 
    }

    // Génère des données de température/humidité avec un bruit aléatoire réaliste
    bool read(SensorData &data) override {
        // Ajoute un petit décalage aléatoire (-0.5°C à +0.4°C)
        currentTemp += ((rand() % 10) - 5) * 0.1f;
        
        // Ajoute une petite fluctuation d'humidité (-1.0% à +0.8%)
        currentHum += ((rand() % 10) - 5) * 0.2f;

        // Bornage des valeurs dans des limites physiques plausibles
        if (currentTemp < 15.0f) currentTemp = 15.0f;
        if (currentTemp > 35.0f) currentTemp = 35.0f;
        if (currentHum < 30.0f) currentHum = 30.0f;
        if (currentHum > 90.0f) currentHum = 90.0f;

        // Écriture directe dans la structure partagée
        data.temperature = currentTemp;
        data.humidity = currentHum;

        return true;
    }
};

#endif // MOCK_SHT31_H