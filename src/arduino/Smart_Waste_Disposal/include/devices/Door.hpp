#ifndef __DOOR__
#define __DOOR__

#include "ServoMotor.hpp"

/// @brief Class to manage a door.
class Door {
private:
    ServoMotor* servoMotor;
public:
    /// @brief Door constructor, it creates an electric door.
    /// @param pin the pin where the door is connected to be controlled.
    Door(int pin);
    
    /// @brief Opens the door.
    void open();
    
    /// @brief Closes the door.
    void close();   
};

#endif
