//------------------------------------------------------------------------------
// test_task.h
// テスト
//------------------------------------------------------------------------------

#pragma once

class Test
{
public:
    static Test CreateTask();

    void SetPos(float x, float y);
    void SetSpeed(float speed);

private:
    class Task;
    Task* task_ = nullptr;
};
