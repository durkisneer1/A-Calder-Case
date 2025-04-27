#include "Window.hpp"
#include "states/OutsideState.hpp"
#include "Core.hpp"

#include <algorithm>

OutsideState::OutsideState(Core* core)
    : BaseState(core, kn::color::fromHex("#596070"))
    , tileMap("../assets/environ/outside.tmx")
    , player(tileMap.getLayer("ground"), { 504, 56 })
    , bgDarken(kn::window::getSize(), { 230, 230, 230 })
{
    m_bgColor = kn::color::BLACK;
    m_camera = { 224, -30 };
    bgDarken.makeMultiply();
}

void OutsideState::update()
{
    kn::camera.x = player.getRect().bottomMid().x - 224;
    kn::camera.x = std::clamp(kn::camera.x, 0.0, 224.0);

    kn::window::clear(m_bgColor);
    // kn::window::blit(bgDarken);

    tileMap.drawMap();

    if (player.getRect().collideRect(doorRect))
    {
        kn::draw::rect(doorRect, kn::color::YELLOW, 1);
        if (kn::key::isJustPressed(kn::S_e))
        {
            m_core->currState = AppState::ROOM;
        }
    }

    player.update(m_core->dt);
    tileMap.getLayer("grass")->draw();
}
