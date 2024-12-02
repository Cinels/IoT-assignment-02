#ifndef __TASK__
#define __TASK__

class Task {
private:  
    int myPeriod;
    int timeElapsed;
public:
    virtual void init(int period);
    virtual void tick() = 0;
    bool updateAndCheckTime(int basePeriod);
};

#endif

