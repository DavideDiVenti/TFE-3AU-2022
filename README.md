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
  <img align="center" width="80%" src="https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Images/Industry_4.0_Proto_Board_V1.0%20(PCB%203D)%20v24.png?raw=true" />
</p>

La **Carte de Prototypage Industrie 4.0** se compose de :
| Modules    | Subtilités | Réferences    |
| ------|-----|-----|
| Un microphone/capteur de son  | Détection de bruit par entrée analogique | VMA309 |
| Un capteur de mouvement PIR | Détection d'un mouvement d'un corps chaud | HC-SR501 |
| Un écran OLED 64*128 | Adresse I²C : 0x3C | SSD1306 |
| Un accéléromètre et/ou gyroscope| Accès aux données d'accéléromètres uniquement | MPU6050|
| ETC... | / | / |
