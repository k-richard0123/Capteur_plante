#include <Arduino.h>
#include "config.h"
#include "data_types.h"
#include "SystemManager/SystemManager.h"

// ============================================================================
// SELECTION CONDITIONNELLE DES COMPOSANTS (MOCK VS MATÉRIEL RÉEL)
// ============================================================================
#if USE_MOCK_SENSORS
#include "Sensors/mocks/MockSHT31.h"
#include "Sensors/mocks/MockSoil.h"
#include "Storage/MockStorage.h"

// Instanciation statique des objets fictifs (Mocks)
MockSHT31 sht31;
MockSoil soilSensor;
MockStorage storage;
#else
// Ici viendront les inclusions des vrais drivers (ex: #include <Adafruit_SHT31.h>)
#endif

// Gestionnaire du cycle de vie et de l'énergie
SystemManager sysManager;

// ============================================================================
// ARCHITECTURE BASSE CONSOMMATION : EXECUTION UNIQUE EN SETUP()
// ============================================================================
// Sur ESP32 en mode Deep Sleep, le microcontrôleur s'éteint complètement.
// À chaque réveil, il redémarre depuis le début et exécute setup().
// Le code s'exécute linéairement : Boot -> Mesure -> Stockage -> Endormissement.
void setup() {
    // Initialisation du port série pour la console de débogage
    Serial.begin(115200);
    
    // Attente du démarrage de la liaison série (max 2 secondes)
    while (!Serial && millis() < 2000); 

    // Initialisation du contrôleur d'alimentation
    sysManager.begin();
    
    Serial.println(F("\n========================================"));
    Serial.print(F("ESP32 Plant-Datalogger | Boot Cycle #"));
    Serial.println(sysManager.getBootCount());
    Serial.println(F("========================================"));

    // ------------------------------------------------------------------------
    // ÉTAPE 1 : Allumage logique des capteurs via le MOSFET
    // ------------------------------------------------------------------------
    sysManager.powerOnSensors();

    // ------------------------------------------------------------------------
    // ÉTAPE 2 : Initialisation des interfaces
    // ------------------------------------------------------------------------
    sht31.begin();
    soilSensor.begin();
    storage.begin();

    // ------------------------------------------------------------------------
    // ÉTAPE 3 : Lecture et agrégation des métriques
    // ------------------------------------------------------------------------
    SensorData currentData;
    currentData.timestamp = millis() / 1000; // Simulation d'horodatage
    
    // Prise de mesure sur la sonde SHT31
    sht31.read(currentData);
    
    // Prise de mesure sur la sonde de sol
    soilSensor.read(currentData);
    
    // Simulation d'une mesure de batterie (diviseur de tension sur ADC)
    currentData.batteryVoltage = 4.12f; 

    // ------------------------------------------------------------------------
    // ÉTAPE 4 : Coupure immédiate du rail 3.3V des capteurs
    // ------------------------------------------------------------------------
    // Réduit au strict minimum le temps d'allumage des périphériques
    sysManager.powerOffSensors();

    // ------------------------------------------------------------------------
    // ÉTAPE 5 : Sauvegarde des données (Carte SD / Log)
    // ------------------------------------------------------------------------
    storage.save(currentData);

    // ------------------------------------------------------------------------
    // ÉTAPE 6 : Extinction de l'ESP32 (Deep Sleep)
    // ------------------------------------------------------------------------
    sysManager.goToSleep();
}

// ============================================================================
// BOUCLE PRINCIPALE (INUTILISÉE EN DEEP SLEEP)
// ============================================================================
void loop() {
    // La boucle loop reste vide. L'ESP32 n'atteint jamais cette section en
    // fonctionnement réel car esp_deep_sleep_start() stoppe l'exécution du CPU.
}