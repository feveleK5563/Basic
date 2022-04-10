//------------------------------------------------------------------------------
// fps_task.cpp
// FPS制御
//------------------------------------------------------------------------------

#include <chrono>
#include <thread>

#include "DxLib/DxLib.h"
#include "system/fps_task.h"
#include "util/various.hpp"

class Fps_Impl
{
public:
    Fps_Impl()
    {
    }

    ~Fps_Impl()
    {
    }

    void Initialize()
    {
        // システム時間を取得
        check_time_ = GetNowHiPerformanceCount();

        // 最初の経過時間は適当に設定
        delta_time_ = 0.000001f;
    }

    void Finalize()
    {
    }

    void Update()
    {
        // 現時刻を取得して、差分を計算
        LONGLONG current_time = GetNowHiPerformanceCount();
        LONGLONG dif_time = current_time - check_time_;

        // 前回取得した時間からの経過時間を秒に変換
        // (マイクロ秒単位なので 1000000 で割る)
        delta_time_ = dif_time / 1000000.f;

        // 1秒経過（60フレーム）毎に処理する
        if (fps_count_ == FPS_COUNT)
        {
            fps_ = 1000000.f / (dif_time / (float)FPS_COUNT);
            fps_count_ = 0;
            check_time_ = current_time;
        }
        ++fps_count_;

        // 待機時間計算
        LONGLONG wait_time = fps_count_ * 1000000 / FPS_COUNT - dif_time;
        if (wait_time > 0)
        {
            // 待機
            std::this_thread::sleep_for(
                std::chrono::microseconds(wait_time));
        }

#ifdef _DEBUG
        DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", fps_);
#endif
    }

private:
    void Count()
    {

    }

    void Wait()
    {

    }

private:
    static const int FPS_COUNT = 60;

    LONGLONG check_time_    = 0;
    float delta_time_       = 0.f;
    int fps_count_  = 0;
    float fps_      = 0.f;
};

static Fps_Impl* impl = nullptr;

//------------------------------------------------------------------------------

Fps_Task::Fps_Task()
    : TaskBase()
{
    ASSERT(!impl);
    impl = new Fps_Impl();
}

Fps_Task::~Fps_Task()
{
    ASSERT(impl);
    delete impl;
}

void Fps_Task::Initialize()
{
    ASSERT(impl);
    impl->Initialize();
}

void Fps_Task::Finalize()
{
    ASSERT(impl);
    impl->Finalize();
}

void Fps_Task::Update()
{
    ASSERT(impl);
    impl->Update();
}
