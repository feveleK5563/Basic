//------------------------------------------------------------------------------
// mainSystem.h
// DXライブラリの起動とメインループ実行
//------------------------------------------------------------------------------

#pragma once

class MainSystem
{
public:
    MainSystem();
    ~MainSystem();

    // 初期化
    bool Initialize();

    // 終了処理
    bool Finalize();

    // メインループ
    void MainLoop();
};
