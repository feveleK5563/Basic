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
        if (is_use_vsync)
        {
            return;
        }

        // 現時刻を取得して、差分を計算
        LONGLONG current_time = GetNowHiPerformanceCount();
        LONGLONG dif_time = current_time - check_time_;

        // 前回取得した時間からの経過時間を秒に変換
        // (マイクロ秒単位なので 1000000 で割る)
        delta_time_ = dif_time / MIC_SEC;

        // フレーム数カウント
        if (fps_count_ == FPS_COUNT)
        {
            // 1秒毎の平均を計算
            fps_ = MIC_SEC / (dif_time / (float)FPS_COUNT);
            fps_count_ = 0;
        }
        ++fps_count_;

        // 待機時間計算
        if (dif_time < MIN_FREAM_TIME)
        {
            // 待機
            std::this_thread::sleep_for(
                std::chrono::microseconds(MIN_FREAM_TIME - dif_time));
        }
        else
        {
            DEBUG_LOG("DIF_TIME : %d\n", dif_time);
        }
        check_time_ = GetNowHiPerformanceCount();

#ifdef _DEBUG
        DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", MIN_FREAM_TIME);
        DrawFormatString(0, 15, GetColor(255, 255, 255), "%d", dif_time);
#endif
    }

    // 垂直同期設定
    void SetUseVSync(bool b)
    {
        is_use_vsync = b;
        SetWaitVSyncFlag(b);
    }

    // フレーム時間取得
    float GetDeltaTime()
    {
        return delta_time_;
    }

private:
    static constexpr LONGLONG FPS_COUNT = 60;
    static constexpr LONGLONG MIC_SEC = 1000000;
    static constexpr LONGLONG MIN_FREAM_TIME = (MIC_SEC / FPS_COUNT);

    bool is_use_vsync = false;

    LONGLONG check_time_    = 0;
    int fps_count_          = 0;
    float delta_time_       = 0.f;
    float fps_              = 0.f;
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

//------------------------------------------------------------------------------

void Fps::SetUseVSync(bool b)
{
    if (impl)
    {
        impl->SetUseVSync(b);
    }
}

float Fps::GetDeltaTime()
{
    if (impl)
    {
        return impl->GetDeltaTime();
    }

    return 0.f;
}