#pragma once
#include <Arduino.h>

constexpr char CIRCUIT_NAME[] = "Harry4_EK5_Globe";
constexpr byte IP_ENDING = 65U;
constexpr bool UPLOAD_BOOT_INFO = true;

namespace Globe_space {
  constexpr int8_t GLOBE_ERP_NUM = 15;
  constexpr char GLOBE_SOUND[] = "150";
  constexpr uint8_t REED_PIN = 2U;
  constexpr uint8_t ILLUMINATION_PIN = 5U;
  constexpr uint8_t STAINED_GLASS_PIN = 6U;
  constexpr unsigned long TIMER_OFFSET = 2000UL;
}