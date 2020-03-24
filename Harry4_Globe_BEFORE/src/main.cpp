//  general  //
#include "Arduino.h"
#include "g_defines.h"
#include "g_console.h"
#include "g_mqtt.h"
#include "g_mqtt_handler.h"
#include "g_wdt.h"
//  riddle 1  //
#include "hw_gerkon.h"
#include "hw_led.h"
#include "l_timer.h"

// ---- riddle 1 ---- //

#define STAGE_1_NONE         1
#define STAGE_1_GERKON       2
#define STAGE_1_DONE         3
int stage1Number = STAGE_1_NONE;

//
//  Gerkon  //
//

void gerkon_onActivated() {
  Serial.println("gerkon_onActivated");
  led2_on();
  timer1_startOnce(2000);
  stage1Number = STAGE_1_DONE;
  console->println("STAGE_1_DONE");
  strcpy(riddle1State, MQTT_1_STRSTATUS_FINISHED);  
  
  mqtt_publish("/er/music/play", "26");
}

//
//  Timer  //
//

void timer1_onTimeout(){
  console->println("timer1_onTimeout");
  led2_off();
  stage1Number = STAGE_1_GERKON;
  console->println(F("STAGE_1_GERKON"));
  strcpy(riddle1State, MQTT_1_STRSTATUS_ENABLED);
}

//
//  MQTT  //
//

//  riddle 1  //
void mqtt_riddle1_onReset() {
  console->println(F(MQTT_1_STRNAME ": Reset"));

  telnet_stop();
  wdTimer_reset();
}

void mqtt_riddle1_onActivate() {
  console->println(F(MQTT_1_STRNAME ": Activated"));
  led1_on();
  stage1Number = STAGE_1_GERKON;
  console->println(F("STAGE_1_GERKON"));
  strcpy(riddle1State, MQTT_1_STRSTATUS_ENABLED);
}

void mqtt_riddle1_onFinish() {
  console->println(F(MQTT_1_STRNAME ": Finish"));  
  gerkon_onActivated();
}

//  main  //
void mqtt_er_onStart() {
  console->println(F("ER: Start"));
  // mqtt_riddle1_onActivate();
}

void mqtt_er_onReset() {
  console->println("ER: Reset");
  mqtt_riddle1_onReset();
}

//
//  Main //
//

void setup() {
  //  general  //
  Serial.begin(115200);  
  console_init();
  wdTimer_init();
  resetServer_init();
  mqtt_init();  
  // bootloader_init();  //  ONLY ONCE !!
  // bootloader_show_info();
  
  //  riddle 1  //
  gerkon_init();
  led1_init();
  led2_init();
  
  console->println();
  console->println(F(PROP_NAME ": Init done"));
}

void loop() {
  //  general  //
  mqtt_check();
  console_check();
  wdTimer_check();
  resetServer_check();

  //  riddle 1 //
  if(stage1Number >= STAGE_1_GERKON){
    gerkon_check();
  }  
  timer1_check();

  mqtt_sendInfo_loop();
}