#ifndef __CONTAINER_TASK__
#define __CONTAINER_TASK__

#include "Task.hpp"

class ContainerTask : public Task {
private:
    enum {SLEEP, AWAKE, OPEN, CLOSE} state;
public:
    ContainerTask(int period);
    void tick();
};

#endif