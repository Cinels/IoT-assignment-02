#include "tasks/Task.hpp"

void Task::init(int period) {
    this->myPeriod = period;  
    this->timeElapsed = 0;
}

bool Task::updateAndCheckTime(int basePeriod) {
    this->timeElapsed += basePeriod;
    if (this->timeElapsed >= this->myPeriod){
        this->timeElapsed = 0;
        return true;
    } else {
        return false; 
    }
}
