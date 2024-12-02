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

typedef enum temperatureState {OK, ALERT, ALLARM, RESTORING} temperatureState;

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
    TemperatureTask(int period);
    void setFlag(Flag* flag);
    void setDevices(TempSensor* tempSensor, Led* greenLed, Led* redLed, Display* display, Door* door);
    void tick();
};

#endif
