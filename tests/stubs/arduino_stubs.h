#pragma once
#include <cstdint>

using byte = uint8_t;
#define INPUT 0

extern unsigned long __millis;
extern int __digital_pins[256];

inline void pinMode(uint8_t, uint8_t) {}
inline int digitalRead(uint8_t pin) { return __digital_pins[pin]; }
inline void delay(unsigned long ms) { __millis += ms; }
inline unsigned long millis() { return __millis; }
