#ifndef __LIGHT__
#define __LIGHT__

/// @brief Abstract class to manage any light source.
class Light {
public:
    /// @brief Turns on the light.
    virtual void switchOn() = 0;

    /// @brief Turns off the light.
    virtual void switchOff() = 0;
};

#endif
