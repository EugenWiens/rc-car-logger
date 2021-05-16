
#pragma once

#include <TaskSchedulerDeclarations.h>


class WorkerTask : public Task
{
public:
    virtual void setup() = 0;

    WorkerTask(Scheduler *pScheduler, unsigned long interval)
        : Task(interval, TASK_FOREVER, pScheduler, true)
    {}

protected:
    virtual void run() = 0;

private:
    virtual bool Callback() override
    {
        run();

        return true;
    }
};
