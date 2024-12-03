#ifndef __CONTAINER_TASK__
#define __CONTAINER_TASK__

#include "utility/Flag.hpp"
#include "tasks/Task.hpp"
#include "tasks/FillingTask.hpp"
#include "tasks/TemperatureTask.hpp"
#include "devices/Button.hpp"
#include "devices/Led.hpp"
#include "devices/Display.hpp"
#include "devices/Door.hpp"
#include "devices/UserDetector.hpp"

/// @brief Enumeration to track the state of the task.
typedef enum containerState {SLEEP, AWAKE, OPEN, CLOSE} containerState;

/// @brief Task to manage a waste container.
class ContainerTask : public Task {
private:
    containerState state;
    Flag* flag;
    Button* openButton;
    Button* closeButton;
    Led* greenLed;
    Led* redLed;
    Display* display;
    Door* door;
    UserDetector* userDetector;
    long ts;
public:
    /// @brief Task constructor, it creates a task with a base period.
    /// @param period the base period every which the task must be performed.
    ContainerTask(int period);

    /// @brief Sets the flag object which keeps trak of alarms and instruction to be communicated among theads.
    /// @param flag the flag to communicate among threads.
    void setFlag(Flag* flag);

    /// @brief Set devices to operate with.
    /// @param openButton the button to open the container.
    /// @param closeButton the button to close the container.
    /// @param greenLed the led that indicates that the container is available.
    /// @param redLed the led that indicates that the container is not available.
    /// @param display the display that show to the user messages.
    /// @param door the door that opens and closes the container.
    /// @param userDetector the user sensor that perceives if an user is present and wakes up the container.
    void setDevices(Button* openButton, Button* closeButton, Led* greenLed, Led* redLed, Display* display, Door* door, UserDetector* userDetector);

    /// @brief the running method, every time is called it checks if the base time is elapsed and if so, 
    /// depending on the state of the container performs some actions.
    void tick();
};

#endif
