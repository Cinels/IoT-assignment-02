#include "devices/Button.hpp"
#include "utility/interrupt_utils.hpp"
#include <Arduino.h>

Button::Button(int pin, Queue* Q) {
    this->pin = pin;
    this->Q = Q;
}

void Button::init(buttonType type) {
    switch (type) {
    case OPEN_BUTTON: setInterrupt(this->pin, openButtonPressed, FALLING); break;
    case CLOSE_BUTTON: setInterrupt(this->pin, closeButtonPressed, FALLING); break;
    default: break;
    }
    
}

__attribute__((unused))
static void openButtonPressed() {
    //aggiungi in coda il fatto che sei stato premuto
}

__attribute__((unused))
static void closeButtonPressed() {
    //aggiungi in coda il fatto che sei stato premuto
}