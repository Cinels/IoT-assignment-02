#ifndef __DOOR__
#define __DOOR__

#include "ServoMotor.hpp"

#define OPEN (90)
#define CLOSE (-90)

class Door : public ServoMotor {

public:
    void setAngle(int degrees);
};

#endif