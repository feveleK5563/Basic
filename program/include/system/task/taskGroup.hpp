//------------------------------------------------------------------------------
// taskGroup.hpp
// タスクグループ列挙
//------------------------------------------------------------------------------

#pragma once

// タスクグループ列挙
// 上から順番に更新されるようになってるぞ
enum struct TaskGroup
{
    None = 0,

    // システム系
    MainSystem  = 1,    // DXライブラリの起動と更新
    Fps         = 2,    // FPS制御

    //----------------------------------------------------------------------

    // テスト
    Test        = 10,

};
