#pragma once

#include <array>
#include <vector>

namespace esphome {
namespace wmbus {

  // Maximum encoded frame length for wM-Bus.
  // For an L-field of 255 bytes the packet size including CRCs is 290 bytes.
  // Mode T uses 3-out-of-6 encoding, expanding this to 435 bytes on air.
  // Use this as the upper bound for our internal buffer.
  constexpr size_t MAX_WMBUS_FRAME_LENGTH = 435;

  typedef struct WMbusData{
    uint16_t  length;
    uint8_t   lengthField;
    std::array<uint8_t, MAX_WMBUS_FRAME_LENGTH> data{};
    char      mode;
    char      block;
  } WMbusData;

  typedef struct WMbusFrame {
    std::vector<unsigned char> frame{};
    char mode;
    char block;
    int8_t rssi;
    uint8_t lqi;
  } WMbusFrame;

}
}