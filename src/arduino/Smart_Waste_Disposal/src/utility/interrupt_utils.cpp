#include <EnableInterrupt.h>
#include <Arduino.h>
#include "utility/interrupt_utils.hpp"
// #include "devices/UserDetector.hpp"
// #include "devices/Button.hpp"

void setInterrupt(uint8_t pin, void (*func)(), uint8_t mode) {
    enableInterrupt(pin, func, mode);
}

// __attribute__((unused))
void userDetected() {
    // Serial.println("DETECTED!");
}

// __attribute__((unused))
void openButtonPressed() {
    // Serial.println("OPEN!");
}

// __attribute__((unused))
void closeButtonPressed() {
    // Serial.println("CLOSE!");
}