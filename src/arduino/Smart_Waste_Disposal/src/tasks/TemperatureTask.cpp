#include "tasks/TemperatureTask.hpp"
#include <Arduino.h>

#define MAX_TEMP 50
#define ALERT_TIME 5000

#define RESTORING_TIME 10

TemperatureTask::TemperatureTask(int period) {
    Task::init(period);
    this->state = OK;
}

void TemperatureTask::init(Flag* tempflag, Flag* fillflag) {
    this->tempAllarm = tempAllarm;
    this->containerFull = containerFull;
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
        if ((millis() - ts > ALERT_TIME) && (this->tempSensor->getTemperature() > MAX_TEMP)) {
            this->state = ALLARM;
            this->tempAllarm->setValue(true);
            this->greenLed->switchOff();
            this->redLed->switchOn();
            this->display->setText(DISPLAY_POSITION, "PROBLEM DETECTED");
            this->door->close();
        } else if(this->tempSensor->getTemperature() <= MAX_TEMP) {
            this->state = OK;
        } 
        break;
    case RESTORING:
        if(millis() - ts >= RESTORING_TIME) {
            this->state = OK;
            this->tempAllarm->setValue(false);
            if(!this->containerFull->getValue()) {
                this->redLed->switchOff();
                this->greenLed->switchOn();
                this->display->setText(DISPLAY_POSITION, "PRESS OPEN TO");
                this->display->setText(DISPLAY_POSITION_2, "ENTER WASTE");
            } else {
                this->display->setText(DISPLAY_POSITION, "CONTAINER FULL");
            }
            this->door->close();
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
