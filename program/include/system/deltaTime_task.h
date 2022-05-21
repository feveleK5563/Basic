//------------------------------------------------------------------------------
// deltaTime_task.h
// デルタタイム計算
//------------------------------------------------------------------------------

#pragma once

#include "system/task/taskBase.h"

class DeltaTime_Task : public TaskBase
{
public:
    explicit DeltaTime_Task();
    ~DeltaTime_Task();

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

struct DeltaTime
{
    // 経過秒数取得
    static float Get();
};
