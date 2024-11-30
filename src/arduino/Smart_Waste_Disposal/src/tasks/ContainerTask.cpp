#include "tasks/ContainerTask.hpp"
#include <Arduino.h>
#include "tasks/Task.hpp"

ContainerTask::ContainerTask(int period) {
    Task::init(period);
}

void ContainerTask::tick() {
    Serial.println("CONTAINER TASK");
}