#ifndef __DOOR__
#define __DOOR__

#include "ServoMotor.hpp"

class Door  {

    ServoMotor* servoMotor;

public:
    Door(int pin);
    void open();
    void close();

};

#endif