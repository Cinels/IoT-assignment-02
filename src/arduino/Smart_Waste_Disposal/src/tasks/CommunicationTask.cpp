#include <Arduino.h>
#include "tasks/CommunicationTask.hpp"

#define GET_DATA 0
#define EMPTY 1
#define RESTORE 2

CommunicationTask::CommunicationTask(int period) {
    Task::init(period);
}

void CommunicationTask::setDevices(WasteDetector* wasteDetector, TempSensor* tempSensor) {
    this->wasteDetector = wasteDetector;
    this->tempSensor = tempSensor;
}

void CommunicationTask::setTasks(FillingTask* fillingTask, TemperatureTask* temperatureTask) {
    this->fillingTask = fillingTask;
    this->temperatureTask = temperatureTask;
}

void CommunicationTask::tick() {
    if(Serial.available()) {
        int message = Serial.readString().toInt();
        switch (message) {
        case GET_DATA:
            Serial.print(this->wasteDetector->getFilling());
            Serial.print(" ");
            Serial.print(this->tempSensor->getTemperature());
            Serial.println(" ");
            break;
        case EMPTY: this->fillingTask->empty(); break;
        case RESTORE: this->temperatureTask->restore(); break;
        default: break;
        }
    }
}