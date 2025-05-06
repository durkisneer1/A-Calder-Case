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

    for (const auto& tapeTile : tileMap.getLayer("tape")->tiles)
    {
        if (kn::key::isJustPressed(kn::S_e) && player.getRect().collideRect(tapeTile.collider))
        {
            inScene = !inScene;
            break;
        }
    }

    if (player.getRect().collideRect(doorRect))
    {
        kn::draw::rect(doorRect, kn::color::YELLOW, 1);
        if (kn::key::isJustPressed(kn::S_e))
            m_core->currState = AppState::OUTSIDE;
    }

    player.draw(m_core->dt);

    inScene ? crimeScene.update() : player.move(m_core->dt);
}
