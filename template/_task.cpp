//------------------------------------------------------------------------------
// <name>_task.cpp
// 説明
//------------------------------------------------------------------------------

#include "<name>_task.h"
#include "util/various.hpp"

class <Name>_Impl
{
public:
    <Name>_Impl()
    {
    }

    ~<Name>_Impl()
    {
    }

    void Initialize()
    {
    }

    void Finalize()
    {
    }

    void Update()
    {
    }
};

static <Name>_Impl* impl = nullptr;

//------------------------------------------------------------------------------

<Name>_Task::<Name>_Task()
    : TaskBase()
{
    ASSERT(!impl);
    impl = new <Name>_Impl();
}

<Name>_Task::~<Name>_Task()
{
    ASSERT(impl);
    delete impl;
}

void <Name>_Task::Initialize()
{
    ASSERT(impl);
    impl->Initialize();
}

void <Name>_Task::Finalize()
{
    ASSERT(impl);
    impl->Finalize();
}

void <Name>_Task::Update()
{
    ASSERT(impl);
    impl->Update();
}
