#ifndef __COMMUNICATION_TASK__
#define __COMMUNICATION_TASK__

#include "tasks/Task.hpp"
#include "tasks/FillingTask.hpp"
#include "tasks/TemperatureTask.hpp"
#include "devices/WasteDetector.hpp"
#include "devices/TempSensor.hpp"

class CommunicationTask : public Task {
private:
    WasteDetector* wasteDetector;
    TempSensor* tempSensor;

    FillingTask* fillingTask;
    TemperatureTask* temperatureTask;
public:
    CommunicationTask(int period);
    void setDevices(WasteDetector* wasteDetector, TempSensor* tempSensor);
    void setTasks(FillingTask* fillingTask, TemperatureTask* temperatureTask);
    void tick();
};

#endif
