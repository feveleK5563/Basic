//------------------------------------------------------------------------------
// taskSystem.h
// タスクシステム
//------------------------------------------------------------------------------

#pragma once

#include "system/task/taskGroup.hpp"
#include "system/deltaTime_task.h"

class TaskBase;

enum struct TaskState
{
    Ready,  // 準備
    Active, // 稼働
    Kill,   // 消滅要請
};

class TaskSystem
{
public:
    // 初期化
    static void Initialize();

    // 終了処理
    static void Finalize();

    // メインループ
    static void MainLoop();

    // 全てのタスクを削除要請状態にする
    // ※次のフレームでTaskSystemが終了します
    static void KillAllTask();

    //----------------------------------------------------------------------

    // タスクを追加
    static bool AddTask(TaskBase* task);

    // 指定したグループのタスク個数を取得
    static int GetTaskNum(TaskGroup group);

    // 指定したグループのタスクを先頭だけ取得
    template<class T>
    static bool GetTask(TaskGroup group, const T* task_single);

    // 指定したグループのタスクをまとめて取得
    template<class T>
    static bool GetTaskArray(TaskGroup group, const T** task_array, int size);
};
