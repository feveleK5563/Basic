//------------------------------------------------------------------------------
// mainSystem_task.cpp
// DXライブラリの起動と更新
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "system/mainSystem_task.h"
#include "util/debugUtil.hpp"

class MainSystem_Task::Impl
{
public:
    Impl()
    {
    }

    ~Impl()
    {
    }

    // 初期化
    void Initialize()
    {
        // Log.txtが作られないようにする
        SetOutApplicationLogValidFlag(false);

        // スクリーン設定
        // TODO 本来は設定管理システムに問い合わせる
        SetScreen(false, 1280, 720);

        // 垂直同期設定
        SetWaitVSyncFlag(false);

        // ウィンドウタイトルを付ける
        SetWindowText("Basic");

        // 初期化と裏画面化
        if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
        {
            DEBUG_LOG("Failed to initialize DxLib.");
            ASSERT(false);
        }
    }

    // 終了処理
    void Finalize()
    {
        if (DxLib_End() == -1)
        {
            DEBUG_LOG("Failed to finalize DxLib.");
            ASSERT(false);
        }
    }

    // 更新
    void Update()
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
    void SetScreen(bool is_full_screen,
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

        // 解像度とカラービット数設定
        SetGraphMode(window_size_x, window_size_y, 32);
    }
};

//------------------------------------------------------------------------------

MainSystem_Task::Impl* MainSystem_Task::impl_ = nullptr;

MainSystem_Task::MainSystem_Task()
    : TaskBase()
{
    ASSERT(!impl_);
    impl_ = new Impl();
}

MainSystem_Task::~MainSystem_Task()
{
    ASSERT(impl_);
    delete impl_;
}

void MainSystem_Task::Initialize()
{
    ASSERT(impl_);
    impl_->Initialize();
}

void MainSystem_Task::Finalize()
{
    ASSERT(impl_);
    impl_->Finalize();
}

void MainSystem_Task::Update()
{
    ASSERT(impl_);
    impl_->Update();
}
