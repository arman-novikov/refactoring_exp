#include <ArdSensor.h>
#include <ArdPin.h>

#define PIN_ADMIN_GERKON 2

ArdSensor *gerkon;

extern void gerkon_onActivated();

void gerkon_init() {
  gerkon = new ArdSensor(PIN_ADMIN_GERKON, LOW, 10);
  gerkon->setCallbackOnActivated(gerkon_onActivated);
}

void gerkon_check() {
  gerkon->check();
}

//bool gerkon_isDetecting() {
//  gerkon->check();
//  return gerkon->isActivating();
//}

bool gerkon_debug() {
  gerkon->check();
  Serial.println("Gerkon: " + String(gerkon->isActivating()));
}
