#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.hpp"

#define MAX_TASKS 4

class Scheduler {
  
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  unsigned long ts;

public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif