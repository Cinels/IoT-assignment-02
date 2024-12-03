#include "tasks/TemperatureTask.hpp"
#include <Arduino.h>

#define MAX_TEMP 50
#define ALERT_TIME 5000

#define RESTORING_TIME 15000

TemperatureTask::TemperatureTask(int period) {
    Task::init(period);
    this->state = OK;
}

void TemperatureTask::setFlag(Flag* flag) {
    this->flag = flag;
}

void TemperatureTask::setDevices(TempSensor* tempSensor, Led* greenLed, Led* redLed, Display* display, Door* door) {
    this->tempSensor = tempSensor;
    this->greenLed = greenLed;
    this->redLed = redLed;
    this->display = display;
    this->door = door;
}

void TemperatureTask::tick() {
    switch(this->state) {
    case OK:
        if (this->tempSensor->getTemperature() > MAX_TEMP) {
            this->state = ALERT;
            this->ts = millis();
        }
        break;
    case ALERT:
        if ((millis() - ts > ALERT_TIME) && (this->tempSensor->getTemperature() > MAX_TEMP)) {
            this->state = ALARM;
            if(this->flag->getAlarm() == FULL_ALARM) this->flag->setAlarm(TEMPERATURE_AND_FULL_ALARM);
            else this->flag->setAlarm(TEMPERATURE_ALARM);
            this->greenLed->switchOff();
            this->redLed->switchOn();
            this->display->clear();
            this->display->setText(DISPLAY_POSITION, "PROBLEM DETECTED");
            this->door->close();
        } else if(this->tempSensor->getTemperature() <= MAX_TEMP) {
            this->state = OK;
        } 
        break;
    case ALARM:
        if (this->flag->getInstruction() == RESTORE_INSTRUCTION || this->flag->getInstruction() == EMPTY_AND_RESTORE_INSTRUCTION) {
            if(this->flag->getInstruction() == RESTORE_INSTRUCTION) this->flag->setInstruction(NO_INSTRUCTION);
            else this->flag->setInstruction(EMPTY_INSTRUCTION);
            this->state = RESTORING;
            this->door->open();
            this->ts = millis();
        }
        break;
    case RESTORING:
        if(millis() - ts >= RESTORING_TIME) {
            this->state = OK;
            this->display->clear();
            if(this->flag->getAlarm() == TEMPERATURE_AND_FULL_ALARM) {
                this->flag->setAlarm(FULL_ALARM);
                this->display->setText(DISPLAY_POSITION, "CONTAINER FULL");
            } else {
                this->flag->setAlarm(NO_ALARM);
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
