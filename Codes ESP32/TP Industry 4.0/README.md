# TP Industry 4.0
Ce Travail Pratique rassemble plusieurs notions de l'IoT & de l'Industrie 4.0. En plus de la programmation de chaque **Carte de Prototypage Industrie 4.0**, une machine virtuelle de type Docker sera utilisée. Cette machine peut être embarquée dans un ordinateur ou un Raspberry Pi. Dans l'exemple présenté dans ce fichier, un Raspberry Pi a été utilisé, mais le principe est le même qu'avec un PC.

## Consigne du TP
L’idée de ce TP serait d’assembler 3 des 4 différentes **Cartes de Prototypage Industrie 4.0** et de les faire communiquer entre eux, mais pas n’importe comment. En premier temps, le PCB multi-protocole et le Raspberry Pi 4 doivent se connecter en tant que client Wi-Fi à partir d’un point d’accès. Ces deux derniers communiqueront entre eux sous la couche MQTT créée par le Raspberry Pi 4. En deuxième temps, le PCB orienté Zigbee communique en radio avec le PCB multi-protocole et le PCB orienté LoRa communique à son tour également en radio avec le PCB multi-protocole indépendamment.

Le Raspberry Pi 4 simulera un bot depuis le cloud Telegram. Sur base des interactions effectuées dans le tchat entre l’utilisateur et le bot, le Raspberry Pi 4 demandera au PCB multi-protocole en MQTT d’agir en conséquence.

Par exemple, si l’utilisateur demande d’allumer la LED 2 du PCB orienté LoRa, alors le Raspberry Pi 4 envoie la requête correspondante en MQTT aux PCB multi-protocole pour qu’à son tour ce dernier envoie la même requête en radio sous le protocole LoRa vers le PCB orienté LoRa. Il allumera sa LED et enverra un accusé de réception (en renvoyant une requête en sens inverse) de sorte que l’utilisateur sache que sa demande ait bien été exécutée.

Toutes les requêtes ainsi que leurs réponses sont enregistrées dans une base de données (Fire Base). Leur visualisation peut se faire depuis l’interaction dans le tchat entre l’utilisateur et le bot.

## Schéma représentatif du TP
<p align="left">
  <img align="center" width="80%" src="https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Images/TP%20Industry%204.0.drawio.png" />
</p>

## Les fichiers présents dans ce dépôt
Dans ce répertoire se trouvent les 3 différents codes des **Cartes de Prototypage Industrie 4.0** correspondant au TP. Quant au quatrième, celui du NodeRed, est également disponible. Des modifications supplémentaires dans le code pourraient s'avérer être nécessaire dans le cas où 
* l'adresse IP du broker MQTT est différente de la mienne
* le nom de votre base de données Firebase est différent de la mienne (dans les requètes HTTP de l'API)
* la connexion Wi-Fi (SSID & PASSWORD) est différente de la mienne
* les identifiants du bot Telegram sont différents de la mienne (chatID & botID)
* ...

### Contenu :
Ce répertoire [TP Industry 4.0](https://github.com/DavideDiVenti/TFE-3AU-2022/tree/master/Codes%20ESP32/TP%20Industry%204.0) se compose de plusieurs éléments :
* Un fichier [MonoProtocol_LoRa_Node](https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Codes%20ESP32/TP%20Industry%204.0/MonoProtocol_LoRa_Node/MonoProtocol_LoRa_Node.ino) correspondant au PCB Mono-Protocole orienté LoRa
* Un fichier [MonoProtocol_Zigbee_Node](https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Codes%20ESP32/TP%20Industry%204.0/MonoProtocol_Zigbee_Node/MonoProtocol_Zigbee_Node.ino) correspondant au PCB Mono-Protocole orienté Zigbee
* Un fichier [MultiProtocol_Node](https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Codes%20ESP32/TP%20Industry%204.0/MultiProtocol_Node/MultiProtocol_Node.ino) correspondant au PCB Multi-Protocole
* Un fichier [NodeRed flows](https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Codes%20ESP32/TP%20Industry%204.0/NodeRed%20flows.json) correspondant au code NodeRed de votre PC ou Raspberry Pi

## Remarque
Les codes mis à disposition dans le répertoire [TP Industry 4.0](https://github.com/DavideDiVenti/TFE-3AU-2022/tree/master/Codes%20ESP32/TP%20Industry%204.0) ne vous permettent pas de faire fonctionner le TP du premier coup. Des étapes de configuration sont nécessaires avant d'utiliser ces codes, notamment pour la création d'un docker et de ses containers. Référencez-vous aux pages 69 à 80 du [Rapport du TFE](https://github.com/DavideDiVenti/TFE-3AU-2022/blob/master/Documents/TFE-DI%20VENTI-DAVIDE.pdf) pour avoir un guide sur les différentes étapes.
