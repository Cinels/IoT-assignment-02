#include "devices/Door.hpp"
#include "devices/ServoMotor.hpp"

#define OPEN (90)
#define CLOSE (-90)

Door::Door(int pin) {
    this->servoMotor = new ServoMotor(pin);
    this->close();
}

void Door::open() {
    this->servoMotor->setAngle(OPEN);
}

void Door::close() {
    this->servoMotor->setAngle(CLOSE);
}