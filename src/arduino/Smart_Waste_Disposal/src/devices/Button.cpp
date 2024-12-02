#include "devices/Button.hpp"
#include <Arduino.h>

Button::Button(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

int Button::isPressed() {
    return digitalRead(this->pin);
}
