#pragma once
#include <ds_console.h>
#include <ds_mqtt_manager.h>
#include <ds_wdt.h>
#include <ds_bootloader.h>
#include "config.h"

enum PROPS_STATES_POSITIONS {GLOBE_STATE_POS,};

constexpr size_t PROPS_NUM = 1U;
constexpr int props_num_in_ERP[PROPS_NUM] = {Globe_space::GLOBE_ERP_NUM,};

constexpr char PROP_1_STRID[] = "Globe";

const char *propsNames[PROPS_NUM] = {PROP_1_STRID,};

void globe_onActivate();
void globe_onFinish();
prop_CBs_t  globe_cbs = { globe_onActivate, globe_onFinish, ds_MQTT::reset };

props_CBs_t props_cbs[PROPS_NUM] = { &globe_cbs,};

prop_state_t    globe_state = {0};
props_states_t  props_states[PROPS_NUM] = {globe_state, };

Console *console;

void on_er_start()
{
  console->println(F("ER: Start"));
  globe_onActivate();
}

typedef  MQTT_manager<
  PROPS_NUM, CIRCUIT_NAME, propsNames, props_num_in_ERP,
  on_er_start, ds_MQTT::reset, props_cbs> mqtt_manager_t;

mqtt_manager_t *mqtt_manager;

void common_routine_init()
{
  if (UPLOAD_BOOT_INFO)
    bootloader_init(IP_ENDING);

  console = new Console(CIRCUIT_NAME);
  mqtt_manager = new mqtt_manager_t(console, IP_ENDING);
  Serial.begin(115200);
  resetServer_init();  
}

void common_routine()
{
  mqtt_manager->routine(props_states);
  console->check();
  wdTimer_check();
  resetServer_check(console);
}