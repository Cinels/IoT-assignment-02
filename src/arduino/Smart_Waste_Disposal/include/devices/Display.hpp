#ifndef __DISPLAY__
#define __DISPLAY__

#include <LiquidCrystal_I2C.h>

#define DISPLAY_POSITION 0, 1
#define DISPLAY_POSITION_2 0, 2

class Display {
private:
    LiquidCrystal_I2C* lcd;
public:
    Display();
    void init();
    void setText(int row, int col, String text);
    void clear();
};

#endif