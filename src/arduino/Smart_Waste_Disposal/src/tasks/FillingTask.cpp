#include "tasks/FillingTask.hpp"
#include <Arduino.h>

#define CONTAINER_FULL 100.0

#define EMPTY_TIME 15000

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
            if(this->flag->getAlarm() == TEMPERATURE_ALARM) this->flag->setAlarm(TEMPERATURE_AND_FULL_ALARM);
            else {
                this->flag->setAlarm(FULL_ALARM);
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
            this->state = EMPTYING;
            this->door->open();
            this->ts = millis();
        }
        break;
    case EMPTYING:
        if(millis() - this->ts >= EMPTY_TIME) {
            this->state = AVAILABLE;
            if(this->flag->getAlarm() == TEMPERATURE_AND_FULL_ALARM) this->flag->setAlarm(TEMPERATURE_ALARM);
            else {
                this->flag->setAlarm(NO_ALARM);
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
