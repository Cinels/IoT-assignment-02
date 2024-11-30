#ifndef __CONTAINER_TASK__
#define __CONTAINER_TASK__

#include "Task.hpp"

class ContainerTaks : public Task {
private:
    enum {SLEEP, AWAKE, OPEN, CLOSE} state;
public:
    ContainerTaks(int period);
    void tick();
};

#endif