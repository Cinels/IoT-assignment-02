#ifndef __FILLING_TASK__
#define __FILLING_TASK__

#include "Task.hpp"
#include "devices/WasteDetector.hpp"

class FillingTask : public Task {
private:
    enum {AVAILABLE, FULL, EMPTING} state;
    WasteDetector* wasteDetector;
public:
    FillingTask(int period);
    void tick();
    void empty();
};

#endif