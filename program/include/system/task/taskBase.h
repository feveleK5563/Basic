//------------------------------------------------------------------------------
// taskBase.h
// タスク基底クラス
//------------------------------------------------------------------------------

#pragma once

#include "system/task/taskGroup.hpp"
#include "system/task/taskSystem.h"

class TaskBase
{
public:
    // コンストラクタ
    TaskBase();

    // デストラクタ
    virtual ~TaskBase();

    // 初期化
    virtual void Initialize() = 0;

    // 終了処理
    virtual void Finalize() = 0;

    // 更新処理
    virtual void Update() = 0;

    //----------------------------------------------------------------------

    // タスク状態設定
    void SetState(TaskState state);

    // ポーズ設定
    void SetPause(bool is_pause);

    //----------------------------------------------------------------------

    // グループ取得
    virtual TaskGroup GetGroup() const = 0;

    // タスク状態取得
    TaskState GetState() const;

    // ポーズ状態か
    bool IsPause() const;

private:
    TaskState state_;       // タスク状態
    bool is_pause_ = false; // ポーズ状態
};
