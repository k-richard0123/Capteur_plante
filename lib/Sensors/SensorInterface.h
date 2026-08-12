#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include "data_types.h"

// ============================================================================
// INTERFACE ABSTRAITE DES CAPTEURS (POLYMORPHISME C++)
// ============================================================================
// Cette classe purement virtuelle définit le "contrat" que tout capteur doit respecter.
// Qu'il s'agisse d'un vrai SHT31, d'un capteur capacitif ou d'un Mock, ils héritent tous d'ici.
class SensorInterface {
public:
    // Destructeur virtuel obligatoire pour éviter les fuites mémoire à la destruction
    virtual ~SensorInterface() {}

    // Méthode d'initialisation du composant (ex: initialisation du bus I2C)
    // Retourne true si le matériel répond correctement, false sinon.
    virtual bool begin() = 0;

    // Méthode de lecture des valeurs physiques.
    // Remplit la structure SensorData passée par référence (&).
    virtual bool read(SensorData &data) = 0;
};

#endif // SENSOR_INTERFACE_H