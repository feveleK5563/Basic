//------------------------------------------------------------------------------
// <name>_task.cpp
// 説明
//------------------------------------------------------------------------------

#include "<name>_task.h"
#include "util/debugUtil.hpp"

class <Name>_Task::Impl
{
public:
    Impl()
    {
    }

    ~Impl()
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

//------------------------------------------------------------------------------

<Name>_Task::<Name>_Task()
    : TaskBase()
    , impl_(nullptr)
{
    ASSERT(!impl_);
    impl_ = new Impl();
}

<Name>_Task::~<Name>_Task()
{
    ASSERT(impl_);
    delete impl_;
}

void <Name>_Task::Initialize()
{
    ASSERT(impl_);
    impl_->Initialize();
}

void <Name>_Task::Finalize()
{
    ASSERT(impl_);
    impl_->Finalize();
}

void <Name>_Task::Update()
{
    ASSERT(impl_);
    impl_->Update();
}
