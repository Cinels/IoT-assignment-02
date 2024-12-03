#include "tasks/Scheduler.hpp"
#include <Arduino.h>

void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    this->nTasks = 0;
    this->ts = millis();
}

bool Scheduler::addTask(Task* task) {
    if(this->nTasks < MAX_TASKS) {
        this->taskList[this->nTasks++] = task;
        return true;
    }
    return false;
}

void Scheduler::schedule() {
    if(millis() - ts >= (unsigned long)this->basePeriod) {
        for (int i = 0; i < this->nTasks; i++) {
            if (this->taskList[i]->updateAndCheckTime(this->basePeriod)) {
                this->taskList[i]->tick();
            }
        }
        ts = millis();
    }
}
