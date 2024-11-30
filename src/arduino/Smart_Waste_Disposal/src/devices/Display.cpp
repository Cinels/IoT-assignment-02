#include "devices/Display.hpp"
// #include <LiquidCrystal_I2C.h>

Display::Display() {
    this->lcd = new LiquidCrystal_I2C(0x27,20,4);
}

void Display::init() {
    lcd->init();
    lcd->clear();
    lcd->noBacklight();
}

void Display::setText(int row, int col, String text) {
    lcd->backlight();
    lcd->setCursor(row, col);
    lcd->print(text);
}

void Display::clear() {
    lcd->clear();
    lcd->noBacklight();
}