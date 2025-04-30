#include "states/CrimeState.hpp"
#include "Core.hpp"

CrimeState::CrimeState(Core* core)
    : BaseState(core, kn::color::fromHex("#1f1f29"))
    , tileMap("../assets/environ/crime.tmx")
    , player(tileMap.getLayer("Ground"), { 256, 64 })
    , bgTex("../assets/environ/crime-scene.png")
{
    m_camera = { -8, -30 };
}

void CrimeState::update()
{
    kn::camera = m_camera;

    kn::window::clear(m_bgColor);
    kn::window::blit(bgTex, { 8, 8 });
    tileMap.drawMap();

    player.update(m_core->dt);
}