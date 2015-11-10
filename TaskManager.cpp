#include <Arduino.h>
#include "TaskManager.h"

// Creates a new instance of the task manager.
TaskManager::TaskManager() {
  taskCount = 0;
}

// Adds a new periodic task. The first execution will be delayed
// from the current time by the period.
int TaskManager::addPeriodicTask(void (*taskFn)(), unsigned long period) {
  if (taskCount >= MAX_TASKS) {
    return 0;
  }
  
  pFunctions[taskCount] = taskFn;
  taskPeriod[taskCount] = period;
  nextExecution[taskCount] = millis() + period;
  ++taskCount;
}

// Executes any tasks whose execution time has come up, and updates
// their next execution time if so. If the normal next execution time
// would be in the past, because some task took too long to run, the
// next execution will be incremented by the period until the next
// execution time is in the future. In this way, some executions may
// be skipped, if tasks take too long to run, but all executions will
// occur close to their intended time.
void TaskManager::doTasks() {
  unsigned long now = millis();
  
  for (int i=0; i < taskCount; ++i) {
    if (now >= nextExecution[i]) {
      pFunctions[i]();
      do {
        nextExecution[i] += taskPeriod[i];
      } while (nextExecution[i] <= millis());
    }
  }
}
