# Protocole complet d'assemblage — Datalogger environnemental ESP32

Ce document explique, étape par étape, comment assembler ton projet à partir de zéro. Chaque mot technique est défini la première fois qu'il apparaît. Suis les sections dans l'ordre : elles sont pensées pour que tu apprennes les gestes simples avant les plus délicats.

---

## PARTIE 0 — Le matériel dont tu as besoin AVANT de commencer

### Outils de soudure

* **Fer à souder** : un outil qui chauffe une pointe métallique très fort (300-350°C) pour faire fondre un métal spécial (l'étain) et créer des connexions électriques permanentes entre deux pièces. Ressemble à un gros stylo relié à une base électrique.
* **Étain (ou "soudure", "fil à souder")** : un fil métallique fin qui fond à la chaleur du fer et qui, une fois refroidi, colle et connecte électriquement deux pièces de métal. Prends de l'étain **avec âme de flux** (souvent écrit "rosin core" ou "flux core" sur la bobine) — le flux est un produit qui nettoie automatiquement la surface pendant que tu soudes, indispensable pour un débutant.
* **Support pour fer à souder (ou "béquille")** : un socle métallique qui tient le fer chaud en l'air pour que tu ne le poses jamais sur la table (risque de brûlure/incendie).
* **Éponge humide ou tampon métallique** : sert à nettoyer la pointe du fer entre deux soudures (retire les résidus noirs qui s'accumulent).
* **Pince brucelle (ou "pince à épiler de précision")** : une pince fine pour tenir les petits composants et les pins pendant que tu soudes, sans te brûler les doigts.
* **Multimètre** : un appareil de mesure électrique (tension, continuité) qui te permet de vérifier qu'une soudure est bien connectée et qu'il n'y a pas de court-circuit. Indispensable pour débugger.
* **Support "3ème main" (optionnel mais très utile)** : une base avec deux pinces articulées qui tiennent tes pièces en place pendant que tu as les deux mains occupées par le fer et l'étain.

### Petites fournitures

* **Barrettes de pins (header pins)** : des rangées de petites tiges métalliques que tu soudes sur les modules (SHT31, DS3231) pour ensuite pouvoir les brancher sur une breadboard ou avec des câbles. Souvent vendues en barrette de 40 pins que tu casses à la bonne longueur.
* **Câbles Dupont** : des petits câbles souples avec des connecteurs aux extrémités, pour relier les composants entre eux sans souder (utilisés en phase breadboard). Il en existe 3 types : mâle-mâle, mâle-femelle, femelle-femelle — prends un kit avec les trois.
* **Breadboard (plaque d'essai)** : une plaque en plastique blanche pleine de petits trous, qui te permet de brancher des composants électroniques sans soudure, pour tester avant de rendre ça permanent.
* **Gaine thermorétractable** : un petit tube en plastique qui rétrécit à la chaleur (avec un briquet ou un décapeur thermique) pour isoler et protéger une soudure sur un fil.

### Sécurité de base (à lire une fois, applicable à toute la suite)

1. Soude toujours dans un endroit **aéré** — la fumée du flux qui chauffe n'est pas à respirer directement.
2. Le fer à souder reste chaud plusieurs minutes après l'avoir éteint — repose-le toujours sur son support, jamais sur la table.
3. Ne touche jamais la pointe métallique du fer, même "juste pour voir" — 300°C brûle instantanément.
4. Travaille sur une surface qui ne craint pas la chaleur (pas de nappe plastique, de tissu).
5. Lave-toi les mains après avoir manipulé de l'étain (il contient un peu de plomb dans la plupart des versions grand public).

---

## PARTIE 1 — L'ESP32 (déjà vu, résumé rapide)

**Aucune soudure nécessaire ici**, sauf si tu prends une version "sans pins" (rare). Si ta carte a déjà les pins soudés en usine (cas standard), tu n'as rien à faire.

Si tu as une version **32U avec IPEX** : clipse l'antenne comme expliqué précédemment (appui vertical léger jusqu'au clic, jamais de force en biais).

✅ **Test de vérification** : branche la carte en USB à ton ordinateur, une LED doit s'allumer sur la carte.

---

## PARTIE 2 — Souder les pins sur le module SHT31 (capteur air)

Le module SHT31 arrive souvent **sans les pins soudés** — juste des petits trous ronds dorés (appelés "pads") sur le bord de la carte. Il faut souder une barrette de pins dedans pour pouvoir le brancher plus tard.

### Étapes

1. **Coupe une barrette de pins** à la bonne longueur : compte le nombre de trous sur ton module SHT31 (souvent 4 ou 6), et casse une barrette de header pins à cette longueur exacte (les barrettes sont pré-découpées avec des encoches, tu casses à la main ou avec une petite pince coupante).
2. **Insère la barrette** dans les trous du module, côté où les pins les plus longs dépassent en dessous (c'est ce côté que tu vas souder).
3. **Stabilise l'ensemble** : pose le module à plat sur la table, pins vers le haut, ou utilise ta "3ème main" pour le maintenir immobile. Si les pins ne tiennent pas droit tout seuls, tu peux les planter dans une breadboard pour les stabiliser bien perpendiculaires pendant la soudure.
4. **Chauffe la jonction** : pose la pointe du fer chaud sur le pad doré ET le pin en même temps pendant 2-3 secondes (le fer doit toucher les deux à la fois pour bien chauffer l'ensemble).
5. **Ajoute l'étain** : sans bouger le fer, touche la jonction avec le fil d'étain (pas directement avec le fer) — l'étain doit fondre et couler tout seul autour du pin, formant un petit cône brillant.
6. **Retire l'étain puis le fer**, dans cet ordre, après 1-2 secondes.
7. **Répète pour chaque pin.**

✅ **À quoi doit ressembler une bonne soudure** : un petit cône brillant, lisse, en forme de volcan bien fondu autour du pin.

❌ **Signes d'une mauvaise soudure** : aspect terne/grisâtre et granuleux (= "soudure froide", pas assez chauffée, mauvaise connexion) ou une grosse boule qui ne touche pas bien le pin (= pas assez d'étain fondu ou fer pas assez chaud).

### Vérification avec le multimètre

Mets le multimètre en mode "continuité" (souvent symbole 🔊 ou icône diode). Touche une pointe sur le pin soudé, l'autre sur le pad correspondant côté composant — le multimètre doit biper, confirmant que le courant passe bien.

---

## PARTIE 3 — Souder les pins sur le module DS3231 (RTC)

**Exactement la même procédure que la Partie 2.** Le module DS3231 a généralement plus de trous (7 pins : SCL, SDA, SQW, 32K, VCC, GND, et parfois un pin supplémentaire).

Point spécifique à ce module : **insère la pile CR2032** dans son support rond argenté avant ou après la soudure des pins (peu importe l'ordre) — fais attention au sens (+ vers le haut, généralement indiqué par une gravure "+" à côté du support).

---

## PARTIE 4 — Le capteur d'humidité du sol capacitif

**Bonne nouvelle : rien à souder.** Ce capteur arrive avec ses 3 fils déjà soudés en usine et un connecteur à l'extrémité (souvent un connecteur blanc "JST-PH" ou directement des câbles Dupont femelles). Tu n'as qu'à le brancher.

⚠️ Vérifie juste que le connecteur du capteur correspond à ce que tu comptes brancher en face (câbles Dupont mâle-femelle si le capteur a un connecteur femelle).

---

## PARTIE 5 — Le circuit d'alimentation (TP4056 + support 18650)

C'est l'étape la plus délicate, car elle implique la batterie — à faire avec attention.

### Vocabulaire spécifique

* **B+ / B-** : les deux points de connexion du module TP4056 qui vont vers la **batterie** (B+ = borne positive, B- = borne négative).
* **OUT+ / OUT-** : les deux points de connexion qui vont vers **ton circuit** (l'ESP32), c'est-à-dire la sortie d'alimentation une fois la batterie chargée/en cours d'utilisation.
* **Court-circuit** : quand le + et le - se touchent directement sans passer par un composant — ça peut faire chauffer très fort, voire prendre feu avec une batterie Li-ion. C'est le risque principal de cette étape, d'où la prudence demandée.

### Étapes

1. **Repère les 4 points de soudure** sur le module TP4056 : B+, B-, OUT+, OUT-. Ils sont écrits en petit sur le circuit imprimé (PCB), à la loupe si besoin.
2. **Coupe 4 petits bouts de fil électrique** (fil de câblage fin, ~5-10cm chacun) de 2 couleurs différentes si possible (rouge pour le +, noir pour le -) — ça t'évitera de te tromper plus tard.
3. **Soude le fil rouge sur B+**, le fil noir sur B- (même technique de soudure que Partie 2 : chauffe le point, ajoute l'étain, retire).
4. **Soude un autre fil rouge sur OUT+**, un autre fil noir sur OUT-.
5. **Connecte le support de batterie 18650** : ses deux fils (rouge = +, noir = -) se soudent ou se clipsent sur B+ et B- du TP4056 (**respecte bien les couleurs, une inversion ici peut détruire le module ou la batterie**).
6. **Insère la batterie 18650** dans le support en respectant le sens indiqué (+ et - gravés sur le support en plastique).

### Test de sécurité AVANT de brancher l'ESP32

1. Mets le multimètre en mode **tension continue (DC), calibre 20V**.
2. Touche les pointes du multimètre sur OUT+ et OUT- du module.
3. Tu dois lire une tension entre **3.0V et 4.2V** (c'est la plage normale d'une 18650 chargée à des degrés divers).
4. Si tu lis 0V → un fil est mal soudé ou débranché, vérifie.
5. Si tu lis une tension négative → tu as inversé + et -, débranche immédiatement et recommence.

✅ Seulement une fois cette tension confirmée correcte, tu peux brancher OUT+ / OUT- vers l'alimentation de l'ESP32 (pin "VIN" ou "3V3" selon comment tu veux l'alimenter — on en reparlera à l'étape de câblage final).

---

## PARTIE 6 — Assemblage sur breadboard (avant toute soudure finale)

**Objectif : vérifier que tout fonctionne ensemble avant de rendre les connexions permanentes.** C'est l'étape 3 de ton plan de projet initial.

### Câblage I2C (SHT31 + DS3231 partagent le même bus)

Le bus **I2C** est un protocole de communication qui permet à plusieurs composants de parler au même microcontrôleur avec seulement 2 fils partagés (au lieu d'un fil dédié par composant). C'est pour ça que le SHT31 et le DS3231 peuvent utiliser les mêmes 2 pins de l'ESP32.

| Pin ESP32     | Va vers                                                                   |
| ------------- | ------------------------------------------------------------------------- |
| GPIO 21 (SDA) | SDA du SHT31 **et** SDA du DS3231 (les deux en parallèle sur le même fil) |
| GPIO 22 (SCL) | SCL du SHT31 **et** SCL du DS3231 (pareil)                                |
| 3V3           | VCC du SHT31 **et** VCC du DS3231                                         |
| GND           | GND du SHT31 **et** GND du DS3231                                         |

Utilise des câbles Dupont mâle-mâle si tes modules ont des pins mâles (que tu viens de souder), en passant par la breadboard pour répartir un même signal vers deux composants (deux câbles branchés sur la même ligne de trous de la breadboard = même signal partagé).

### Câblage du capteur de sol (analogique, pas I2C)

| Pin ESP32     | Va vers                |
| ------------- | ---------------------- |
| GPIO 34 (ADC) | AOUT du capteur de sol |
| 3V3           | VCC du capteur de sol  |
| GND           | GND du capteur de sol  |

*(GPIO 34 est un exemple — n'importe quelle pin marquée "ADC" sur ton ESP32 fonctionne, elles sont indiquées sur le schéma "pinout" de ta carte, souvent imprimé sur un petit carton fourni ou trouvable en cherchant "ESP32 DevKitC pinout" en ligne.)*

### Câblage de l'alimentation par batterie

| Sortie TP4056 | Va vers                                                                                                  |
| ------------- | -------------------------------------------------------------------------------------------------------- |
| OUT+          | Pin **VIN** de l'ESP32 (PAS 3V3 directement, VIN passe par le régulateur de tension intégré de la carte) |
| OUT-          | Pin **GND** de l'ESP32                                                                                   |

### Vérification finale avant mise sous tension

1. Repasse visuellement sur chaque fil : est-ce que chaque + va bien vers un +, chaque GND vers un GND ?
2. Utilise le multimètre en mode continuité pour vérifier qu'il n'y a **aucun contact accidentel** entre une ligne + et une ligne GND (touche les deux avec les pointes du multimètre — s'il bipe, il y a un court-circuit à corriger).
3. Seulement après ces vérifications, branche l'alimentation (USB ou batterie).

---

## PARTIE 7 — Câblage définitif (après validation sur breadboard)

Une fois que tout fonctionne sur breadboard et que ton firmware lit correctement les capteurs, tu peux "figer" le montage en soudant les connexions définitives (remplace les câbles Dupont temporaires par des fils soudés directement, plus fiable pour un usage longue durée en extérieur — les connexions Dupont peuvent se desserrer avec les vibrations/l'humidité).

Utilise la même technique de soudure que dans les Parties 2-5 pour relier définitivement :

* SHT31 → ESP32 (4 fils : VCC, GND, SDA, SCL)
* DS3231 → ESP32 (mêmes 4 fils, en parallèle sur les mêmes points que le SHT31)
* Capteur sol → ESP32 (3 fils : VCC, GND, AOUT)
* TP4056 → ESP32 (2 fils : VIN, GND)

💡 Astuce débutant : soude un point à la fois, teste avec le multimètre après chaque soudure plutôt que de tout souder d'un coup — ça isole immédiatement l'origine d'un problème si quelque chose ne fonctionne plus après.

---

## PARTIE 8 — Boîtier et étanchéité

1. **Imprime le boîtier en 3D** (PETG recommandé pour la résistance à l'humidité, voir discussion précédente).
2. **Perce ou prévois dans le design** un trou pour le presse-étoupe (le passage de câble étanche) par lequel sortira le câble du capteur de sol.
3. **Visse le presse-étoupe** dans ce trou (il se visse comme un boulon, avec un joint en caoutchouc à l'intérieur qui se resserre autour du câble quand tu serres l'écrou).
4. **Fais passer le câble du capteur de sol** à travers le presse-étoupe avant de le brancher, puis serre l'écrou pour bloquer le câble et assurer l'étanchéité.
5. **Place un sachet de gel de silice** à l'intérieur du boîtier (absorbe l'humidité résiduelle qui pourrait s'infiltrer ou se former par condensation).
6. **Ferme le boîtier** — si ton modèle 3D a un couvercle à vis, ajoute un petit joint (caoutchouc ou silicone) entre le couvercle et la base pour améliorer l'étanchéité.

---

## Récapitulatif de l'ordre à suivre

1. ✅ Vérifier l'ESP32 (antenne si 32U, test USB)
2. 🔧 Souder les pins sur SHT31
3. 🔧 Souder les pins sur DS3231 + insérer la pile CR2032
4. 🔌 Rien à faire sur le capteur de sol (déjà câblé)
5. 🔧 Souder les fils sur le TP4056 + connecter la batterie + **tester la tension avant de continuer**
6. 🧪 Tout assembler sur breadboard, tester avec le firmware
7. 🔧 Ressouder en définitif une fois validé
8. 📦 Imprimer et assembler le boîtier

N'hésite pas à me dire à quelle étape tu en es concrètement une fois que le matériel arrive — je peux détailler encore plus une partie spécifique (par exemple faire un schéma visuel du câblage, ou t'aider à débugger si le multimètre te donne une lecture bizarre).
