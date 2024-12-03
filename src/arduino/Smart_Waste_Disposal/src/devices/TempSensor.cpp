#include <Arduino.h>
#include "devices/TempSensor.hpp"

TempSensor::TempSensor(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

float TempSensor::getTemperature() {
    int x = analogRead(this->pin);
    float temp = (((float)x * 0.00488) - 0.5) / 0.01;
    return temp;
}
