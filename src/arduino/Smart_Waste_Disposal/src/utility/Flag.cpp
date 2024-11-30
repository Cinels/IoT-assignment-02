#include "utility/Flag.hpp"

Flag::Flag() {
    this->flag = false;
}

bool Flag::getValue() {
    return this->flag;
}

void Flag::setValue(bool value) {
    this->flag = value;
}
