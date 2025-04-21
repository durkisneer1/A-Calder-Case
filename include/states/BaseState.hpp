#pragma once

class Core;

class BaseState
{
public:
    BaseState(Core* core);
    virtual ~BaseState() = default;

    virtual void update() = 0;

protected:
    Core* m_core;
};
