#ifndef __INTERRUPT_UTILS__
#define __INTERRUPT_UTLIS__

void setInterrupt(uint8_t pin, void (*func)(), uint8_t mode);

#endif