#include "states/RoomState.hpp"
#include "Core.hpp"

RoomState::RoomState(Core* core)
    : BaseState(core, kn::color::fromHex("#1f1f29"))
    , bgTex("../assets/environ/room.png")
    , lightTex("../assets/environ/room-light.png")
    , tileMap("../assets/environ/border.tmx", 1)
    , player(tileMap.getLayer("ground"), { 256, 64 })
{
    lightTex.makeMultiply();
    m_camera = { -8, -30 };
}

void RoomState::handleEvents(const kn::Event& event)
{
    typeWriter.update(event);
}

void RoomState::update()
{
    if (!typeWriter.isOpened() && kn::key::isJustPressed(kn::K_ESC))
    {
        m_core->prevPauseState = m_core->currState;
        m_core->currState = AppState::PAUSE;
    }

    kn::camera = m_camera;

    kn::window::clear(m_bgColor);

    kn::window::blit(bgTex, { 8, 8 });
    tileMap.drawMap();

    const auto playerRect = player.getRect();
    if (playerRect.collideRect(doorRect))
    {
        kn::draw::rect(doorRect, kn::color::YELLOW, 1);
        if (kn::key::isJustPressed(kn::S_e))
        {
            m_core->currState = AppState::OUTSIDE;
        }
    }

    typeWriter.drawWriter(playerRect);

    if (!typeWriter.isOpened())
        player.move(m_core->dt);
    player.draw(m_core->dt);

    kn::window::blit(lightTex, { 8, 8 });

    typeWriter.drawInput();

    if (typeWriter.isSubmitted())
    {
        m_core->currState = typeWriter.isCorrect() ? AppState::GOOD : AppState::BAD;
    }
}
