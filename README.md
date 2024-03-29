# Forklift_Arduino
Notre projet est un Chariot élévateur supportée par une grue avant, ce grue elle fonctionne pour porter et soulever des objets.
 Cette Chariot fonctionne dans toutes les directions et elle nous permet de déterminer sa trajectoire et de la contrôler grâce à une application Android.
  tout les objet et connecté avec  publish-subscribe network "**MQTT**",cette dernière et transfert les messages entre eux.
## Contents
+ [Introduction](#Forklift_Arduino)
+ [Matériel utilisé](#Matériel-utilisé)
+ [Préparez le chariot élévateur](#Préparez-le-chariot-élévateur) <br/>
           + [fabrication de carrosserie](#Préparez-le-chariot-élévateur)<br/>
           + [Programming esp8266](#Préparez-le-chariot-élévateur)<br/>
           + [Circuit de projet](#Préparez-le-chariot-élévateur)
+ [Arduino code](#Arduino-code-)
+ [Application de contrôle ( Android )](#application-de-contr%C3%B4le-android-)
+ [Photo de projet final](#Photo-de-projet-final-)

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

*[top↑](#Forklift_Arduino)*

## Préparez le chariot élévateur
1. La première chose est la fabrication de carrosserie :

<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P1.jpeg" target="_blank"><img src="Assets/P1.jpeg" alt="Browser Stack" width="190"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P2.jpeg" target="_blank"><img src="Assets/P2.jpeg" alt="Browser Stack" width="190"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P3.jpeg" target="_blank"><img src="Assets/P3.jpeg" alt="Browser Stack" width="190"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/P4.jpeg" target="_blank"><img src="Assets/P4.jpeg" alt="Browser Stack" width="190"></a><br/>

2. Programming esp8266 :

<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/prog_esp.PNG" target="_blank"><img src="Assets/prog_esp.PNG" alt="Browser Stack" ></a><br/>
 - include les 3 librairies suivantes :
 >
 
 ```c++
    #include <ESP8266WiFi.h>
    #include <PubSubClient.h>
 ```
 
 - Les variables suivantes permettent de définir les paramètres de connexion au réseau WiFi && les paramètres de connexion a mosquitto :
 >
```c++
    #define MSG_BUFFER_SIZE  (50)
    
    const char* ssid = "LP";
    const char* password = "00000000";
    const char* mqtt_server = "test.mosquitto.org";
    
    WiFiClient espClient;
    PubSubClient client(espClient);
    unsigned long lastMsg = 0;
    
    char msg[MSG_BUFFER_SIZE];
    int value = 0;
```
 - methode de connexion et de reconnexion :
 >
```c++
    void setup_wifi() {
      delay(10);
      WiFi.mode(WIFI_STA);
      WiFi.setAutoReconnect(true);
      WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
      }
    
      randomSeed(micros());
    }
    
    void callback(char* topic, byte* payload, unsigned int length) {
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.println();
    }
    
    void reconnect() {
      while (!client.connected()) {
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str())) {
          client.subscribe("lpsieForklift");
        } else {
          delay(5000);
        }
      }
    }
```
 - setup & loop :
 >
```c++
    void setup() {
      Serial.begin(9600);
      setup_wifi();
      client.setServer(mqtt_server, 1883);
      client.setCallback(callback);
    }
    
    void loop() {
      if (!client.connected()) {
        reconnect();
      }
      client.loop();
      if (Serial.available() > 0) {
        char inbyte = Serial.read();
        if(inbyte != '\n' && inbyte != '\r'){
          char msg[2];
          msg[0]=inbyte;
          msg[1]='\0';
          client.publish("lpsieForklift", msg);
        }
      }  
    }
 ```   
   **Esp8266-code** [here](EspCode/EspCode.ino)
   
   3. Circuit de projet :
   
   <a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/project.PNG" target="_blank"><img src="/Assets/project.PNG" alt="Browser Stack">   
 | | Arduino pin |
|--|--|
| drive l298n | 8 - 9 - 10 - 11 - GND  |
| drive Stepper | 4 - 5 - 6 - 7 - 5v - GND  |
| Esp8266 | 3,5v - TX - RX - GND  |
 </a>

*[top↑](#Forklift_Arduino)*

## Arduino code :

 - les bibliothèques utilisées :
 >
```c++
    #include <Stepper.h>
```
 - la fonction utilisées pour controle les motors :
 >
```c++
    void forkliftMotor(int Mode1,int Mode2,int Mode3,int Mode4){
        digitalWrite(pin1,Mode1);
        digitalWrite(pin2,Mode2);
        digitalWrite(pin3,Mode3);
        digitalWrite(pin4,Mode4);
    }
 ``` 
> les pin : 8 - 9 - 10 - 11

 - la fonction utilisées pour controle la grue :
 >
```c++
    void fokliftHand(Stepper stepPer ,  int SR){ 
      stepPer.step(SR);
      delay(1);
      stepPer.step(SR);
    }
 ```   
> SR --> StepperOneRevolution : Tournez l'arbre d'un tour dans le sens des aiguilles d'une montre et d'un tour dans le sens inverse   
    
 - test de controle :
 >
```c++
    if (Serial.available() > 0) {
        char incomingByte = Serial.read();
        switch(incomingByte){
           case 'a' :forkliftMotor(1,0,1,0); //forward        
               break;
           case 'b' :forkliftMotor(0,1,0,1); //back        
               break;
           case 'c' :forkliftMotor(0,0,1,0); //RIGHT      
               break;
           case 'd' :forkliftMotor(1,0,0,0); //LEFT       
               break;
           case 'e' :forkliftMotor(1,0,0,0); //STOP car        
               break;
           case 'f' :fokliftHand(Mystepper,SR); //Top        
               break;
           case 'g' :fokliftHand(Mystepper,-SR); //bottom        
               break;
           case 'k' :fokliftHand(Mystepper,0); //STOP        
               break;
          }
    }
 ```
 **Forklift-controle-code** [here](Forklift_Arduino.ino)
 
*[top↑](#Forklift_Arduino)* 
 
## Application de contrôle Android :

<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/app.PNG" target="_blank"><img src="Assets/app.PNG" alt="Browser Stack"></a><br/> 
 
 - les bibliothèques utilisées :
 >
```java
    import org.eclipse.paho.android.service.MqttAndroidClient;
    import org.eclipse.paho.client.mqttv3.IMqttActionListener;
    import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
    import org.eclipse.paho.client.mqttv3.IMqttToken;
    import org.eclipse.paho.client.mqttv3.MqttCallback;
    import org.eclipse.paho.client.mqttv3.MqttClient;
    import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
    import org.eclipse.paho.client.mqttv3.MqttException;
    import org.eclipse.paho.client.mqttv3.MqttMessage;
 ```  
 - les variable utilisées :
 >
```java
    String topicStr = "lpsieForklift";
    String clientId = MqttClient.generateClientId();
    MqttAndroidClient client = new MqttAndroidClient(this.getApplicationContext(), "tcp://test.mosquitto.org", clientId);
    Button stop = findViewById(R.id.stop); 
```  
> **D'autres boutons peuvent être ajoutés**
    
  - Connexion à mosquitto :
 >
```java
    try {
    IMqttToken token = client.connect();
    token.setActionCallback(new IMqttActionListener() {
    @Override
    public void onSuccess(IMqttToken asyncActionToken) {
    // We are connected
    Toast.makeText(MainActivity.this, "connect", Toast.LENGTH_LONG).show();
    }
    @Override
    public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
    // Something went wrong e.g. connection timeout or firewall problems
    Toast.makeText(MainActivity.this, "Not connect", Toast.LENGTH_LONG).show();
    }
    });
    } catch (MqttException e) {
    e.printStackTrace();
    }
    }
```
  - envoie un message à mosquitto :
 >
```java
    //click methode
    public void stop(View view) {
    String topic = topicStr;
    String message = "k";
    try {
    client.publish(topic, message.getBytes(), 0, false);
    } catch (MqttException e) {
    e.printStackTrace();
    }
    }
```
*[top↑](#Forklift_Arduino)*

## Photo de projet final :

<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/f2.jpeg" target="_blank"><img src="Assets/f2.jpeg" alt="Browser Stack" width="190"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/f3.jpeg" target="_blank"><img src="Assets/f3.jpeg" alt="Browser Stack" width="190"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/f4.jpeg" target="_blank"><img src="Assets/f4.jpeg" alt="Browser Stack" width="190"></a>
<a href="https://github.com/hamzaelmoudden/Forklift_Arduino/blob/master/Assets/f5.jpeg" target="_blank"><img src="Assets/f5.jpeg" alt="Browser Stack" width="190"></a>


    **Réalisé par :** 
     - Hamza El Moudden
     - Charki Mohamed
     - Outmouhine ahmed
     - Lagdrori zakaria

*[top↑](#Forklift_Arduino)*
