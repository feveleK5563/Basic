//------------------------------------------------------------------------------
// renderSystem_task.h
// 描画管理
//------------------------------------------------------------------------------

#pragma once

class ImageData
{

};

class RenderSystem
{
public:
    static RenderSystem CreateTask();

private:
    class Task;
    static Task* task_;
};
