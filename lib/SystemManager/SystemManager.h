#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <Arduino.h>
#include "config.h"

// ============================================================================
// GESTIONNAIRE SYSTÈME & BASSE CONSOMMATION
// ============================================================================
// Cette classe orchestre la mémoire persistante RTC, la coupure physique 
// des lignes d'alimentation et l'endormissement de l'ESP32.
class SystemManager {
public:
    // Initialise les broches d'alimentation et incrémente le compteur de boot
    void begin();

    // Gestion du compteur de réveils
    void incrementBootCount();
    uint32_t getBootCount();

    // Contrôle du MOSFET de coupure d'énergie des capteurs
    void powerOnSensors();
    void powerOffSensors();

    // Lance le processus d'extinction du SOC ESP32
    void goToSleep();
};

#endif // SYSTEM_MANAGER_H