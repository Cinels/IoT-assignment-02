#ifndef __SONAR__
#define __SONAR__

class Sonar {
private:
    virtual void trigger() = 0;
public:
    virtual float getDistance() = 0;
    const float temperature = 20;
    const float vs = 331.45 + 0.62*temperature;
};

#endif