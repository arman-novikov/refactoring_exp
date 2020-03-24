#ifndef G_DEFINES_H
#define G_DEFINES_H

#include <SPI.h>
#include <Ethernet2.h>
#include <NetEEPROM.h>
//#define HOST_NAME "ard_eth"

//  Riddle  //
#define PROP_NAME "Harry4_EK4_Globe"

//  MQTT  //
#define MQTT_1_STRID              "globe"
#define MQTT_1_STRNAME            "Globe"
#define MQTT_1_NUMBER             15

//  MQTT Server  //
IPAddress server(192, 168, 10, 1);
#define MQTT_CLIENT_NAME PROP_NAME

//  Ethernet  //
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xA9, 0x65};
IPAddress  ip     (192, 168, 10, 65);
IPAddress  gateway(192, 168, 10, 1);
IPAddress  subnet (255, 255, 255, 0);

//  Bootloader  //
void bootloader_init(){
  NetEEPROM.writeNet(mac, ip, gateway, subnet);
}
void bootloader_debug_info(){
  NetEEPROM.printAll(&Serial);
}

#endif