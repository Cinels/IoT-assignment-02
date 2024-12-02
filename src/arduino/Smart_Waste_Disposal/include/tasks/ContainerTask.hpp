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

typedef enum containerState {SLEEP, AWAKE, OPEN, CLOSE} containerState;


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
    ContainerTask(int period);
    void setFlag(Flag* flag);
    void setDevices(Button* openButton, Button* closeButton, Led* greenLed, Led* redLed, Display* display, Door* door, UserDetector* userDetector);
    void tick();
};

#endif
