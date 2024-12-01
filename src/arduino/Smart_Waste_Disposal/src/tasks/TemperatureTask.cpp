#include "tasks/TemperatureTask.hpp"
#include <Arduino.h>

#define MAX_TEMP 50
#define ALERT_TIME 5000

#define RESTORING_TIME 10

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
    // Serial.print("FLAG: ");
    // Serial.println(this->flag->getValue());
        
    // Serial.print("TEMPERATURE State: ");
    // Serial.print(this->state);
    // Serial.print("\tTemp: ");
    // Serial.println(this->tempSensor->getTemperature());
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
            if(this->flag->getValue() == FULL_ALLARM) this->flag->setValue(TEMPERATURE_AND_FULL_ALLARM);
            else this->flag->setValue(TEMPERATURE_ALLARM);
            this->greenLed->switchOff();
            this->redLed->switchOn();
            this->display->clear();
            this->display->setText(DISPLAY_POSITION, "PROBLEM DETECTED");
            this->door->close();
        } else if(this->tempSensor->getTemperature() <= MAX_TEMP) {
            this->state = OK;
        } 
        break;
    case RESTORING:
        if(millis() - ts >= RESTORING_TIME) {
            this->state = OK;
            this->display->clear();
            if(this->flag->getValue() == TEMPERATURE_AND_FULL_ALLARM) {
                this->flag->setValue(FULL_ALLARM);
                this->display->setText(DISPLAY_POSITION, "CONTAINER FULL");
            } else {
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

void TemperatureTask::restore() {
    if (this->state == ALLARM) {
        this->state = RESTORING;
        this->door->open();
        this->ts = millis();
    }
}
