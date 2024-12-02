#ifndef __BUTTON__
#define __BUTTON__

class Button {
private:
    int pin;
public:
    Button(int pin);
    int isPressed();
};

#endif