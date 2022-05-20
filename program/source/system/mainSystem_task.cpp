//------------------------------------------------------------------------------
// mainSystem_task.cpp
// DXライブラリの起動と更新
//------------------------------------------------------------------------------

#include "DxLib/DxLib.h"
#include "system/fps_task.h"
#include "system/mainSystem_task.h"
#include "util/various.hpp"

class MainSystem_Impl
{
public:
    MainSystem_Impl()
    {
    }

    ~MainSystem_Impl()
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

        // 画像を左右に動かす
        static int graph_handle = -1;
        if (graph_handle == -1)
        {
            graph_handle = LoadGraph("resource/aoi.png");
            DEBUG_LOG("GRAPH_HANDLE : %d\n", graph_handle);
        }
        else
        {
            static float x = 0;
            static bool lr = false;
            float speed = 1280.f * Fps::GetDeltaTime();
            DrawGraph(x - 160, 340, graph_handle, true);
            if (!lr)
            {
                // 右移動
                x += speed;
                if (x >= 1280)
                {
                    lr = true;
                }
            }
            else
            {
                // 左移動
                x -= speed;
                if (x <= 0)
                {
                    lr = false;
                }
            }
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

static MainSystem_Impl* impl = nullptr;

//------------------------------------------------------------------------------

MainSystem_Task::MainSystem_Task()
    : TaskBase()
{
    ASSERT(!impl);
    impl = new MainSystem_Impl();
}

MainSystem_Task::~MainSystem_Task()
{
    ASSERT(impl);
    delete impl;
}

void MainSystem_Task::Initialize()
{
    ASSERT(impl);
    impl->Initialize();
}

void MainSystem_Task::Finalize()
{
    ASSERT(impl);
    impl->Finalize();
}

void MainSystem_Task::Update()
{
    ASSERT(impl);
    impl->Update();
}
