#ifndef STORAGE_INTERFACE_H
#define STORAGE_INTERFACE_H

#include "data_types.h"

// ============================================================================
// INTERFACE ABSTRAITE DE STOCKAGE DE DONNÉES
// ============================================================================
// Abstraction permettant d'écrire les logs aussi bien dans la console Serie (Mock)
// que sur une vraie carte MicroSD au format CSV sans modifier le reste du code.
class StorageInterface {
public:
    virtual ~StorageInterface() {}

    // Prépare le support de stockage (ex: montage du système de fichiers FAT32)
    virtual bool begin() = 0;

    // Persiste une ligne de mesures dans le support
    virtual bool save(const SensorData &data) = 0;
};

#endif // STORAGE_INTERFACE_H