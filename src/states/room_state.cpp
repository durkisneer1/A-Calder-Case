#include "states/RoomState.hpp"
#include "Core.hpp"

RoomState::RoomState(Core* core)
    : BaseState(core, kn::color::fromHex("#1f1f29"))
    , bgTex("../assets/environ/room.png")
    , lightTex("../assets/environ/room-light.png")
    , tileMap("../assets/environ/border.tmx")
    , player(tileMap.getLayer("ground"), { 256, 64 })
{
    lightTex.makeMultiply();
    m_camera = { -8, -30 };
}

void RoomState::update()
{
    kn::camera = m_camera;
    
    kn::window::clear(m_bgColor);

    kn::window::blit(bgTex, { 8, 8 });
    tileMap.drawMap();

    if (player.getRect().collideRect(doorRect))
    {
        kn::draw::rect(doorRect, kn::color::YELLOW, 1);
        if (kn::key::isJustPressed(kn::S_e))
        {
            m_core->currState = AppState::OUTSIDE;
        }
    }

    player.update(m_core->dt);

    kn::window::blit(lightTex, { 8, 8 });
}
