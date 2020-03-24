#ifndef G_CONSOLE_H
#define G_CONSOLE_H

#include <Ethernet2.h>

// Telnet listens on port 23
EthernetServer telnet(23); 

// Client needs to have global scope so it can be called
// from functions outside of loop, but we don't know
// what client is yet, so creating an empty object
EthernetClient telnetClient = 0; 
       
//we'll use a flag separate from client.connected
boolean telnet_connectFlag = 0; 
//time in milliseconds of last activity
unsigned long timeOfLastActivity; 
//five minutes
unsigned long allowedConnectTime = 300000; 

Stream *console;

void console_init(){
  telnet.begin();   
  console = &Serial;
}

void telnet_stop(){
  telnetClient.stop();
}

void console_check(){
  //  check new connection  //
  if (telnet.available() && !telnet_connectFlag) {
    telnet_connectFlag = 1;
    telnetClient = telnet.available();
    Serial.println(F("Telnet: Connected"));
    telnetClient.println(F(PROP_NAME " (telnet)"));
  }  

  //  check disconnected  //
  if ((telnetClient.status() == 0x1C) && telnet_connectFlag) {
    Serial.println(F("Telnet: Disconnected"));
    telnetClient.stop();
    telnet_connectFlag = 0;
  }

  //  select stream  //
  if (!telnet_connectFlag)
    console = &Serial;
  else
    console = &telnetClient;
}

#endif