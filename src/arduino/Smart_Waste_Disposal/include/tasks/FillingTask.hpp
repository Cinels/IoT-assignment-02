#ifndef __FILLING_TASK__
#define __FILLING_TASK__

#include "utility/Flag.hpp"
#include "tasks/Task.hpp"
#include "tasks/TemperatureTask.hpp"
#include "tasks/ContainerTask.hpp"
#include "devices/WasteDetector.hpp"
#include "devices/Led.hpp"
#include "devices/Display.hpp"
#include "devices/Door.hpp"

/// @brief Enumeration to track the state of the task.
typedef enum fillingState {AVAILABLE, FULL, EMPTING} fillingState;

/// @brief Task to check the filling of an object.
class FillingTask : public Task {
private:
    fillingState state;
    Flag* flag;
    WasteDetector* wasteDetector;
    Led* greenLed;
    Led* redLed;
    Display* display;
    Door* door;
    long ts;
public:
    /// @brief Task constructor, it creates a task with a base period.
    /// @param period the base period every which the task must be performed.
    FillingTask(int period);
    
    /// @brief Sets the flag object which keeps trak of allarms and instruction to be communicated among theads.
    /// @param flag the flag to communicate among threads.
    void setFlag(Flag* flag);
    
    /// @brief Set devices to operate with.
    /// @param wasteDetector the sensor that indicates the filling percentage.
    /// @param greenLed the led that indicates that the container is available.
    /// @param redLed the led that indicates that the container is not available.
    /// @param display the display that show to the user messages.
    /// @param door the door that opens and closes the container.
    void setDevices(WasteDetector* wasteDetector, Led* greenLed, Led* redLed, Display* display, Door* door);
    
    /// @brief the running method, every time is called it checks if the base time is elapsed and if so, 
    /// depending on the state of the container performs some actions.
    void tick();
};

#endif
