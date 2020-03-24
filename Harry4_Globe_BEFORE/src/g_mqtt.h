#ifndef G_MQTT_H
#define G_MQTT_H

#include <Ethernet2.h>
#include <PubSubClient.h>
#include "g_console.h"
#include "g_defines.h"

#define MQTT_1_STRSTATUS_READY    "Not activated"
#define MQTT_1_STRSTATUS_ENABLED  "Activated"
#define MQTT_1_STRSTATUS_FINISHED "Finished"
char riddle1State[20] = MQTT_1_STRSTATUS_READY;

// #define MQTT_2_STRSTATUS_READY    "Not activated"
// #define MQTT_2_STRSTATUS_ENABLED  "Activated"
// #define MQTT_2_STRSTATUS_FINISHED "Finished"
// char riddle2State[20] = MQTT_2_STRSTATUS_READY;

// #define MQTT_3_STRSTATUS_READY    "Not activated"
// #define MQTT_3_STRSTATUS_ENABLED  "Activated"
// #define MQTT_3_STRSTATUS_FINISHED "Finished"
// char riddle3State[20] = MQTT_3_STRSTATUS_READY;

// #define MQTT_4_STRSTATUS_READY    "Not activated"
// #define MQTT_4_STRSTATUS_ENABLED  "Activated"
// #define MQTT_4_STRSTATUS_FINISHED "Finished"
// char riddle4State[20] = MQTT_4_STRSTATUS_READY;

// Initialize the Ethernet Client
EthernetClient ethernetClient;

// Create an instance of the MQTT Client
PubSubClient client;

// Initialize the last reconnect attempt
long lastReconnectAttempt = 0;

extern void mqtt_ConnectedCb();
extern void mqtt_DisconnectedCb();

extern void mqtt_msgRecieve(char* topic, uint8_t* payload, unsigned int length);

boolean reconnect() {
  console->println(F("MQTT: Connecting ..."));
  if (client.connect(MQTT_CLIENT_NAME)) {
    console->println(F("MQTT: Connected (id: " MQTT_CLIENT_NAME ")"));
    mqtt_ConnectedCb();
  } else {
    console->print(F("MQTT: Failed, Return Code: "));
    console->println(client.state());
    mqtt_DisconnectedCb();
  }
  return client.connected();
}

boolean mqtt_publish(const char* topic, const char* payload) {
  client.publish(topic,payload);
}


boolean mqtt_subscribe(const char* topic) {
  client.subscribe(topic);
}

//
//  Main  //
//

void mqtt_init(){

  // Initializing Ethernet
  console->println(F("Initializing Ethernet..."));

  // Wait for IP address to be resolved
  Ethernet.begin(mac, ip);

  // Print the ethernet gateway
  console->print("Gateway IP: ");
  console->println(Ethernet.gatewayIP());

  // Print your local IP address:
  console->print("Local IP: ");
  console->println(Ethernet.localIP());

  // Print Ethernet OK
  console->println(F("Ethernet Initialized..."));

  // Set the ethernet client
  client.setClient(ethernetClient);

  // Set the mqtt server
  client.setServer(server, 1883);

  // Set the callback
  client.setCallback(mqtt_msgRecieve);

  // Reset the last reconnect attempt
  lastReconnectAttempt = 0;

  // Set a delay
  delay(1500); 
}

void mqtt_check(){
  //  try to connect every 5 sec  //
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } 
  //  connected, do stuff  //
  else {
    client.loop();
  }
}

#endif