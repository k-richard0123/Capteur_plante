#ifndef MOCK_STORAGE_H
#define MOCK_STORAGE_H

#include "StorageInterface.h"

// ============================================================================
// SIMULATION DE STOCKAGE CARTE SD (AFFICHAGE CONSOLE)
// ============================================================================
// Formate les données sous forme de ligne CSV claire et les affiche sur l'UART.
class MockStorage : public StorageInterface {
public:
    bool begin() override {
        Serial.println(F("[MOCK SD] Montage du système de fichiers virtuel SD... OK"));
        return true;
    }

    // Formate et affiche la ligne de log
    bool save(const SensorData &data) override {
        Serial.println(F("--- [MOCK SD LOG] Écriture de la ligne CSV ---"));
        
        // Structure CSV : Timestamp ; Temp ; HumAir ; HumSol ; TensionBat
        Serial.print(F("DATA;"));
        Serial.print(data.timestamp); Serial.print(F(";"));
        Serial.print(data.temperature, 2); Serial.print(F(";"));
        Serial.print(data.humidity, 2); Serial.print(F(";"));
        Serial.print(data.soilMoisture, 2); Serial.print(F(";"));
        Serial.println(data.batteryVoltage, 2);
        
        Serial.println(F("---------------------------------------------"));
        return true;
    }
};

#endif // MOCK_STORAGE_H