//------------------------------------------------------------------------------
// <name>_task.cpp
// 説明
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "system/task/taskBase.h"
#include "util/debugUtil.hpp"

class <Name>::Task : public TaskBase 
{
public:
    TaskGroup GetGroup() const override
    {
        return TaskGroup::;
    }

public:
    explicit Task()
        : TaskBase()
    {
    }

    virtual ~Task()
    {
    }

    void Initialize() override
    {
    }

    void Finalize() override
    {
    }

    void Update() override
    {
    }

private:
};

//------------------------------------------------------------------------------

<Name> Test::CreateTask()
{
    <Name> task_interface;

    <Name>* task = new Task;
    if (TaskSystem::AddTask(task))
    {
        task_interface.task_ = task;
    }
    return task_interface;
}
