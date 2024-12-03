#ifndef __USER_DETECTOR__
#define __USER_DETECTOR__

#include "interfaces/PIR.hpp"

/// @brief Class to manage an user detector.
class UserDetector : public PIR {
private:
    int pin;
public:
    /// @brief User detector constructor, it creates an user detector. 
    /// @param pin the pin where the user detector is connected.
    UserDetector(int pin);

    /// @brief Initialize the user detector by calibrating it and attaching an interrupt.
    void init();

    /// @brief Dummy interrupt handler to wake up the system if is in sleep mode. 
    static void userDetected();
};

#endif
