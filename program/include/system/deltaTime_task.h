//------------------------------------------------------------------------------
// deltaTime_task.h
// デルタタイム計算
//------------------------------------------------------------------------------

#pragma once

class DeltaTime
{
public:
    static DeltaTime CreateTask();

    // デルタタイム取得
    static float Get();

private:
    class Task;
    static Task* task_;
};
