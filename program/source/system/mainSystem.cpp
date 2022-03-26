//------------------------------------------------------------------------------
// mainSystem.cpp
// DXライブラリの起動とメインループ実行
//------------------------------------------------------------------------------

#include <assert.h>

#include "DxLib/DxLib.h"
#include "system/mainSystem.h"

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
    bool Initialize()
    {
        // Log.txtが作られないようにする
        SetOutApplicationLogValidFlag(false);

        // スクリーン設定
        // TODO 本来は設定管理システムに問い合わせる
        SetScreen(false, 1280, 720);

        // ウィンドウタイトルを付ける
        SetWindowText("Basic");

        // 初期化と裏画面化
        if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
        {
            return false;
        }

        return true;
    }

    // 終了処理
    bool Finalize()
    {
        if (DxLib_End() == -1)
        {
            return false;
        }

        return true;
    }

    // メインループ
    void MainLoop()
    {
        while (ScreenFlip() == 0 &&                 // 裏画面を表画面に反映
               ProcessMessage() == 0 &&             // メッセージ処理
               ClearDrawScreen() == 0 &&            // 画面をクリア
               CheckHitKey(KEY_INPUT_ESCAPE) == 0)  // ESCキーを押してない
        {
            DrawCircle(640, 340, 100, GetColor(255, 255, 255), true);
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

MainSystem::MainSystem()
{
    assert(!impl);
    impl = new MainSystem_Impl;
}

MainSystem::~MainSystem()
{
    assert(impl);
    delete impl;
}

bool MainSystem::Initialize()
{
    assert(impl);
    return impl->Initialize();
}

bool MainSystem::Finalize()
{
    assert(impl);
    return impl->Finalize();
}

void MainSystem::MainLoop()
{
    assert(impl);
    impl->MainLoop();
}