#include <Arduino.h>
#include "devices/WasteDetector.hpp"

WasteDetector::WasteDetector(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

void WasteDetector::trigger() {
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(1);
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