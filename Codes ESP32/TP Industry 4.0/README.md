# TP Industry 4.0
Ce Travail Pratique rassemble plusieurs notions de l'IoT & de l'Industrie 4.0. En plus de la programmation de chaque **Carte de Prototypage Industrie 4.0**, une machine virtuelle de type Docker sera utilisée. Cette machine peut etre embarquée dans un ordinateur ou un Raspberry Pi. Dans l'exemple présenté dans ce fichier, un Raspberry Pi a été utilisé, mais le principe est le même qu'avec un PC.

## Consigne
L’idée de ce TP serait d’assembler 3 des 4 différentes **Cartes de Prototypage Industrie 4.0** et de les faire communiquer entre eux, mais pas n’importe comment. En premier temps, le PCB multi-protocole et le Raspberry Pi 4 doivent se connecter en tant que client Wi-Fi à partir d’un point d’accès. Ces deux derniers communiqueront entre eux sous la couche MQTT créée par le Raspberry Pi 4. En deuxième temps, le PCB orienté Zigbee communique en radio avec le PCB multi-protocole et le PCB orienté LoRa communique à son tour également en radio avec le PCB multi-protocole indépendamment.

Le Raspberry Pi 4 simulera un bot depuis le cloud Telegram. Sur base des interactions effectuées dans le tchat entre l’utilisateur et le bot, le Raspberry Pi 4 demandera au PCB multi-protocole en MQTT d’agir en conséquence.

Par exemple, si l’utilisateur demande d’allumer la LED 2 du PCB orienté LoRa, alors le Raspberry Pi 4 envoie la requête correspondante en MQTT aux PCB multi-protocole pour qu’à son tour ce dernier envoie la même requête en radio sous le protocole LoRa vers le PCB orienté LoRa. Il allumera sa LED et enverra un accusé de réception (en renvoyant une requête en sens inverse) de sorte que l’utilisateur sache que sa demande ait bien été exécutée.

Toutes les requêtes ainsi que leurs réponses sont enregistrées dans une base de données (Fire Base). Leur visualisation peut se faire depuis l’interaction dans le tchat entre l’utilisateur et le bot.

## Schéma représentatif au TP Industry 4.0


## Les fichiers présents dans ce dépôt
Dans ce répertoire se trouve tous les codes exemples des différentes **Cartes de Prototypage Industrie 4.0**. Des modifications supplémentaires dans le code pourraient s'avérer nécessaire dans le cas où le choix du brochage des différents composants d'un PCB ne corresponderait pas.

### Contenu :
Ce répertoire TP Industry 4.0 se compose de plusieurs éléments :
* Un fichier [MonoProtocol_LoRa_Node]
* Un fichier [MonoProtocol_Zigbee_Node]
* Un fichier [MultiProtocol_Node]
* Un fichier [NodeRed flows]

