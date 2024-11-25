#include <Arduino.h>
#include "devices/TempSensor.hpp"

TempSensor::TempSensor(int pin) {
    this->pin = pin;
}

float TempSensor::getTemperature() {
    int x = analogRead(this->pin);
    long z = map(x, 100, 1700, -400, 1250);
    return (float)z/10;
}