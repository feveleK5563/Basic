//------------------------------------------------------------------------------
// main.cpp
// これが無いとなんもなんない
//------------------------------------------------------------------------------

#include <crtdbg.h>

#include "DxLib/DxLib.h"
#include "system\mainSystem.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // メモリリーク検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // メインシステム起動
    MainSystem ms;
    if (!ms.Initialize())
    {
        return 1;
    }

    // ループ
    ms.MainLoop();

    // 終了
    if (!ms.Finalize())
    {
        return 1;
    }

    return 0;
}