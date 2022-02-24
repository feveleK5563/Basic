
#include <iostream>
#include "DxLib/DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    SetOutApplicationLogValidFlag(false);

    // ウィンドウモード
    ChangeWindowMode(true);
    // ウインドウのサイズを手動で変更できず、且つウインドウのサイズに合わせて拡大もしないようにする
    SetWindowSizeChangeEnableFlag(FALSE, FALSE);
    // ウィンドウサイズ(解像度以下に設定)
    SetWindowSize(1280, 720);

    //画面解像度とカラービット数
    SetGraphMode(1280, 720, 32);

    // 初期化と裏画面化
    if (DxLib_Init() == -1 /* || SetDrawScreen(DX_SCREEN_BACK) != 0*/)
    {
        return 1;
    }

    // 絵を表示
    DrawCircle(640, 340, 100, GetColor(255, 255, 255), 0);

    // キー入力待ち
    WaitKey();

    // DXライブラリ終了
    DxLib_End();

    return 0;
}