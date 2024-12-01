#ifndef __FLAG__
#define __FLAG__

typedef enum containerFlag {NONE, TEMPERATURE_ALLARM, FULL_ALLARM, TEMPERATURE_AND_FULL_ALLARM} containerFlag;

class Flag {
private:
    containerFlag flag;
public:
    Flag();
    containerFlag getValue();
    void setValue(containerFlag value);
};

#endif