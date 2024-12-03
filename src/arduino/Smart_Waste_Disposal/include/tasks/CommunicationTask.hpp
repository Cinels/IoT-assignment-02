#ifndef __COMMUNICATION_TASK__
#define __COMMUNICATION_TASK__

#include "utility/Flag.hpp"
#include "tasks/Task.hpp"
#include "tasks/FillingTask.hpp"
#include "tasks/TemperatureTask.hpp"
#include "devices/WasteDetector.hpp"
#include "devices/TempSensor.hpp"

/// @brief Task to manage serial communication.
class CommunicationTask : public Task {
    
private:
    Flag* flag;
    WasteDetector* wasteDetector;
    TempSensor* tempSensor;
public:
    /// @brief Task constructor, it creates a task with a base period.
    /// @param period the base period every which the task must be performed.
    CommunicationTask(int period);

    /// @brief Sets the flag object which keeps trak of alarms and instruction to be communicated among theads.
    /// @param flag the flag to communicate among threads.
    void setFlag(Flag* flag);

    /// @brief Sets devices to read values from.
    /// @param wasteDetector the waste detector.
    /// @param tempSensor the temperature sensor.
    void setDevices(WasteDetector* wasteDetector, TempSensor* tempSensor);

    /// @brief the running method, every time is called it checks if the base time is elapsed and if so,
    /// based on what message is arrived on the serial line, performs some actions.
    void tick();
};

#endif
