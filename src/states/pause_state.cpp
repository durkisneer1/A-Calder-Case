#include "states/PauseState.hpp"
#include "Core.hpp"

PauseState::PauseState(Core* core)
    : BaseState(core, kn::color::fromHex("#1f1f29"))
{
    kn::Font font("kraken-retro", 8);
    pausedTex = font.render("PAUSED", false, kn::color::fromHex("eaf0d8"));
    resumeTex = font.render("RESUME", false, m_bgColor);
    quitTex = font.render("QUIT", false, m_bgColor);
}

void PauseState::update()
{
    kn::camera = { 0, 0 };

    const auto winSize = kn::window::getSize();

    kn::window::clear(m_bgColor);
    kn::window::blit(pausedTex, winSize / 2, kn::CENTER);

    kn::Rect resumeRect = resumeTex.getRect();
    resumeRect.center({ winSize.x / 4, winSize.y * 3 / 4 });
    kn::Rect resumeboxRect = resumeRect;
    resumeboxRect.w += 3;
    resumeboxRect.x -= 2;
    kn::draw::rect(resumeboxRect, kn::color::fromHex("#eaf0d8"));
    kn::draw::rect(resumeboxRect, kn::color::fromHex("#596070"), 1);
    kn::window::blit(resumeTex, resumeRect);

    kn::Rect quitRect = quitTex.getRect();
    quitRect.center({ winSize.x * 3 / 4, winSize.y * 3 / 4 });
    kn::Rect quitBoxRect = quitRect;
    quitBoxRect.w += 3;
    quitBoxRect.x -= 2;
    kn::draw::rect(quitBoxRect, kn::color::fromHex("#eaf0d8"));
    kn::draw::rect(quitBoxRect, kn::color::fromHex("#596070"), 1);
    kn::window::blit(quitTex, quitRect);

    const auto mousePos = kn::mouse::getPos();
    bool justLeftClicked = kn::mouse::isJustPressed(kn::M_LEFT);
    if ((resumeboxRect.collidePoint(mousePos) && justLeftClicked) || kn::key::isJustPressed(kn::K_ESC))
    {
        m_core->currState = m_core->prevPauseState;
    }
    else if (quitBoxRect.collidePoint(mousePos) && justLeftClicked)
    {
        kn::window::close();
    }
}