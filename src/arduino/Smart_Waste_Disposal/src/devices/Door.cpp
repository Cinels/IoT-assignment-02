#include "devices/Door.hpp"
#include "devices/ServoMotor.hpp"
#include <Arduino.h>

#define OPEN (0)
#define CLOSE (180)

Door::Door(int pin) {
    this->servoMotor = new ServoMotor(pin);
    this->close();
}

void Door::open() {
    this->servoMotor->setPosition(OPEN);
}

void Door::close() {
    this->servoMotor->setPosition(CLOSE);
}