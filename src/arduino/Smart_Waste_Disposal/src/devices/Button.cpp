#include "devices/Button.hpp"
#include <Arduino.h>

Button::Button(int pin) {
    this->pin = pin;
    this->prevts = millis();
}

void Button::init() {
    //associa ad un interrupt
}