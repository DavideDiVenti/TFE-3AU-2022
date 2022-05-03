# TFE 3AU 2022
Ce dépôt reprend l'ensemble de mon Travail de Fin d'Etude. Dans le cadre du cours d'Industrie 4.0, avec la **Carte de Prototypage Industrie 4.0** des 3AU, il sera possible d'exploiter 6 différents types de communications : Wi-Fi, Bluetooth, Zigbee, LoRa, SigFox & IR.

## Le répertoire *Codes ESP32*
Dans ce répertoire se trouve les codes exemples de chaque périphérique de l'ESP32 correspondant à la **Carte de Prototypage Industrie 4.0**. Aucune modification supplémentaire ne sera nécessaire si ce n'est que dans le but de tester le bon fonctionnement du module concerné.

### Contenu :
Le répertoire *Codes ESP32* contient :
* Des codes exemples propre à chaque module
* Des codes exemples exploitant plusieurs modules à la fois
* Autre...

### Prise en main :
Chaque fichier reprenant un exemple de code est minutieusement commenté afin de pouvoir s'y repérer sans trop de difficulté. Dans certain cas, des liens vers des exemples de codes sources fiables en lignes sont introduit. 

## Documentation technique
Afin de permettre une mise en service plutot aisée dans ce nouveau matériel pédagogique, une explication de toutes les facettes de la **Carte de Prototypage Industrie 4.0** aura lieu ci-dessous...

### Présentation de la carte :
Blabla
<p align="left">
  <img align="center" width="80%" src="https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Images/Industry_4.0_Proto_Board_V2.0%20(PCB%203D).png.PNG" />
</p>

### Modules :
La **Carte de Prototypage Industrie 4.0** se compose de plusieurs modules. Il y en a des pré-soudés mais aussi à brancher manuellement sur des headers femelles.
| Modules    | Subtilités | Pré-soudés | Réferences    |
| ------|-----|-----|-----|
| Un microphone/capteur de son  | Détection de bruit par entrée analogique | non | VMA309 |
| Un capteur de mouvement PIR | Détection d'un mouvement d'un corps chaud | non | HC-SR501 |
| Un écran OLED 64*128 | Adresse I²C : 0x3C | non | SSD1306 |
| Un accéléromètre et/ou gyroscope| Accès aux données d'accéléromètres uniquement | non | MPU6050|
| Deux LEDs| Pullup | oui | / |
| ETC... | / | / |

### Les types de communications :
Blabla

### Pinout :
Blabla
| GPIO | Périphériques | Notes | 
|:------:|-----|-----|
| 0 | LORA-NSS | SPI Chip Select |
| 1 | NC |  | 
| 2 | LORA-D0 |  |
| 3 | NC |  |
| 4 | IO4 Jumper | Jumper JP11: Choice of CAN-RX or LED1 |
| 5 | IO5 Jumper | Jumper JP12: Choice of CAN-TX or BP2 |
| 6 | IO6 Jumper | Jumper JP14: Choice of RFID-CS (SPI Chip Select) or LED2 |
| 12 |  |  |
| 13 |  |  |
| 14 |  |  |
| 15 |  |  |
| 16 |  |  |
| 17 |  |  |
| 18 |  |  |
| 19 |  |  |
