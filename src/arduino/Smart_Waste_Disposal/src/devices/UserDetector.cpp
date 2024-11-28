#include <Arduino.h>
#include "utility/interrupt_utils.hpp"
#include "devices/UserDetector.hpp"

#define CALIBRATING_TIME 10000

UserDetector::UserDetector(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

void UserDetector::init() {
    delay(CALIBRATING_TIME);
    setInterrupt(this->pin, userDetected, RISING);
}