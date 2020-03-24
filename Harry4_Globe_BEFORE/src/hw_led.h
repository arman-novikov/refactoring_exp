#define PIN_RELAY_LED_1 5
#define PIN_RELAY_LED_2 6


//
//  Led 1  //
//

void led1_off() {
  digitalWrite(PIN_RELAY_LED_1, LOW);
}

void led1_on() {
  digitalWrite(PIN_RELAY_LED_1, HIGH);
}

void led1_init() {
  pinMode(PIN_RELAY_LED_1, OUTPUT);
  led1_off();
}

//
//  Led 2  //
//

void led2_off() {
  digitalWrite(PIN_RELAY_LED_2, LOW);
}

void led2_on() {
  digitalWrite(PIN_RELAY_LED_2, HIGH);
}

void led2_init() {
  pinMode(PIN_RELAY_LED_2, OUTPUT);
  led2_off();
}

