#ifndef G_MQTT_HANDLER_H
#define G_MQTT_HANDLER_H

#include "g_mqtt.h"

void mqtt_ConnectedCb() {
  mqtt_subscribe("/er/" MQTT_1_STRID "/cmd");
  mqtt_subscribe("/er/cmd");
//   mqtt_subscribe("/Test");
//   mqtt_subscribe("/er/dragonbox/sv");
//   mqtt_subscribe("/er/dragonbox/sh");
//   mqtt_subscribe("/er/music-sub/stop");
}

void mqtt_DisconnectedCb() {
}

//
//  Msgs  //
//

char mqtt_msgData[150];
char* mqtt_msgInfo(char* strId, char* strName, char* strStatus, int number) {
  //"{\"strId\":\"" MQTT_1_STRID "\", \"strName\":\"" MQTT_1_STRNAME "\", \"strStatus\":\"" + strStatus1 + "\", \"number\":\"" + MQTT_1_NUMBER + "\"}";

  //  begin  //
  mqtt_msgData[0] = 0;
  strcat(mqtt_msgData, "{");

  //  strId  //
  strcat(mqtt_msgData, "\"strId\":\"");
  strcat(mqtt_msgData, strId);
  strcat(mqtt_msgData, "\", ");

  //  strName  //
  strcat(mqtt_msgData, "\"strName\":\"");
  strcat(mqtt_msgData, strName);
  strcat(mqtt_msgData, "\", ");

  //  strStatus  //
  strcat(mqtt_msgData, "\"strStatus\":\"");
  strcat(mqtt_msgData, strStatus);
  strcat(mqtt_msgData, "\", ");

  //  number  //
  strcat(mqtt_msgData, "\"number\":\"");
  char strVal2[8];
  itoa(number, strVal2, 10);
  strcat(mqtt_msgData, strVal2);
  strcat(mqtt_msgData, "\"");

  //  end  //
  strcat(mqtt_msgData, "}");

  return mqtt_msgData;
}

//
//  SEND  //
//

void mqtt_sendInfo_loop() {
  static unsigned long lastTS = 0;
  if(millis() - lastTS > 1000) {
    lastTS = millis();    
    mqtt_publish("/er/riddles/info", mqtt_msgInfo(MQTT_1_STRID, MQTT_1_STRNAME, riddle1State, MQTT_1_NUMBER));
  }
}

//
//  RECIEVE  //
//

extern void mqtt_riddle1_onReset();
extern void mqtt_riddle1_onActivate();
extern void mqtt_riddle1_onFinish();

extern void mqtt_er_onStart();
extern void mqtt_er_onReset();

void mqtt_msgRecieve(char* topic, uint8_t* payload, unsigned int length) {
  //  prepare str  //
  char* payloadStr = (char*) payload;
  //  add end of string  //
  payloadStr[length] = '\0';

  //  debug msg  //
  console->print(F("Mqtt: "));console->print(topic);console->print(F(" : "));console->println(payloadStr); 
  
  //  riddle 1 cmd  //
  if(strcmp(topic, "/er/" MQTT_1_STRID "/cmd") == 0) {
    if(strcmp(payloadStr, "reset") == 0) {
      mqtt_riddle1_onReset();
    }
    else if(strcmp(payloadStr, "activate") == 0) {
      mqtt_riddle1_onActivate();
    }
    else if(strcmp(payloadStr, "finish") == 0) {
      mqtt_riddle1_onFinish();
    }
  }
  
  //  er cmd  //
  else if(strcmp(topic, "/er/cmd") == 0) {
    if(strcmp(payloadStr, "start") == 0) {
      mqtt_er_onStart();
    }
    else if(strcmp(payloadStr, "reset") == 0) {
      mqtt_er_onReset();
    }
  }
  
  // if(strcmp(topic, "/er/dragonbox/sv") == 0) {
  //   if(strcmp(payloadStr, "1") == 0) {
  //     console->println("1sv received");
  //     smokeValve_activate();
  //     console->println("smokeValve_activate");
  //   }
  //   else if(strcmp(payloadStr, "0") == 0) {
  //     console->println("0sv received");
  //     smokeValve_deactivate();
  //     console->println("smokeValve_deactivate");
  //   }
  //  } 

  // if(strcmp(topic, "/er/dragonbox/sh") == 0) {
  //   if(strcmp(payloadStr, "1") == 0) {
  //     console->println("1sh received");
  //     smokeHeater_activate();
  //     console->println("smokeHeater_activate");
  //   }
  //   else if(strcmp(payloadStr, "0") == 0) {
  //     console->println("0sh received");
  //     smokeHeater_deactivate();
  //     console->println("smokeHeater_deactivate");
  //   }
  //  }
  


  //  if(strcmp(topic, "/er/music-sub/stop") == 0) {
  //   if(strcmp(payloadStr, "1") == 0) {
  //     console->println("/er/music-sub/stop received");
  //    // smokeHeater_activate();
  //    // console->println("smokeHeater_activate");
  //   }
  //   else if(strcmp(payloadStr, "0") == 0) {
  //     console->println("0sh received");
  //     smokeHeater_deactivate();
  //     console->println("smokeHeater_deactivate");
  //   }
  //  }

  memset(payloadStr, 0, length); //обнуляем память ?? почему не работает без нее? 
}

#endif