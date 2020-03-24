#ifndef G_WDT_H
#define G_WDT_H

#include <avr/wdt.h>
#include <Ethernet2.h>

EthernetServer resetServer(44444); // Reset Server
EthernetClient resetClient = 0;


void wdTimer_reset() {
  wdt_enable(WDTO_60MS);
  delay(1000);
}

void resetServer_init(){
  resetServer.begin();
}


void wdTimer_init() {
  wdt_enable(WDTO_8S);
}

void wdTimer_check() {
  wdt_reset();
}


void resetServer_check(){
  resetClient = resetServer.available();
  if (resetClient){  
      unsigned long millis_cur = millis();
        while(millis() - millis_cur > 500); //задержка на чтение запроса от браузера
          resetClient.flush();   
        	resetClient.println(F("HTTP/1.1 200 OK"));
          resetClient.println(F("Content-Type: text/html"));
          resetClient.println(F("Connnection: close"));
          resetClient.println();
         // resetClient.println(F("<!DOCTYPE HTML>"));
         // resetClient.println(F("<html>"));
          resetClient.println(F("OK"));
         // resetClient.println(F("</html>"));
    resetClient.stop();
    console->println(F("ResetServer reset"));
    wdTimer_reset();    
  }
}

#endif