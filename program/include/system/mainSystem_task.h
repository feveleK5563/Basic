//------------------------------------------------------------------------------
// mainSystem_task.h
// DXライブラリの起動とメインループ実行
//------------------------------------------------------------------------------

#pragma once

#include "system/task/taskBase.h"

class MainSystem_Task : public TaskBase
{
public:
    explicit MainSystem_Task();
    virtual ~MainSystem_Task();

    // 初期化
    void Initialize() override;

    // 終了処理
    void Finalize() override;

    // 更新
    void Update() override;

    // グループ取得
    TaskGroup GetGroup() const override
    {
        return TaskGroup::MainSystem;
    }

private:
    class Impl;
    static Impl* impl_;
};
