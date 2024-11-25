#ifndef __BUTTON__
#define __BUTTON__

#include "utility/queue.hpp"

typedef enum buttonType {OPEN_BUTTON, CLOSE_BUTTON} buttonType;

class Button {
private:
    int pin;
    Queue* Q;
    static void openButtonPressed();
    static void closeButtonPressed();
public:
    Button(int pin, Queue* Q);
    void init(buttonType type);
};

#endif