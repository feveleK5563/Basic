//------------------------------------------------------------------------------
// test_task.h
// ใในใ
//------------------------------------------------------------------------------

#pragma once

class Test
{
public:
    static Test CreateTask();

    void SetIndex(int index);
    void SetPos(float x, float y);
    void SetSpeed(float speed);

private:
    class Task;
    Task* task_ = nullptr;
};
