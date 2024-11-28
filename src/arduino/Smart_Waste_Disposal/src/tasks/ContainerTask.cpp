#include "tasks/ContainerTaks.hpp"
#include <Arduino.h>
#include "tasks/Task.hpp"

ContainerTaks::ContainerTaks(int period) {
    Task::init(period);
}

void ContainerTaks::tick() {
    Serial.println("CONTAINER TASK");
}