#ifndef __PIR__
#define __PIR__

/// @brief Abstract class to use PIR sensors. 
class PIR {
public:
    /// @brief Initialize the sensor.
    virtual void init() = 0;
};

#endif
