#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.hpp"

#define MAX_TASKS 4

/// @brief Class to use a simple cooperative scheduler.
class Scheduler {
private:
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  unsigned long ts;
public:
  /// @brief Initialize the scheduler by setting his base period.
  /// @param basePeriod the base period every which the scheduler will try to execute every task.
  void init(int basePeriod);  
  
  /// @brief Adds a task in the scheduler list of tasks.
  /// @param task the task to be added to the scheduler's list.
  /// @return true if the task has been added, false otherwise.
  virtual bool addTask(Task* task);  
  
  /// @brief The running method, every time is called it checks if the base time is elapsed and if so
  /// it checks if can execute any task, otherwise it waits until his base time is elapsed.
  virtual void schedule();
};

#endif
