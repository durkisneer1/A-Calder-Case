#include "states/EndState.hpp"
#include "Core.hpp"

EndState::EndState(Core* core, const std::string& message)
    : BaseState(core, kn::color::fromHex("#1f1f29"))
{
    kn::Font font("kraken-retro", 8);
    kn::Color textColor = kn::color::fromHex("eaf0d8");
    messageTex = font.render(message, false, textColor);
    escTex = font.render("Press ESC to exit.", false, textColor);
}

void EndState::update()
{
    kn::camera = { 0, 0 };

    if (kn::key::isJustPressed(kn::K_ESC))
    {
        kn::window::close();
    }

    kn::window::clear(m_bgColor);
    const kn::Vec2 halfWin = kn::window::getSize() / 2;
    kn::window::blit(messageTex, halfWin, kn::CENTER);
    const kn::Vec2 offsetVec = { 0, 12 };
    kn::window::blit(escTex, halfWin + offsetVec, kn::CENTER);
}