#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__

class TempSensor {
private:
    int pin;
public:
    TempSensor(int pin);
    float getTemperature();
};

#endif