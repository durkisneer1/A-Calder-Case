#pragma once

#include <KrakenEngine.hpp>

class Core;

class BaseState
{
public:
    BaseState(Core* core, const kn::Color& bgColor)
        : m_core(core)
        , m_bgColor(bgColor)
    {
    }
    virtual ~BaseState() = default;

    virtual void handleEvents(const kn::Event& event)
    {
    }

    virtual void update() = 0;

protected:
    Core* m_core;
    kn::Color m_bgColor;
    kn::Vec2 m_camera;
};
