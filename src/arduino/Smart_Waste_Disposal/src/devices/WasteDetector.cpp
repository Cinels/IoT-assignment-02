#include <Arduino.h>
#include "devices/WasteDetector.hpp"

WasteDetector::WasteDetector(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

void WasteDetector::trigger() {
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin, LOW);
}

float WasteDetector::getDistance() {
    this->trigger();

    float tUS = pulseIn(this->echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}

float WasteDetector::getFilling() {
    float d = this->getDistance();
    long perc = map((long)(d*100), 11, 2, 0, 100);
    return (float)perc;
}