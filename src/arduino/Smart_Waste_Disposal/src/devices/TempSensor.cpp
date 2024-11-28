#include <Arduino.h>
#include "devices/TempSensor.hpp"

TempSensor::TempSensor(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

float TempSensor::getTemperature() {
    int x = analogRead(this->pin);
    float temp = (((float)x * 0.00488) - 0.5) / 0.01;
    long z = map(x, 100, 1700, -4000, 12500);
    // return (float)z/100;
    return temp;
}