#ifndef __WASTE_DETECTOR__
#define __WASTE_DETECTOR__

#include "interfaces/Sonar.hpp"

/// @brief Class to use a waste detector.
class WasteDetector : public Sonar {
private:
    int trigPin;
    int echoPin;
    void trigger();
public:
    /// @brief Waste detector constructor, it creates a waste detector.
    /// @param trigPin the pin where the sonar's trigger pin is connected.
    /// @param echoPin the pin where the sonar's echo pin is connected.
    WasteDetector(int trigPin, int echoPin);
    
    /// @brief Restrives the distance perceived by the sensor.
    /// @return the measured distance.
    float getDistance();

    /// @brief Retrives the distance converted to filling percentage .
    /// @return the filling percentage of the system.
    float getFilling();
};

#endif
