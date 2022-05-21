//------------------------------------------------------------------------------
// taskSystemCore.cpp
// タスクシステム コア
//------------------------------------------------------------------------------

#include <algorithm>
#include <memory>
#include <string.h>
#include <unordered_map>
#include <vector>

#include "system/deltaTime_task.h"
#include "system/mainSystem_task.h"
#include "system/task/taskBase.h"
#include "system/task/taskSystem.h"
#include "util/debugUtil.hpp"

#include "test/test_task.h"

class TaskSystem_Impl
{
public:
    TaskSystem_Impl()
    {
        // 適当にメモリをとっておく
        task_list_.reserve(1024);
        task_group_num_.reserve(128);
    }

    ~TaskSystem_Impl()
    {
    }

    // 初期化
    void Initialize()
    {
        // システム系タスクを作成する
        CreateTask<MainSystem_Task>();
        CreateTask<DeltaTime_Task>();

        // ゲーム内タスク生成
        CreateTask<Test_Task>();
    }

    // 終了処理
    void Finalize()
    {
        ForceAllDeleteTask();
    }

    // メインループ
    void MainLoop()
    {
        while (true)
        {
            if (task_list_.size() <= 0)
            {
                // タスクが無くなったら終わり
                break;
            }

            AllUpdate();        // 全部更新
            ChangeTaskState();  // タスクの状態変更（初期化と終了処理）
            RemoveKillTask();   // タスク削除
            SortTask();         // 並び替え
        }
    }

    // 全てのタスクを削除要請状態にする
    void KillAllTask()
    {
        for (auto& task : task_list_)
        {
            task->SetState(TaskState::Kill);
        }
    }

    // タスクを生成して追加
    template<class T>
    T* CreateTask()
    {
        T* task = new T;
        task_list_.emplace_back(task);
        is_sorted_ = false;
    
        DEBUG_LOG("CreateTask : group(%d)\n", task->GetGroup());

        return task;
    }

    // 指定したグループのタスク個数を取得
    int GetTaskNum(TaskGroup group)
    {
        return task_group_num_[group];
    }

    // 指定したグループのタスクを先頭だけ取得
    template<class T>
    bool GetTask(TaskGroup group, const T* task_single)
    {
        int num = task_group_num_[group];
        if (num <= 0)
        {
            return false;
        }

        task_single = nullptr;

        for (auto& task : task_list_)
        {
            if (task->GetGroup() == group)
            {
                task_single = dynamic_cast<const T*>(task);
                break;
            }
        }

        return task_single != nullptr;
    }


    // 指定したグループのタスクをまとめて取得
    template<class T>
    bool GetTaskArray(TaskGroup group, const T** task_array, int size)
    {
        int num = task_group_num_[group];
        if (num < size)
        {
            return false;
        }

        memset(task_array, nullptr, size);

        int count = 0;
        for (auto& task : task_list_)
        {
            if (task->GetGroup() == group)
            {
                task_array[count] = dynamic_cast<const T*>(task);
                ++count;
            }

            if (count == num || count == size)
            {
                break;
            }
        }

        return true;
    }

private:
    // 全ての登録済タスクの更新処理を呼ぶ
    void AllUpdate()
    {
        for (auto& task : task_list_)
        {
            if (task->IsPause())
            {
                continue;
            }

            if (task->GetState() == TaskState::Active)
            {
                // 稼働中の場合は普通に更新
                task->Update();
            }
        }
    }

    // タスクの状態を変更する
    void ChangeTaskState()
    {
        for (auto& task : task_list_)
        {
            switch (task->GetState())
            {
            // 準備状態だったら初期化呼んで稼働させる
            case TaskState::Ready:
                task->Initialize();
                task->SetState(TaskState::Active);
                ++task_group_num_[task->GetGroup()];
                break;

            // 消滅要請の場合は終了処理を呼ぶ
            case TaskState::Kill:
                task->Finalize();
                --task_group_num_[task->GetGroup()];
                break;
            }
        }
    }

    // Kill状態のタスクを削除
    void RemoveKillTask()
    {
        // タスクを消す
        for (auto& task : task_list_)
        {
            if (task->GetState() == TaskState::Kill)
            {
                delete task;
                task = nullptr;
            }
        }

        // 配列から削除
        const auto& remove_it = std::remove_if(
            task_list_.begin(), task_list_.end(),
            [](TaskBase* task)
            {
                return (task == nullptr);
            });

        task_list_.erase(remove_it, task_list_.end());

        is_sorted_ = false;
    }

    // グループがまとまるようにソートする
    void SortTask()
    {
        if (is_sorted_)
        {
            return;
        }

        std::sort(task_list_.begin(), task_list_.end(),
            [](TaskBase* left, TaskBase* right)
            {
                return (left->GetGroup() < right->GetGroup());
            });

        is_sorted_ = true;
    }

    // 強制的に全てのタスクを削除
    void ForceAllDeleteTask()
    {
        for (auto& task : task_list_)
        {
            delete task;
            task = nullptr;
        }

        task_list_.clear();
        task_group_num_.clear();
    }

private:
    std::vector<TaskBase*> task_list_;                  // タスクリスト
    std::unordered_map<TaskGroup, int> task_group_num_; // 稼働タスク数記録

    bool is_sorted_ = false;    // ソートしたか
};

static TaskSystem_Impl* impl = nullptr;

//------------------------------------------------------------------------------

void TaskSystem::Initialize()
{
    ASSERT(!impl);
    impl = new TaskSystem_Impl;
    impl->Initialize();
}

void TaskSystem::Finalize()
{
    ASSERT(impl);
    impl->Finalize();
    delete impl;
}

void TaskSystem::MainLoop()
{
    ASSERT(impl);
    impl->MainLoop();
}

void TaskSystem::KillAllTask()
{
    ASSERT(impl);
    impl->KillAllTask();
}

template<class T>
T* TaskSystem::CreateTask()
{
    ASSERT(impl);
    return impl->CreateTask<T>();
}

int TaskSystem::GetTaskNum(TaskGroup group)
{
    ASSERT(impl);
    return impl->GetTaskNum(group);
}

template<class T>
bool TaskSystem::GetTask(TaskGroup group, const T* task_single)
{
    ASSERT(impl);
    return impl->GetTask(group, task_single);
}

template<class T>
bool TaskSystem::GetTaskArray(
    TaskGroup group, const T** task_array, int size)
{
    ASSERT(impl);
    return impl->GetTaskArray(group, task_array, size);
}

//------------------------------------------------------------------------------

float DeltaTime::Get()
{
    return DeltaTime_Task::GetDeltaTime();
}
