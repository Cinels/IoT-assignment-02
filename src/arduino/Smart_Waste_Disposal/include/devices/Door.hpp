#ifndef __DOOR__
#define __DOOR__

#include "ServoMotor.hpp"

class Door  {
private:
    ServoMotor* servoMotor;
public:
    Door(int pin);
    void open();
    void close();   
};

#endif
