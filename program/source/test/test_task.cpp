//------------------------------------------------------------------------------
// test_task.cpp
// 説明
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "test/test_task.h"
#include "util/debugUtil.hpp"

class Test_Task::Impl
{
public:
    Impl()
    {
    }

    ~Impl()
    {
    }

    void Initialize()
    {
        graph_handle_ = LoadGraph("resource/aoi.png");
        DEBUG_LOG("GRAPH_HANDLE : %d\n", graph_handle_);
    }

    void Finalize()
    {
        DeleteGraph(graph_handle_);
    }

    void Update()
    {
        if (graph_handle_ == -1)
        {
            // なんか読み込めてない
            return;
        }

        // 画像を左右に動かす
        float speed = 1280.f * DeltaTime::Get();
        DrawGraph(pos_x_ - 160, 340, graph_handle_, true);
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

private:
    int graph_handle_ = -1;
    float pos_x_ = 0.f;
    bool left_or_right_ = false;
};

//------------------------------------------------------------------------------

Test_Task::Test_Task()
    : TaskBase()
    , impl_(nullptr)
{
    ASSERT(!impl_);
    impl_ = new Impl();
}

Test_Task::~Test_Task()
{
    ASSERT(impl_);
    delete impl_;
}

void Test_Task::Initialize()
{
    ASSERT(impl_);
    impl_->Initialize();
}

void Test_Task::Finalize()
{
    ASSERT(impl_);
    impl_->Finalize();
}

void Test_Task::Update()
{
    ASSERT(impl_);
    impl_->Update();
}
