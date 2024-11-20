#include "devices/Door.hpp"

Door::Door(int pin) {
    this->pin = pin;
    this->angle = CLOSE;
}

void Door::setAngle(int angle) {
    this->angle = angle;
}