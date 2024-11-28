#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.hpp"
#include "devices/TempSensor.hpp"

class TemperatureTask : public Task {
private:
    enum {OK, ALERT, ALLARM, RESTORING} state;
    TempSensor* tempSensor;
    long ts;
public:
    TemperatureTask(int period);
    void tick();
    void restore();
};

#endif