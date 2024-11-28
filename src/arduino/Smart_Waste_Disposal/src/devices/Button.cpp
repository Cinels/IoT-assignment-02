#include "devices/Button.hpp"
#include "utility/interrupt_utils.hpp"
#include <Arduino.h>

Button::Button(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

void Button::init(buttonType type) {
    switch (type) {
    case OPEN_BUTTON: setInterrupt(this->pin, openButtonPressed, RISING); break;
    case CLOSE_BUTTON: setInterrupt(this->pin, closeButtonPressed, RISING); break;
    default: break;
    }
}

