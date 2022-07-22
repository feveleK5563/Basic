//------------------------------------------------------------------------------
// mainSystem_task.cpp
// DXライブラリの起動と更新
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "system/task/taskBase.h"
#include "system/mainSystem_task.h"
#include "util/debugUtil.hpp"

class MainSystem::Task : public TaskBase
{
public:
    TaskGroup GetGroup() const override
    {
        return TaskGroup::MainSystem;
    }

public:
    explicit Task()
        : TaskBase()
    {
    }

    virtual ~Task()
    {
    }

    // 初期化
    void Initialize() override
    {
        // Log.txtが作られないようにする
        SetOutApplicationLogValidFlag(false);

        // スクリーン設定
        // TODO 本来は設定管理システムに問い合わせる
        SetScreen(false, 0, 1280, 720);

        // 垂直同期設定
        SetWaitVSyncFlag(false);

        // 非アクティブでも動作するように
        SetAlwaysRunFlag(true);

        // ウィンドウタイトルを付ける
        SetWindowText("Basic");

        // 初期化と裏画面化
        if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
        {
            DEBUG_LOG("Failed to initialize DxLib.");
            DEBUG_ASSERT(false);
        }
    }

    // 終了処理
    void Finalize() override
    {
        if (DxLib_End() == -1)
        {
            DEBUG_LOG("Failed to finalize DxLib.");
            DEBUG_ASSERT(false);
        }
    }

    // 更新
    void Update() override
    {
        if (ScreenFlip() != 0 ||                // 裏画面を表画面に反映
            ProcessMessage() != 0 ||            // メッセージ処理
            ClearDrawScreen() != 0 ||           // 画面をクリア
            CheckHitKey(KEY_INPUT_ESCAPE) != 0) // ESCキー押下判定
        {
            // 終了（タスクシステムも道連れ）
            TaskSystem::KillAllTask();
            return;
        }
    }

private:
    // フルスクリーンにするかメッセージボックスで訊く
    bool PopDialogIsFullScreenMode()
    {
        int flag = 0;
        flag = MessageBox(
            nullptr,
            TEXT("FULLSCREEN????"),
            TEXT("SCREEN"),
            MB_YESNO | MB_ICONQUESTION
        );

        return (flag == IDYES);
    }

    // スクリーン設定
    void SetScreen(bool is_full_screen, int display_index,
                   int window_size_x, int window_size_y)
    {
        if (is_full_screen)
        {
            // フルスクリーンに設定
            ChangeWindowMode(false);

            // フルスクリーン時に縦横比を維持する
            SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
        }
        else
        {
            // ウィンドウモードに設定
            ChangeWindowMode(true);

            // ウィンドウのサイズを手動で変更できず、
            // 且つウィンドウのサイズに合わせて拡大もしないようにする
            SetWindowSizeChangeEnableFlag(false, false);

            // ウィンドウサイズ設定
            SetWindowSize(window_size_x, window_size_y);
        }

        // ディスプレイのインデックス設定
        SetUseDisplayIndex(display_index);

        // 解像度とカラービット数設定
        SetGraphMode(window_size_x, window_size_y, 32);
    }
};

//------------------------------------------------------------------------------

MainSystem::Task* MainSystem::task_ = nullptr;

MainSystem MainSystem::CreateTask()
{
    DEBUG_ASSERT(!task_);
    MainSystem task_interface;

    Task* task = new Task;
    if (TaskSystem::AddTask(task))
    {
        task_interface.task_ = task;
    }
    return task_interface;
}