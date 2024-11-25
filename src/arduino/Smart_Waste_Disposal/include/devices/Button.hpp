#ifndef __BUTTON__
#define __BUTTON__

class Button {
private:
    int pin;
    long prevts;
public:
    Button(int pin);
    void init(/*open-close, coda*/);
};

#endif