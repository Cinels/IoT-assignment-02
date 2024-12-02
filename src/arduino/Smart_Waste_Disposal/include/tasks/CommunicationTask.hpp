#ifndef __COMMUNICATION_TASK__
#define __COMMUNICATION_TASK__

#include "utility/Flag.hpp"
#include "tasks/Task.hpp"
#include "tasks/FillingTask.hpp"
#include "tasks/TemperatureTask.hpp"
#include "devices/WasteDetector.hpp"
#include "devices/TempSensor.hpp"

class CommunicationTask : public Task {
private:
    Flag* flag;
    WasteDetector* wasteDetector;
    TempSensor* tempSensor;
public:
    CommunicationTask(int period);
    void setFlag(Flag* flag);
    void setDevices(WasteDetector* wasteDetector, TempSensor* tempSensor);
    void tick();
};

#endif
