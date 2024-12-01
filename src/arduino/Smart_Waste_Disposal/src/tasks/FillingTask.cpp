#include "tasks/FillingTask.hpp"
#include <Arduino.h>

#define CONTAINER_FULL 100.0

#define DISPLAY_POSITION 0, 1
#define DISPLAY_POSITION_2 0, 2

#define EMPTY_TIME 10

FillingTask::FillingTask(int period) {
    Task::init(period);
    this->state = AVAILABLE;
}

void FillingTask::setFlag(Flag* flag) {
    this->flag = flag;
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
        if (this->wasteDetector->getFilling() >= FULL) {
            this->state = FULL;
            if(this->flag->getValue() == TEMPERATURE_ALLARM) this->flag->setValue(TEMPERATURE_AND_FULL_ALLARM);
            else {
                this->flag->setValue(FULL_ALLARM);
                this->display->setText(DISPLAY_POSITION,"CONTAINER FULL");
            }
            this->greenLed->switchOff();
            this->redLed->switchOn();
            this->door->close();
        }
        break;
    case EMPTING:
        if(millis() - ts >= EMPTY_TIME) {
            this->state = AVAILABLE;
                if(this->flag->getValue() == TEMPERATURE_AND_FULL_ALLARM) this->flag->setValue(TEMPERATURE_ALLARM);
            else {
                this->flag->setValue(NONE);
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
