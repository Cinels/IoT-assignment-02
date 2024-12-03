#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__

/// @brief Class to use a temperature sensor.
class TempSensor {
private:
    int pin;
public:
    /// @brief Temperature sensor constructor, it creates a temperature sensor.
    /// @param pin the pin where the temperature sensor is connected.
    TempSensor(int pin);
    
    /// @brief Restrives the perceived temperature.
    /// @return the current temperature.
    float getTemperature();
};

#endif
