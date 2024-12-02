#include "tasks/FillingTask.hpp"
#include <Arduino.h>

#define CONTAINER_FULL 100.0

#define EMPTY_TIME 10000

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
    switch (this->state) {
    case AVAILABLE:
        if (this->wasteDetector->getFilling() >= CONTAINER_FULL) {
            this->state = FULL;
            if(this->flag->getAllarm() == TEMPERATURE_ALLARM) this->flag->setAllarm(TEMPERATURE_AND_FULL_ALLARM);
            else {
                this->flag->setAllarm(FULL_ALLARM);
                this->display->clear();
                this->display->setText(DISPLAY_POSITION,"CONTAINER FULL");
            }
            this->greenLed->switchOff();
            this->redLed->switchOn();
            this->door->close();
        }
        break;
    case FULL:
        if(this->flag->getInstruction() == EMPTY_INSTRUCTION || this->flag->getInstruction() == EMPTY_AND_RESTORE_INSTRUCTION) {
            if(this->flag->getInstruction() == EMPTY_INSTRUCTION) this->flag->setInstruction(NO_INSTRUCTION);
            else this->flag->setInstruction(RESTORE_INSTRUCTION);
            this->state = EMPTING;
            this->door->open();
            this->ts = millis();
        }
        break;
    case EMPTING:
        if(millis() - this->ts >= EMPTY_TIME) {
            this->state = AVAILABLE;
            if(this->flag->getAllarm() == TEMPERATURE_AND_FULL_ALLARM) this->flag->setAllarm(TEMPERATURE_ALLARM);
            else {
                this->flag->setAllarm(NO_ALLARM);
                this->redLed->switchOff();
                this->greenLed->switchOn();
                this->display->clear();
                this->display->setText(DISPLAY_POSITION, "PRESS OPEN TO");
                this->display->setText(DISPLAY_POSITION_2, "ENTER WASTE");
            }
            this->door->close();
        }
        break;
    default: break;
    }
}
