# Forklift_Arduino
Notre projet est un Chariot élévateur supportée par une grue avant, ce grue elle fonctionne pour porter et soulever des objets.
 Cette Chariot fonctionne dans toutes les directions et elle nous permet de déterminer sa trajectoire et de la contrôler grâce à une application Android.
  tout les objet et connecté avec  publish-subscribe network "**MQTT**",cette dernière et transfert les messages entre eux.
## Contents
+ [Introduction](#Forklift_Arduino)
+ [Matériel utilisé](#Matériel-utilisé)

## Matériel utilisé
Pour ce projet, nous utilisons le drive motor l298n pour contrôler les dc gear motor,une carte arduino Uno et une carte Esp8266 pour connecter avec des autre objet . Les moteurs seront alimentés à l'aide de pile lithium 12v , la arduino sera alimentée à l'aide d’un batterie 5v . stepper motor et motor et son drive ULN2003 pour contrôle la grue . FTDI carte pour configure esp8266

<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/esp8266.jpg" target="_blank"><img src="Assets/esp8266.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/arduino-uno.jpg" target="_blank"><img src="Assets/arduino-uno.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/l298n.jpg" target="_blank"><img src="Assets/l298n.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/100uf-50v-a-800x800.jpg" target="_blank"><img src="Assets/100uf-50v-a-800x800.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/12vBattrery.jpg" target="_blank"><img src="Assets/12vBattrery.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/9V-battery.jpg" target="_blank"><img src="Assets/9V-battery.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/DC%20Geared.png" target="_blank"><img src="Assets/DC%20Geared.png" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/ULN2003-2.jpg" target="_blank"><img src="Assets/ULN2003-2.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/ftdi.jpg" target="_blank"><img src="Assets/ftdi.jpg" alt="Browser Stack" width="140"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/stepper.jpg" target="_blank"><img src="Assets/stepper.jpg" alt="Browser Stack" width="140"></a>

## Préparez le chariot élévateur
1. La première chose est la fabrication de carrosserie :

<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P1.jpeg" target="_blank"><img src="Assets/P1.jpeg" alt="Browser Stack" width="220"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P2.jpeg" target="_blank"><img src="Assets/P2.jpeg" alt="Browser Stack" width="220"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P3.jpeg" target="_blank"><img src="Assets/P3.jpeg" alt="Browser Stack" width="220"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P4.jpeg" target="_blank"><img src="Assets/P4.jpeg" alt="Browser Stack" width="220"></a><br/>

2. La première chose est la fabrication de carrosserie :
