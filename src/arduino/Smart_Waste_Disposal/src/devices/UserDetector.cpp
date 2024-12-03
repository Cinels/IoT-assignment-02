#include <Arduino.h>
#include "devices/UserDetector.hpp"

#define CALIBRATING_TIME 10000

UserDetector::UserDetector(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

void UserDetector::init() {
    delay(CALIBRATING_TIME);
    attachInterrupt(digitalPinToInterrupt(this->pin), UserDetector::userDetected, CHANGE); 
}

void UserDetector::userDetected() {}
