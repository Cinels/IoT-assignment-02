#ifndef __DISPLAY__
#define __DISPLAY__

#include <LiquidCrystal_I2C.h>

class Display {
private:
    LiquidCrystal_I2C lcd;
public:
    Display();
    void init();
    void setText(int row, int col, String text);
};

#endif