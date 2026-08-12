#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <Arduino.h>

// ============================================================================
// STRUCTURE DE DONNÉES CAPTEURS (PASSERELLE DE MESURE)
// ============================================================================
// Cette structure regroupe toutes les métriques collectées lors d'une mesure.
// Elle est transmise de manière uniforme entre les capteurs et le stockage.
struct SensorData {
    uint32_t timestamp;   // Temps UNIX (secondes depuis 1970) ou secondes depuis le boot
    float temperature;    // Température ambiante en degrés Celsius (°C)
    float humidity;       // Humidité relative de l'air en pourcentage (%)
    float soilMoisture;   // Humidité du sol en pourcentage (%)
    float batteryVoltage; // Tension de la batterie LiPo/LiFePO4 en Volts (V)
    bool valid;           // Indicateur de validité (true si tous les capteurs ont répondu)
};

// ============================================================================
// STRUCTURE DE CONFIGURATION SYSTÈME
// ============================================================================
// Stocke la configuration modifiable (ex: via la future interface Web).
struct SystemConfig {
    uint32_t sleepIntervalSec; // Intervalle de Deep Sleep dynamique
    float soilDryThreshold;    // Seuil d'alerte terre sèche (en %)
};

#endif // DATA_TYPES_H