#ifndef __BUTTON__
#define __BUTTON__

typedef enum buttonType {OPEN_BUTTON, CLOSE_BUTTON} buttonType;

class Button {
private:
    int pin;
public:
    Button(int pin);
    void init(buttonType type);
};

#endif