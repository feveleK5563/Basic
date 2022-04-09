//------------------------------------------------------------------------------
// taskBase.cpp
// タスク基底クラス
//------------------------------------------------------------------------------

#include "system/task/taskBase.h"

// コンストラクタ
TaskBase::TaskBase()
    : state_(TaskState::Ready)
{
}

// デストラクタ
TaskBase::~TaskBase()
{
}

// 更新処理
void TaskBase::Update()
{
}

// タスク状態設定
void TaskBase::SetState(TaskState state)
{
    state_ = state;
}

// ポーズ設定
void TaskBase::SetPause(bool is_pause)
{
    is_pause_ = is_pause;
}

// タスク状態取得
TaskState TaskBase::GetState() const
{
    return state_;
}

// ポーズ状態か
bool TaskBase::IsPause() const
{
    return is_pause_;
}
