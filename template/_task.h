//------------------------------------------------------------------------------
// <name>_task.h
// 説明
//------------------------------------------------------------------------------

#pragma once

#include "system/task/taskBase.h"

class <Name>_Task : public TaskBase
{
public:
    explicit <Name>_Task();
    ~<Name>_Task();

    // 初期化
    void Initialize() override;

    // 終了処理
    void Finalize() override;

    // 更新
    void Update() override;

    // グループ取得
    TaskGroup GetGroup() const override
    {
        return TaskGroup::<Name>;
    }
};
