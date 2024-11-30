#include "tasks/TemperatureTask.hpp"
#include <Arduino.h>

#define MAX_TEMP 50
#define ALERT_TIME 5000

#define DISPLAY_POSITION 0, 1
#define DISPLAY_POSITION_2 0, 2

#define RESTORING_TIME 10

TemperatureTask::TemperatureTask(int period) {
    Task::init(period);
    this->state = OK;
}

void TemperatureTask::init(Flag* tempflag, Flag* fillflag) {
    this->tempFlag = tempFlag;
    this->fillFlag = fillFlag;
}

void TemperatureTask::setDevices(TempSensor* tempSensor, Led* greenLed, Led* redLed, Display* display, Door* door) {
    this->tempSensor = tempSensor;
    this->greenLed = greenLed;
    this->redLed = redLed;
    this->display = display;
    this->door = door;
}

void TemperatureTask::tick() {
    Serial.println("TEMPERATURE TASK");
    switch(this->state) {
    case OK:
        if (this->tempSensor->getTemperature() > MAX_TEMP) {
            this->state = ALERT;
            this->ts = millis();
        }
        break;
    case ALERT:
        if(this->tempSensor->getTemperature() <= MAX_TEMP) {
            this->state = OK;
        } else if ((millis() - ts > ALERT_TIME) && (this->tempSensor->getTemperature() > MAX_TEMP)) {
            this->state = ALLARM;
            this->tempFlag->setFlag(true);
            this->greenLed->switchOff();
            this->redLed->switchOn();
            this->display->setText(DISPLAY_POSITION, "PROBLEM DETECTED");
            this->door->close();
        }
        break;
    case RESTORING:
        if(millis() - ts >= RESTORING_TIME) {
            this->state = OK;
            this->tempFlag->setFlag(false);
            if(!this->fillFlag->getFlag()) {
                this->redLed->switchOff();
                this->greenLed->switchOn();
                this->display->setText(DISPLAY_POSITION, "PRESS OPEN TO");
                this->display->setText(DISPLAY_POSITION_2, "ENTER WASTE");
            }
            this->door->close();
            this->ts = millis();
        }
        break;
    default: break;
    }
}

void TemperatureTask::restore() {
    if (this->state == ALLARM) {
        this->state = RESTORING;
        this->door->open();
        this->ts = millis();
    }
}
