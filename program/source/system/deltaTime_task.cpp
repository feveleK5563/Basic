//------------------------------------------------------------------------------
// fps_task.cpp
// デルタタイム計算
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "system/deltaTime_task.h"
#include "util/debugUtil.hpp"

class DeltaTime_Impl
{
public:
    DeltaTime_Impl()
    {
    }

    ~DeltaTime_Impl()
    {
    }

    void Initialize()
    {
        // システム時間を取得
        check_time_ = GetNowHiPerformanceCount();

        // 最初の経過時間は適当に設定
        delta_time_ = 0.000001f;

#ifdef _DEBUG
        // FPS計測用
        fps_check_time_ = GetNowHiPerformanceCount();
#endif
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
        delta_time_ = dif_time / MIC_SEC_F;
        check_time_ = current_time;

#ifdef _DEBUG
        // フレーム数カウント
        ++fps_count_;
        if (current_time - fps_check_time_ > MIC_SEC)
        {
            // 1秒毎の処理回数を表示
            fps_ = fps_count_;
            fps_count_ = 0;
            fps_check_time_ = current_time;
        }

        DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", fps_);
#endif
    }

    // フレーム時間取得
    float GetDeltaTime()
    {
        return delta_time_;
    }

private:
    static constexpr LONGLONG MIC_SEC = 1000000;
    static constexpr float MIC_SEC_F = 1000000.f;

    LONGLONG check_time_ = 0;
    float delta_time_ = 0.f;

#ifdef _DEBUG
    LONGLONG fps_check_time_ = 0;
    int fps_count_ = 0;
    int fps_ = 0;
#endif
};

static DeltaTime_Impl* impl = nullptr;

//------------------------------------------------------------------------------

DeltaTime_Task::DeltaTime_Task()
    : TaskBase()
{
    ASSERT(!impl);
    impl = new DeltaTime_Impl();
}

DeltaTime_Task::~DeltaTime_Task()
{
    ASSERT(impl);
    delete impl;
}

void DeltaTime_Task::Initialize()
{
    ASSERT(impl);
    impl->Initialize();
}

void DeltaTime_Task::Finalize()
{
    ASSERT(impl);
    impl->Finalize();
}

void DeltaTime_Task::Update()
{
    ASSERT(impl);
    impl->Update();
}

//------------------------------------------------------------------------------

float DeltaTime::Get()
{
    if (impl)
    {
        return impl->GetDeltaTime();
    }

    return 0.f;
}
