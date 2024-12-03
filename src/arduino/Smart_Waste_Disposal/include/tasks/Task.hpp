#ifndef __TASK__
#define __TASK__

/// @brief Abstract task.
class Task {
private:  
    int myPeriod;
    int timeElapsed;
public:
    /// @brief Initialize the task setting the base period.
    /// @param period the base period every which the task must be performed.
    virtual void init(int period);
    
    /// @brief The running method, every time is called it checks if the base time is elapsed and if so performs some actions.
    virtual void tick() = 0;

    /// @brief Checks if the base period is elapsed from the last execution.
    /// @param basePeriod the time elapsed from the last check.
    /// @return true if the base period is elapsed, false otherwise.
    bool updateAndCheckTime(int basePeriod);
};

#endif
