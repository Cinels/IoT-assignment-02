#include <Arduino.h>
#include "tasks/CommunicationTask.hpp"

#define GET_DATA 0
#define EMPTY 1
#define EMPTY_GET 10
#define RESTORE 2
#define RESTORE_GET 20

CommunicationTask::CommunicationTask(int period) {
    Task::init(period);
}

void CommunicationTask::setFlag(Flag* flag) {
    this->flag = flag;
}

void CommunicationTask::setDevices(WasteDetector* wasteDetector, TempSensor* tempSensor) {
    this->wasteDetector = wasteDetector;
    this->tempSensor = tempSensor;
}

void CommunicationTask::tick() {
    if(Serial.available()) {
        int message = Serial.readString().toInt();
        switch (message) {
        case GET_DATA:
            Serial.print(this->flag->getAllarm());
            Serial.print(" ");
            Serial.print(this->wasteDetector->getFilling());
            Serial.print(" ");
            Serial.print(this->tempSensor->getTemperature());
            Serial.println(" ");
            break;
        case EMPTY:
        case EMPTY_GET:
            if(this->flag->getInstruction() == NO_INSTRUCTION) this->flag->setInstruction(EMPTY_INSTRUCTION);
            else this->flag->setInstruction(EMPTY_AND_RESTORE_INSTRUCTION);
            break;
        case RESTORE:
        case RESTORE_GET:
            if(this->flag->getInstruction() == NO_INSTRUCTION) this->flag->setInstruction(RESTORE_INSTRUCTION);
            else this->flag->setInstruction(EMPTY_AND_RESTORE_INSTRUCTION);
            break;
        default: 
            break;
        }
    }
}
