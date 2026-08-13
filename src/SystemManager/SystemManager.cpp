#include "SystemManager/SystemManager.h"

// ============================================================================
// MÉMOIRE RTC PERSISTANTE ENTRE DEUX DEEP SLEEPS
// ============================================================================
// L'attribut 'RTC_DATA_ATTR' place cette variable dans la SRAM RTC de l'ESP32.
// Cette zone reste sous tension minimale pendant le Deep Sleep, ce qui permet
// de conserver sa valeur sans devoir écrire dans la mémoire Flash (économise l'usure).
RTC_DATA_ATTR static uint32_t bootCounter = 0;

void SystemManager::begin() {
    // Configuration de la broche GPIO de commande d'alimentation en sortie
    pinMode(PIN_SENSORS_POWER, OUTPUT);
    
    // Incrémentation du compteur de cycle de vie à chaque sortie de veille
    incrementBootCount();
}

void SystemManager::incrementBootCount() {
    bootCounter++;
}

uint32_t SystemManager::getBootCount() {
    return bootCounter;
}

void SystemManager::powerOnSensors() {
    // Saturation du MOSFET : alimentation envoyée vers le rail VCC des capteurs
    digitalWrite(PIN_SENSORS_POWER, HIGH);
    Serial.println(F("[POWER] Rail 3.3V capteurs : ALLUMÉ"));
    
    // Temps de stabilisation électrique requis par les condensateurs des capteurs
    delay(10); 
}

void SystemManager::powerOffSensors() {
    // Blocage du MOSFET : découplage physique total des capteurs de la batterie
    // Annule tout courant de fuite (leakage current) résiduel pendant le sommeil.
    digitalWrite(PIN_SENSORS_POWER, LOW);
    Serial.println(F("[POWER] Rail 3.3V capteurs : ÉTEINT (0mA)"));
}

void SystemManager::goToSleep() {
    Serial.print(F("[SYSTEM] Activation du Deep Sleep pour "));
    Serial.print(SLEEP_DURATION_SEC);
    Serial.println(F(" secondes..."));
    
    // Attendre la fin de la transmission Série avant de couper les horloges du processeur
    Serial.flush();

#if USE_MOCK_SENSORS
    // Mode Simulation (PC/Moniteur Serie) : On simule l'extinction par une attente passive
    delay(SLEEP_DURATION_SEC * 1000);
#else
    // Mode Matériel ESP32 Réel :
    // 1. Définition de la source de réveil (Timer RTC en microsecondes)
    esp_sleep_enable_timer_wakeup(SLEEP_DURATION_SEC * 1000000ULL);
    
    // 2. Extinction complète des cœurs CPU, du WiFi, du Bluetooth et des bus d'horloge
    esp_deep_sleep_start();
#endif
}