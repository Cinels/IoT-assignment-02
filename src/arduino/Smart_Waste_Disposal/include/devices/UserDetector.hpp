#ifndef __USER_DETECTOR__
#define __USER_DETECTOR__

#include "interfaces/PIR.hpp"

class UserDetector : public PIR {
private:
    int pin;
    static void userDetected();
public:
    UserDetector(int pin);
    void init();
};

#endif