#ifndef __WASTE_DETECTOR__
#define __WASTE_DETECTOR__

#include "Sonar.hpp"

class WasteDetector : public Sonar {
private:
    int trigPin;
    int echoPin;
    void trigger();
public:
    WasteDetector(int trigPin, int echoPin);
    float getDistance();
};

#endif