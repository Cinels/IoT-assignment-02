#include "utility/Flag.hpp"

Flag::Flag() {
    this->allarm = NO_ALLARM;
    this->instruction = NO_INSTRUCTION;
}

containerAllarm Flag::getAllarm() {
    return this->allarm;
}

containerInstruction Flag::getInstruction() {
    return this->instruction;
}

void Flag::setAllarm(containerAllarm alarm) {
    this->allarm= allarm;
}

void Flag::setInstruction(containerInstruction instruction) {
    this->instruction = instruction;
}
