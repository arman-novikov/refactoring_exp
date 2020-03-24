#pragma once
#include <ds_magnet_lock.h>
#include <ArdSensor.h>
#include <ds_simple_led.h>
#include <ds_timer.h>
#include "common.h"

enum {GLOBE_STAGE_NONE, GLOBE_STAGE_REED, GLOBE_STAGE_DONE}
    globe_stage;

static ArdSensor *reed;
static SimpleLed *illumination, *stained_glass;
static Timer *globe_reactivator;

static void reed_on_activated()
{
  *console << F("globe: reed_onActivated") << endl;
  
  stained_glass->on();
  globe_reactivator->launch(Globe_space::TIMER_OFFSET, 1);
  mqtt_manager->publish("/er/music/play", Globe_space::GLOBE_SOUND);  

  globe_stage = GLOBE_STAGE_DONE;
  *console << F("globe_STAGE_DONE") << endl;
  strcpy(props_states[GLOBE_STATE_POS], MQTT_STRSTATUS_FINISHED);  
}

void globe_onActivate()
{
    *console << PROP_1_STRID << F(": on activate") << endl;

    illumination->on();
    
    globe_stage = GLOBE_STAGE_REED;    
    strcpy(props_states[GLOBE_STATE_POS], MQTT_STRSTATUS_ENABLED);
}

void globe_onFinish()
{
    *console << PROP_1_STRID << F(": on finish") << endl;

    reed_on_activated();
    globe_stage = GLOBE_STAGE_DONE;    
    strcpy(props_states[GLOBE_STATE_POS], MQTT_STRSTATUS_FINISHED);
}

void globe_init()
{
    
    illumination = new SimpleLed(Globe_space::ILLUMINATION_PIN);
    stained_glass= new SimpleLed(Globe_space::STAINED_GLASS_PIN);

    reed = new ArdSensor(Globe_space::REED_PIN, LOW, 10);
    reed->setCallbackOnActivated(reed_on_activated);    
    globe_reactivator = new Timer([](void*){
        stained_glass->off();
        globe_stage = GLOBE_STAGE_REED;
        strcpy(props_states[GLOBE_STATE_POS], MQTT_STRSTATUS_ENABLED);
        *console << F("reactivator done") << endl;
    });
    
    globe_stage = GLOBE_STAGE_NONE;
    strcpy(props_states[GLOBE_STATE_POS], MQTT_STRSTATUS_READY);
}

void globe_routine()
{
    
    if (globe_stage == GLOBE_STAGE_REED) {
        reed->check();
    }

    globe_reactivator->routine();
}