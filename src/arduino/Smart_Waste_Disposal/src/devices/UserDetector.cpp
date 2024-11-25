#include <Arduino.h>
#include "devices/UserDetector.hpp"

UserDetector::UserDetector(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

void UserDetector::init() {
    //associa ad un interrupt
}