#include "tasks/FillingTask.hpp"
#include <Arduino.h>

#define CONTAINER_FULL 100.0

#define DISPLAY_POSITION 0, 1
#define DISPLAY_POSITION_2 0, 2

#define EMPTY_TIME 10

FillingTask::FillingTask(int period) {
    Task::init(period);
}

void FillingTask::setDevices(WasteDetector* wasteDetector, Led* greenLed, Led* redLed, Display* display, Door* door) {
    this->wasteDetector = wasteDetector;
    this->greenLed = greenLed;
    this->redLed = redLed;
    this->display = display;
    this->door = door;
}

void FillingTask::init(Flag* tempflag, Flag* fillflag) {
    this->tempAllarm = tempAllarm;
    this->containerFull = containerFull;
    this->state = AVAILABLE;
}

void FillingTask::tick() {
    Serial.print("FILLING State: ");
    Serial.print(this->state);
    Serial.print("\tFilling: ");
    Serial.print(this->wasteDetector->getFilling());
    Serial.print(" >= ");
    Serial.print(CONTAINER_FULL);
    Serial.print(" -> ");
    Serial.println(this->wasteDetector->getFilling() >= CONTAINER_FULL ? "True" : "False");
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
