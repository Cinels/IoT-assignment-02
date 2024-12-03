#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "utility/Flag.hpp"
#include "tasks/Task.hpp"
#include "tasks/FillingTask.hpp"
#include "tasks/ContainerTask.hpp"
#include "devices/TempSensor.hpp"
#include "devices/Led.hpp"
#include "devices/Display.hpp"
#include "devices/Door.hpp"

/// @brief Enumeration to track the state of the task.
typedef enum temperatureState {OK, ALERT, ALLARM, RESTORING} temperatureState;

/// @brief Task to check the temperature of an object.
class TemperatureTask : public Task {
private:
    temperatureState state;
    Flag* flag;
    TempSensor* tempSensor;
    Led* greenLed;
    Led* redLed;
    Display* display;
    Door* door;
    long ts;
public:
    /// @brief Task constructor, it creates a task with a base period.
    /// @param period the base period every which the task must be performed.
    TemperatureTask(int period);

    /// @brief Sets the flag object which keeps trak of allarms and instruction to be communicated among theads.
    /// @param flag the flag to communicate among threads.
    void setFlag(Flag* flag);

    /// @brief Set devices to operate with.
    /// @param tempSensor the sensor that indicates the temperature.
    /// @param greenLed the led that indicates that the container is available.
    /// @param redLed the led that indicates that the container is not available.
    /// @param display the display that show to the user messages.
    /// @param door the door that opens and closes the container.
    void setDevices(TempSensor* tempSensor, Led* greenLed, Led* redLed, Display* display, Door* door);

    /// @brief the running method, every time is called it checks if the base time is elapsed and if so, 
    /// depending on the state of the task performs some actions.
    void tick();
};

#endif
