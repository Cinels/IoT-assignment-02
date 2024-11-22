#include "devices/ServoMotor.hpp"
#include <Arduino.h>

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
}

void ServoMotor::setAngle(int angle) {
    this->angle = angle;
    analogWrite(this->pin, getCurrent());
}

int ServoMotor::getCurrent() {
    return (int)map(this->angle, -90, 90, 0, 1024);
}