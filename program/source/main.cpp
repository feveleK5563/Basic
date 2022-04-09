//------------------------------------------------------------------------------
// main.cpp
// これが無いとなんもなんない
//------------------------------------------------------------------------------

#include <crtdbg.h>

#include "DxLib/DxLib.h"
#include "system/task/taskSystem.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
    // メモリリーク検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // タスクシステム起動
    TaskSystem::Initialize();

    // ループ
    TaskSystem::MainLoop();

    // 終了
    TaskSystem::Finalize();

    return 0;
}