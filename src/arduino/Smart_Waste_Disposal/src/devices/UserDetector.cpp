#include <Arduino.h>
#include "utility/interrupt_utils.hpp"
#include "devices/UserDetector.hpp"

UserDetector::UserDetector(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

void UserDetector::init() {
    setInterrupt(this->pin, userDetected, FALLING);
}

__attribute__((unused))
static void userDetected() {}