#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// COMMUTATEURS DE SIMULATION (MOCK_MODE)
// ============================================================================
// Mettre à 1 pour développer/tester sur console sans aucun matériel branché.
// Mettre à 0 une fois les vrais capteurs I2C/SPI et la carte SD câblés.
#define USE_MOCK_SENSORS 1
#define USE_MOCK_STORAGE 1

// ============================================================================
// CONFIGURATION DE LA GESTION D'ÉNERGIE (DEEP SLEEP)
// ============================================================================
// Durée pendant laquelle l'ESP32 s'endort entre deux prises de mesure (en secondes).
// En mode Mock/PC, cette durée est simulée via un simple delay().
#define SLEEP_DURATION_SEC 15

// ============================================================================
// CARTOGRAPHIE DES BROCHES (PINOUT ESP32)
// ============================================================================
// Broche ADC1_CH0 (GPIO 34) : Lecture de la tension du capteur d'humidité capacitif.
// Utiliser impérativement ADC1 (GPIO 32-39) si le WiFi est activé plus tard.
#define PIN_SOIL_ADC 34

// Broche GPIO 23 : Commande de la grille (Gate) d'un MOSFET P-Channel ou N-Channel.
// Permet de couper complètement l'alimentation 3.3V des capteurs en Deep Sleep.
#define PIN_SENSORS_POWER 23

// Broche GPIO 5 : Chip Select (CS) du lecteur de carte MicroSD sur le bus SPI.
#define PIN_SD_CS 5

#endif // CONFIG_H