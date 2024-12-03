#include "utility/Flag.hpp"

Flag::Flag() {
    this->alarm = NO_ALARM;
    this->instruction = NO_INSTRUCTION;
}

containerAlarm Flag::getAlarm() {
    return this->alarm;
}

containerInstruction Flag::getInstruction() {
    return this->instruction;
}

void Flag::setAlarm(containerAlarm alarm) {
    this->alarm = alarm;
}

void Flag::setInstruction(containerInstruction instruction) {
    this->instruction = instruction;
}
