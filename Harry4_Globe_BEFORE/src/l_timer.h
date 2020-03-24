#include "Arduino.h"

// timer 1 //

bool timer1_isRunning = false;
unsigned long timer1_lastTS = 0;
unsigned long timer1_delay = 0;

void timer1_startOnce(unsigned long delayMS) {
  timer1_delay = delayMS;
  timer1_isRunning = true;
  timer1_lastTS = millis();
}

extern void timer1_onTimeout();

void timer1_check() {
  if(timer1_isRunning
  && (millis() - timer1_lastTS) > timer1_delay) {
    timer1_isRunning = false;
    
    timer1_onTimeout();
  }
}

// timer 2 //

bool timer2_isRunning = false;
unsigned long timer2_lastTS = 0;
unsigned long timer2_delay = 0;

void timer2_startOnce(unsigned long delayMS) {
  timer2_delay = delayMS;
  timer2_isRunning = true;
  timer2_lastTS = millis();
}

extern void timer2_onTimeout();

void timer2_check() {
  if(timer2_isRunning
  && (millis() - timer2_lastTS) > timer2_delay) {
    timer2_isRunning = false;
    
    timer2_onTimeout();
  }
}

// timer 3 //

bool timer3_isRunning = false;
unsigned long timer3_lastTS = 0;
unsigned long timer3_delay = 0;

void timer3_startOnce(unsigned long delayMS) {
  timer3_delay = delayMS;
  timer3_isRunning = true;
  timer3_lastTS = millis();
}

extern void timer3_onTimeout();

void timer3_check() {
  if(timer3_isRunning
  && (millis() - timer3_lastTS) > timer3_delay) {
    timer3_isRunning = false;
    
    timer3_onTimeout();
  }
}

// timer 4 //

bool timer4_isRunning = false;
unsigned long timer4_lastTS = 0;
unsigned long timer4_delay = 0;

void timer4_startOnce(unsigned long delayMS) {
  timer4_delay = delayMS;
  timer4_isRunning = true;
  timer4_lastTS = millis();
}

extern void timer4_onTimeout();

void timer4_check() {
  if(timer4_isRunning
  && (millis() - timer4_lastTS) > timer4_delay) {
    timer4_isRunning = false;
    
    timer4_onTimeout();
  }
}

// timer 5 //

bool timer5_isRunning = false;
unsigned long timer5_lastTS = 0;
unsigned long timer5_delay = 0;

void timer5_startOnce(unsigned long delayMS) {
  timer5_delay = delayMS;
  timer5_isRunning = true;
  timer5_lastTS = millis();
}

extern void timer5_onTimeout();

void timer5_check() {
  if(timer5_isRunning
  && (millis() - timer5_lastTS) > timer5_delay) {
    timer5_isRunning = false;
    
    timer5_onTimeout();
  }
}

// timer 6 //

bool timer6_isRunning = false;
unsigned long timer6_lastTS = 0;
unsigned long timer6_delay = 0;

void timer6_startOnce(unsigned long delayMS) {
  timer6_delay = delayMS;
  timer6_isRunning = true;
  timer6_lastTS = millis();
}

extern void timer6_onTimeout();

void timer6_check() {
  if(timer6_isRunning
  && (millis() - timer6_lastTS) > timer6_delay) {
    timer6_isRunning = false;
    
    timer6_onTimeout();
  }
}

// timer 7 //

bool timer7_isRunning = false;
unsigned long timer7_lastTS = 0;
unsigned long timer7_delay = 0;

void timer7_startOnce(unsigned long delayMS) {
  timer7_delay = delayMS;
  timer7_isRunning = true;
  timer7_lastTS = millis();
}

extern void timer7_onTimeout();

void timer7_check() {
  if(timer7_isRunning
  && (millis() - timer7_lastTS) > timer7_delay) {
    timer7_isRunning = false;
    
    timer7_onTimeout();
  }
}

