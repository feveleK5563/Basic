//------------------------------------------------------------------------------
// mainSystem_task.h
// DXライブラリの起動とメインループ実行
//------------------------------------------------------------------------------

#pragma once

class MainSystem
{
public:
    static MainSystem CreateTask();

private:
    class Task;
    static Task* task_;
};
