#ifndef __LED__
#define __LED__

#include "Light.hpp"

class Led : public Light {

    int pin;

public:
    Led(int pin);
    void switchOn();
    void switchOff();
};

#endif