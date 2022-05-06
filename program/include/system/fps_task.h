//------------------------------------------------------------------------------
// fps_task.h
// FPS制御
//------------------------------------------------------------------------------

#pragma once

#include "system/task/taskBase.h"

class Fps_Task : public TaskBase
{
public:
    explicit Fps_Task();
    ~Fps_Task();

    // 初期化
    void Initialize() override;

    // 終了処理
    void Finalize() override;

    // 更新
    void Update() override;

    // グループ取得
    TaskGroup GetGroup() const override
    {
        return TaskGroup::Fps;
    }
};

struct Fps
{
    // 垂直同期設定（DXライブラリ起動前にしか設定できない）
    static void SetUseVSync(bool b);

    // 経過秒数取得
    static float GetDeltaTime();
};
