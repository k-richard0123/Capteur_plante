# Capteur pour Plante
Un boîtier autonome sur pile qui mesure la température/l’humidité toutes les X minutes, se rendort entre les mesures, et stocke les données (carte SD) ou les envoie par radio.

### Description
Doit servir dans un vivarium ou un pot de plante ou juste dans la terre. L'objectif est que n'importe qui puisse y mettre des valeurs en tant qu'objectifs avec un delta et que l'appareil prévienne quand on est en dehors de ces valeurs et comment y arriver. 

## Cahier des Charges

  - Capter l'humidité dans l'air
  - Capter l'humidité dans la terre
  - Capter la température de l'air
  - Doit faire des mesures toutes x minutes (réglable avec info sur la consommation des piles)

# Plan du Projet

## Étape 1 — Choix du microcontrôleur

Prends un ESP32 (pas un simple ATtiny), même si pour l'instant tu ne fais que du logging. Raison : le WiFi/BLE est déjà intégré, donc quand tu voudras ajouter l'interface de réglage plus tard, tu n'auras pas à changer de carte ni de code de base — juste à activer une fonctionnalité déjà présente sur le chip. Ça évite de refaire le projet de zéro.

## Étape 2 — Composants à commander
ESP32 (carte de dev type ESP32-DevKitC, ~8€)
Capteur d'humidité du sol capacitif (pas résistif — les résistifs se corrodent en quelques semaines en terre humide)
Capteur température/humidité air : SHT31 ou DHT22
Module RTC (DS3231) pour horodater les mesures même pendant le deep sleep
Carte microSD + lecteur, ou utiliser la flash interne de l'ESP32 si tu veux éviter la SD
Batterie LiPo 18650 ou pack + module de charge/protection (TP4056)
Boîtier étanche (boîte IP65, ou tu imprimes en 3D si tu as accès à une imprimante)

Budget total estimé: 25-40€.

## Étape 3 — Prototype sur breadboard

Assemble tout à l'air libre, sans souci d'étanchéité. Objectif : que chaque capteur donne des valeurs cohérentes et que tu saches lire du I2C (RTC, éventuellement SHT31) et de l'analogique (capteur sol). Calibre le capteur d'humidité du sol : mesure la valeur "air sec" et "eau" pour avoir tes bornes de référence.

## Étape 4 — Firmware, avec l'extensibilité en tête dès le départ

C'est l'étape la plus importante pour ton objectif de "pouvoir construire dessus plus tard". Structure ton code en modules séparés dès maintenant, même si un seul module sert aujourd'hui :

capteurs.c/h : lecture des capteurs, indépendant du reste
stockage.c/h : écriture des mesures horodatées (SD ou flash)
config.c/h : un petit fichier de configuration (JSON ou simple struct) stocké en mémoire flash — seuils, intervalle de mesure, etc. Même si rien ne le modifie pour l'instant, prévoir cette couche te fera gagner des semaines plus tard : le jour où tu ajoutes une interface web, elle n'aura qu'à écrire dans ce fichier de config, sans toucher au reste du firmware.
power.c/h : gestion du deep sleep entre les mesures (c'est ce qui fait ton autonomie)

Le programme principal : réveil → lecture capteurs → écriture horodatée → dodo. Simple, mais avec cette séparation, chaque brique est réutilisable.

## Étape 5 — Boîtier et étanchéité (spécifique pot/vivarium)
Électronique (ESP32, batterie, RTC) : dans un boîtier étanche IP65, hors du sol/de l'humidité directe, posé en surface ou fixé au bord du pot/vivarium
Seul le capteur d'humidité du sol va en terre — vérifie qu'il est bien conçu pour ça (capacitif = enrobé, pas de contacts métalliques nus)
Passage de câble étanché (presse-étoupe ou silicone) entre le boîtier et le capteur enterré
Pour un vivarium : attention à la condensation, prévois un boîtier bien fermé et éventuellement un sachet de gel de silice à l'intérieur

## Étape 6 — Test terrain

Installe-le pour de vrai (dans ton pot ou vivarium), laisse tourner 2-3 semaines minimum. Note l'autonomie réelle obtenue et compare à ta cible de l'étape 0. C'est cette phase qui te donne les vraies données à montrer en portfolio (courbe d'humidité/température sur plusieurs jours + chiffre d'autonomie mesuré, pas estimé).

## Étape 7 (plus tard) — Extension : interface de réglage

Grâce à la structure modulaire de l'étape 4, cette phase devient un ajout, pas une refonte :

Le plus simple : l'ESP32 monte un petit serveur web local (mode point d'accès WiFi) accessible depuis ton téléphone, qui lit/écrit le fichier de config et affiche l'historique de mesures
Version plus poussée : connexion à ton WiFi domestique + dashboard accessible à distance (MQTT ou HTTP vers un petit serveur, comme dans le projet IoT dont on avait parlé)
Si un jour tu veux automatiser l'arrosage, tu ajoutes juste un module actionneur.c/h (relais + pompe) qui lit les seuils dans config — le reste du système ne change pas
