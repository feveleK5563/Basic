//------------------------------------------------------------------------------
// test_task.cpp
// テスト
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "system/task/taskBase.h"
#include "test/test_task.h"
#include "util/debugUtil.hpp"

class Test::Task : public TaskBase 
{
public:
    TaskGroup GetGroup() const override
    {
        return TaskGroup::Test;
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
        graph_handle_ = LoadGraph("resource/aoi.png");
        DEBUG_LOG("GRAPH_HANDLE : %d\n", graph_handle_);
    }

    void Finalize() override
    {
        DeleteGraph(graph_handle_);
    }

    void Update() override
    {
        if (graph_handle_ == -1)
        {
            // なんか読み込めてない
            return;
        }

        // 画像を左右に動かす
        float speed = speed_ * DeltaTime::Get();
        DrawGraph(pos_x_ - 160, pos_y_ - 66, graph_handle_, true);
        if (!left_or_right_)
        {
            // 右移動
            pos_x_ += speed;
            if (pos_x_ >= 1280)
            {
                left_or_right_ = true;
            }
        }
        else
        {
            // 左移動
            pos_x_ -= speed;
            if (pos_x_ <= 0)
            {
                left_or_right_ = false;
            }
        }
    }

    //-----------------------------------------------------

    void SetPos(float x, float y)
    {
        pos_x_ = x;
        pos_y_ = y;
    }

    void SetSpeed(float speed)
    {
        speed_ = speed;
    }

private:
    int graph_handle_ = -1;
    float pos_x_ = 0.f;
    float pos_y_ = 0.f;
    bool left_or_right_ = false;
    float speed_ = 1280.f;
};

//------------------------------------------------------------------------------

Test Test::CreateTask()
{
    Test task_interface;

    Task* task = new Task;
    if (TaskSystem::AddTask(task))
    {
        task_interface.task_ = task;
    }
    return task_interface;
}

void Test::SetPos(float x, float y)
{
    ASSERT(task_);
    task_->SetPos(x, y);
}

void Test::SetSpeed(float speed)
{
    ASSERT(task_);
    task_->SetSpeed(speed);
}
