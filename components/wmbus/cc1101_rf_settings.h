#pragma once

#include <ELECHOUSE_CC1101_SRC_DRV.h>

struct Cc1101RegSetting {
  uint8_t reg;
  uint8_t val;
};

// based on https://www.ti.com/lit/an/swra234a/swra234a.pdf
// Type B configuration
constexpr Cc1101RegSetting kTmodeConfig[] = {
  {CC1101_IOCFG2,   0x06}, // GDO2 output pin configuration
  {CC1101_IOCFG1,   0x2E}, // GDO1 output pin configuration
  {CC1101_IOCFG0,   0x00}, // GDO0 output pin configuration
  {CC1101_FIFOTHR,  0x07}, // RX/TX FIFO thresholds
  {CC1101_SYNC1,    0x54}, // SYNC1: sync word high byte
  {CC1101_SYNC0,    0x3D}, // SYNC0: sync word low byte
  {CC1101_PKTLEN,   0xFF}, // Packet length
  {CC1101_PKTCTRL1, 0x00}, // Packet automation control
  {CC1101_PKTCTRL0, 0x00}, // Packet automation control
  {CC1101_ADDR,     0x00}, // Device address
  {CC1101_CHANNR,   0x00}, // Channel number
  {CC1101_FSCTRL1,  0x08}, // Frequency synthesizer control
  {CC1101_FSCTRL0,  0x00}, // Frequency synthesizer control
  {CC1101_FREQ2,    0x21}, // Frequency control word, high byte
  {CC1101_FREQ1,    0x6B}, // Frequency control word, middle byte
  {CC1101_FREQ0,    0xD0}, // Frequency control word, low byte
  {CC1101_MDMCFG4,  0x5C}, // Modem configuration
  {CC1101_MDMCFG3,  0x04}, // Modem configuration
  {CC1101_MDMCFG2,  0x06}, // Modem configuration
  {CC1101_MDMCFG1,  0x22}, // Modem configuration
  {CC1101_MDMCFG0,  0xF8}, // Modem configuration
  {CC1101_DEVIATN,  0x44}, // Modem deviation setting
  {CC1101_MCSM2,    0x07}, // Main Radio Control State Machine
  {CC1101_MCSM1,    0x00}, // Main Radio Control State Machine
  {CC1101_MCSM0,    0x18}, // Main Radio Control State Machine
  {CC1101_FOCCFG,   0x2E}, // Frequency offset compensation
  {CC1101_BSCFG,    0xBF}, // Bit synchronization
  {CC1101_AGCCTRL2, 0x43}, // AGC control
  {CC1101_AGCCTRL1, 0x09}, // AGC control
  {CC1101_AGCCTRL0, 0xB5}, // AGC control
  {CC1101_WOREVT1,  0x87}, // Event0 timeout high byte
  {CC1101_WOREVT0,  0x6B}, // Event0 timeout low byte
  {CC1101_WORCTRL,  0xFB}, // Wake-on-radio control
  {CC1101_FREND1,   0xB6}, // Front-end RX configuration
  {CC1101_FREND0,   0x10}, // Front-end TX configuration
  {CC1101_FSCAL3,   0xEA}, // Frequency synthesizer calibration
  {CC1101_FSCAL2,   0x2A}, // Frequency synthesizer calibration
  {CC1101_FSCAL1,   0x00}, // Frequency synthesizer calibration
  {CC1101_FSCAL0,   0x1F}, // Frequency synthesizer calibration
  {CC1101_RCCTRL1,  0x41}, // RC oscillator configuration
  {CC1101_RCCTRL0,  0x00}, // RC oscillator configuration
  {CC1101_FSTEST,   0x59}, // Frequency synthesizer test
  {CC1101_PTEST,    0x7F}, // Production test
  {CC1101_AGCTEST,  0x3F}, // AGC test
  {CC1101_TEST2,    0x81}, // Various test settings
  {CC1101_TEST1,    0x35}, // Various test settings
  {CC1101_TEST0,    0x09}, // Various test settings
};
