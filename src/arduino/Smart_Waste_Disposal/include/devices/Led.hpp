#ifndef __LED__
#define __LED__

#include "interfaces/Light.hpp"

class Led : public Light {
private:
    int pin;
public:
    Led(int pin);
    void switchOn();
    void switchOff();
};

#endif