#pragma once

#include "DxLib/DxLib.h"

void Test()
{
    // 絵を表示
    DrawCircle(640, 340, 100, GetColor(255, 255, 255), false);

    ScreenFlip();
}