//------------------------------------------------------------------------------
// renderSystem_task.cpp
// 描画管理
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "system/task/taskBase.h"
#include "system/renderSystem_task.h"
#include "util/debugUtil.hpp"

class RenderSystem::Task : public TaskBase 
{
public:
    TaskGroup GetGroup() const override
    {
        return TaskGroup::RenderSystem;
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

RenderSystem::Task* RenderSystem::task_ = nullptr;

RenderSystem RenderSystem::CreateTask()
{
    DEBUG_ASSERT(!task_);
    RenderSystem task_interface;

    Task* task = new Task;
    if (TaskSystem::AddTask(task))
    {
        task_interface.task_ = task;
    }
    return task_interface;
}
