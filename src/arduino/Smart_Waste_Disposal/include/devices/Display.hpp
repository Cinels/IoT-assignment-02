#ifndef __DISPLAY__
#define __DISPLAY__

#include <LiquidCrystal_I2C.h>

#define DISPLAY_POSITION 0, 1
#define DISPLAY_POSITION_2 0, 2

/// @brief Class to use I2C Display with dimensions 20 x 4.
class Display {
private:
    LiquidCrystal_I2C* lcd;
public:
    /// @brief Display constructor, it creates an lcd I2C display.
    /// @note Display dimension is 20 x 4.
    Display();

    /// @brief Initialize the display, set the backlight off and eventually clears it.
    void init();
    
    /// @brief Prints a message on the display starting in given position.
    /// @param row starting row to print.
    /// @param col starting column to print.
    /// @param text the message to print.
    void setText(int row, int col, String text);
    
    /// @brief Clears the display content and sets the backlight off.
    void clear();
};

#endif
