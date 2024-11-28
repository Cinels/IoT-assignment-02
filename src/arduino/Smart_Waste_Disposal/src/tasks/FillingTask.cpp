#include "tasks/FillingTask.hpp"
#include <Arduino.h>
#include "tasks/Task.hpp"

#define TRIG_PIN 5
#define ECHO_PIN 6
#define CONTAINER_FULL 100.0

FillingTask::FillingTask(int period) {
    Task::init(period);
    this->wasteDetector = new WasteDetector(TRIG_PIN, ECHO_PIN);
}

void FillingTask::tick() {
    Serial.println("FILLING TASK");
    if ((this->AVAILABLE) && (this->wasteDetector->getFilling() >= CONTAINER_FULL)) {
        this->state = FULL;
        //setta il pin globale
    }        
}

void FillingTask::empty() {
    if(this->state == FULL) {
        this->state == EMPTING;
    }
}