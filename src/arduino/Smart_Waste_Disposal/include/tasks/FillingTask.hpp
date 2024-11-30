#ifndef __FILLING_TASK__
#define __FILLING_TASK__

#include "Task.hpp"

class FillingTask : public Task {
private:
    enum {NOT_FULL, FULL, EMPTING} state;
public:
    FillingTask(int period);
    void tick();
};

#endif