#include <EnableInterrupt.h>
#include <Arduino.h>
#include "utility/interrupt_utils.hpp"

void setInterrupt(uint8_t pin, void (*func)(), uint8_t mode) {
    enableInterrupt(pin, func, mode);
}