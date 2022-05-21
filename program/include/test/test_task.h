//------------------------------------------------------------------------------
// test_task.h
// 説明
//------------------------------------------------------------------------------

#pragma once

#include "system/task/taskBase.h"

class Test_Task : public TaskBase
{
public:
    explicit Test_Task();
    virtual ~Test_Task();

    // 初期化
    void Initialize() override;

    // 終了処理
    void Finalize() override;

    // 更新
    void Update() override;

    // グループ取得
    TaskGroup GetGroup() const override
    {
        return TaskGroup::Test;
    }

private:
    class Impl;
    Impl* impl_;
};
