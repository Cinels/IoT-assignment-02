#include "devices/Display.hpp"

Display::Display() {
    this->lcd = new LiquidCrystal_I2C(0x27,20,4);
}

void Display::init() {
    this->lcd->init();
    this->clear();
}

void Display::setText(int row, int col, String text) {
    this->lcd->backlight();
    this->lcd->setCursor(row, col);
    this->lcd->print(text);
}

void Display::clear() {
    this->lcd->clear();
    this->lcd->noBacklight();
}