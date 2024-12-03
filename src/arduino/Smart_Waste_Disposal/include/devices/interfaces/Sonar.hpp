#ifndef __SONAR__
#define __SONAR__

/// @brief Abstract class to use a sonar sensor.
class Sonar {
private:
    virtual void trigger() = 0;
public:
    /// @brief Restrives the distance perceived by the sensor.
    /// @return the measured distance.
    virtual float getDistance() = 0;
    
    /// @brief Default ambient temperature.
    const float temperature = 20;
    
    /// @brief Default conversion constant.
    const float vs = 331.45 + 0.62*temperature;
};

#endif
