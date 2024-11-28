#include "tasks/TemperatureTask.hpp"
#include <Arduino.h>
#include "tasks/Task.hpp"

#define MAX_TEMP 50
#define MAX_TIME 5000
#define TEMP_SENSOR_PIN A1

TemperatureTask::TemperatureTask(int period) {
    Task::init(period);
    this->tempSensor = new TempSensor(TEMP_SENSOR_PIN);
}

void TemperatureTask::tick() {
    Serial.println("TEMPERATURE TASK");
    switch(this->state) {
    case OK:
        if (this->tempSensor->getTemperature() > MAX_TEMP) {
            this->state = ALERT;
            ts = millis();
        }
        break;
    case ALERT:
        if(this->tempSensor->getTemperature() <= MAX_TEMP) {
            this->state = OK;
        } else if ((millis() - ts > MAX_TIME) && (this->tempSensor->getTemperature() > MAX_TEMP)) {
            this->state = ALLARM;
            //set global pin
        }
        break;
    default: break;
    }
}

void TemperatureTask::restore() {
    if (this->state == ALLARM) {
        this->state = RESTORING;
        //apri la porta
    }
}