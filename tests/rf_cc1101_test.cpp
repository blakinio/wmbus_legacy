#include <cassert>
#include <cstring>
#include <iostream>

#include "rf_cc1101.h"

ELECHOUSE_CC1101 ELECHOUSE_cc1101;

unsigned long __millis = 0;
int __digital_pins[256] = {0};
constexpr uint8_t GDO0_PIN = 4;
constexpr uint8_t GDO2_PIN = 5;

namespace esphome {
namespace wmbus {
  bool mBusDecode(WMbusData &, WMbusFrame &) { return true; }
}
}

using namespace esphome::wmbus;

int main() {
  RxLoop loop;
  ELECHOUSE_cc1101.version = 1;
  ELECHOUSE_cc1101.marcstate = 0x01;

  loop.init(0,0,0,0,GDO0_PIN,GDO2_PIN,868.0,false);
  loop.task();

  // Valid frame
  __digital_pins[GDO2_PIN] = 1;
  loop.task();

  uint8_t preamble[3] = {WMBUS_MODE_C_PREAMBLE, WMBUS_BLOCK_A_PREAMBLE, 0};
  std::memcpy(ELECHOUSE_cc1101.rx_fifo, preamble, 3);
  ELECHOUSE_cc1101.rx_fifo_len = 3;
  ELECHOUSE_cc1101.rx_fifo_pos = 0;
  __digital_pins[GDO0_PIN] = 1;
  __digital_pins[GDO2_PIN] = 1;
  ELECHOUSE_cc1101.rxbytes = 0;
  loop.task();

  uint8_t payload[4] = {0,0,0,0};
  std::memcpy(ELECHOUSE_cc1101.rx_fifo, payload, 4);
  ELECHOUSE_cc1101.rx_fifo_len = 4;
  ELECHOUSE_cc1101.rx_fifo_pos = 0;
  __digital_pins[GDO0_PIN] = 1;
  __digital_pins[GDO2_PIN] = 1;
  ELECHOUSE_cc1101.rxbytes = 5;
  loop.task();

  __digital_pins[GDO0_PIN] = 0;
  __digital_pins[GDO2_PIN] = 0;
  ELECHOUSE_cc1101.rxbytes = 0;
  loop.task();
  loop.task();

  // Invalid preamble
  __digital_pins[GDO2_PIN] = 1;
  loop.task();

  uint8_t bad[3] = {0,0,0};
  std::memcpy(ELECHOUSE_cc1101.rx_fifo, bad, 3);
  ELECHOUSE_cc1101.rx_fifo_len = 3;
  ELECHOUSE_cc1101.rx_fifo_pos = 0;
  __digital_pins[GDO0_PIN] = 1;
  __digital_pins[GDO2_PIN] = 1;
  ELECHOUSE_cc1101.rxbytes = 0;
  loop.task();
  size_t strobe_invalid = ELECHOUSE_cc1101.strobe_history.size();
  __digital_pins[GDO0_PIN] = 0;
  __digital_pins[GDO2_PIN] = 0;
  loop.task();
  assert(ELECHOUSE_cc1101.strobe_history.size() > strobe_invalid);

  // FIFO overflow
  __digital_pins[GDO2_PIN] = 1;
  loop.task();

  std::memcpy(ELECHOUSE_cc1101.rx_fifo, preamble, 3);
  ELECHOUSE_cc1101.rx_fifo_len = 3;
  ELECHOUSE_cc1101.rx_fifo_pos = 0;
  __digital_pins[GDO0_PIN] = 1;
  __digital_pins[GDO2_PIN] = 1;
  ELECHOUSE_cc1101.rxbytes = 0;
  loop.task();

  __digital_pins[GDO0_PIN] = 0;
  __digital_pins[GDO2_PIN] = 1;
  ELECHOUSE_cc1101.rxbytes = 0x80;
  ELECHOUSE_cc1101.marcstate = 0x11;
  size_t strobe_over = ELECHOUSE_cc1101.strobe_history.size();
  loop.task();
  assert(ELECHOUSE_cc1101.strobe_history.size() > strobe_over);

  std::cout << "All tests passed\n";
  return 0;
}

