#include "utility/Flag.hpp"

Flag::Flag() {
    this->flag = false;
}

bool Flag::getFlag() {
    return this->flag;
}

void Flag::setFlag(bool value) {
    this->flag = value;
}
