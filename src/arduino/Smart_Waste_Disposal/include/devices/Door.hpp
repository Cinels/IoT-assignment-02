#ifndef __DOOR__
#define __DOOR__

#include "ServoMotor.hpp"

#define OPEN (90)
#define CLOSE (-90)

class Door : public ServoMotor {

    int pin;
    int angle;

public:
    Door(int pin);
protected:
    void setAngle(int angle);
};

#endif