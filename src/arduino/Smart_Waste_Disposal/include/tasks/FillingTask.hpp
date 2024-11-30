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

typedef enum fillingState {AVAILABLE, FULL, EMPTING} fillingState;

class FillingTask : public Task {
private:
    fillingState state;
    Flag* tempAllarm;
    Flag* containerFull;
    WasteDetector* wasteDetector;
    Led* greenLed;
    Led* redLed;
    Display* display;
    Door* door;
    long ts;
public:
    FillingTask(int period);
    void init(Flag* tempflag, Flag* fillflag);
    void setDevices(WasteDetector* wasteDetector, Led* greenLed, Led* redLed, Display* display, Door* door);
    void tick();
    void empty();
};

#endif
