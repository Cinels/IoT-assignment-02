#include "tasks/FillingTask.hpp"
#include <Arduino.h>

#define CONTAINER_FULL 100.0

#define EMPTY_TIME 10

FillingTask::FillingTask(int period) {
    Task::init(period);
    this->state = AVAILABLE;
}

void FillingTask::init(Flag* tempflag, Flag* fillflag) {
    this->tempAllarm = tempAllarm;
    this->containerFull = containerFull;
}

void FillingTask::setDevices(WasteDetector* wasteDetector, Led* greenLed, Led* redLed, Display* display, Door* door) {
    this->wasteDetector = wasteDetector;
    this->greenLed = greenLed;
    this->redLed = redLed;
    this->display = display;
    this->door = door;
}

void FillingTask::tick() {
    Serial.println("FILLING TASK");
    switch (this->state) {
    case AVAILABLE:
        if (this->wasteDetector->getFilling() >= CONTAINER_FULL) {
            this->state = FULL;
            this->containerFull->setValue(true);
            this->greenLed->switchOff();
            this->redLed->switchOn();
            if(!this->tempAllarm->getValue()) this->display->setText(DISPLAY_POSITION,"CONTAINER FULL");
            this->door->close();
        }
        break;
    case EMPTING:
        if(millis() - ts >= EMPTY_TIME) {
            this->state = AVAILABLE;
            if(!this->tempAllarm->getValue()) {
                this->redLed->switchOff();
                this->greenLed->switchOn();
                this->display->setText(DISPLAY_POSITION, "PRESS OPEN TO");
                this->display->setText(DISPLAY_POSITION_2, "ENTER WASTE");
            }
            this->door->close();
        }
        break;
    default: break;
    }
}

void FillingTask::empty() {
    if(this->state == FULL) {
        this->state = EMPTING;
        this->door->open();
        this->ts = millis();
    }
}
