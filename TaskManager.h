#ifndef TaskManager_h
#define TaskManager_h

/**
 * Keeps track of period tasks that must be performed and calls them
 * periodically. Tasks are zero-argument void functions. They may be
 * scheduled to run at a period, in milliseconds.
 */
class TaskManager {
  
  public:
  
    /**
     * Creates a new instance of the task manager.
     */
    TaskManager();
  
    /**
     * Adds a task to be called periodically.
     *
     * @param taskFn - The function that should be called when the
     *   task needs to be run
     * @param period - The amount of time, in milliseconds, between
     *   each call of the task function
     * @return true, if the task was added, or false if the maximum
     *   number of tasks has already been scheduled
     */
    int addPeriodicTask(void (*taskFn)(), unsigned long period);
  
    /**
     * Executes any pending tasks, also updating their next execution
     * time.
     */
    void doTasks();
    
  private:
  
    /** The maximum number of tasks that can be scheduled. */
    static const int MAX_TASKS = 5;
    
    /** The number of tasks already scheduled. */
    int taskCount;
    
    /** An array of pointers to each task function. */
    void (*pFunctions[MAX_TASKS])();
    
    /** The amount of time, in milliseconds, between task executions. */
    unsigned long taskPeriod[MAX_TASKS];
    
    /** The system clock time, in milliseconds, when each task should
     * be run next.
     */
    unsigned long nextExecution[MAX_TASKS];
    
};

#endif TaskManager_h
