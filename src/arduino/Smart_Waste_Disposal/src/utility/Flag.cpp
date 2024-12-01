#include "utility/Flag.hpp"

Flag::Flag() {
    this->flag = NONE;
}

containerFlag Flag::getValue() {
    return this->flag;
}

void Flag::setValue(containerFlag value) {
    this->flag = value;
}
