#ifndef __LED__
#define __LED__

#include "interfaces/Light.hpp"

/// @brief Class to manage leds.
class Led : public Light {
private:
    int pin;
public:
    /// @brief Led constructor, it creates a led.
    /// @param pin the pin where the led is connected.
    Led(int pin);

    /// @brief Turns on the led.
    void switchOn();

    /// @brief Turns off the led.
    void switchOff();
};

#endif
