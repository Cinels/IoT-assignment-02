#ifndef __FLAG__
#define __FLAG__

typedef enum containerFlag {NONE, HIGH_TEMPERATURE, FULL, HIGH_TEMPERATURE_AND_FULL} containerFlag;

class Flag {
private:
    containerFlag flag
public:
    Flag();
    containerFlag getValue();
    void setValue(containerFlag value);
};

#endif