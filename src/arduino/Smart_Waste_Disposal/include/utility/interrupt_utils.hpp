#ifndef __INTERRUPT_UTILS__
#define __INTERRUPT_UTLIS__

#include <stdint.h>

void setInterrupt(uint8_t pin, void (*func)(), uint8_t mode);

void userDetected();

void openButtonPressed();

void closeButtonPressed();

#endif