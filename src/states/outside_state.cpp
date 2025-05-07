#include "Window.hpp"
#include "states/OutsideState.hpp"
#include "Core.hpp"

#include <algorithm>

OutsideState::OutsideState(Core* core)
    : BaseState(core, kn::color::fromHex("#eaf0d8"))
    , tileMap("../assets/environ/outside.tmx", 1)
    , player(tileMap.getLayer("ground"), { 504, 56 })
    , firstPass("../assets/environ/outside-firstpass.png")
    , treeTex("../assets/environ/tree.png")
    , bigTreeTex("../assets/environ/big-tree.png")
    , bgTrees("../assets/environ/outside-bg.png")
    , multLayer("../assets/environ/outside-multlayer.png")
{
    m_camera = { 224, -60 };
    firstPass.makeMultiply();
    multLayer.makeMultiply();
}

void OutsideState::handleEvents(const kn::Event& event)
{
    static std::unordered_map<kn::Keycode, int> keyMap = {
        { kn::K_0, 0 },
        { kn::K_KP_0, 0 },
        { kn::K_1, 1 },
        { kn::K_KP_1, 1 },
        { kn::K_2, 2 },
        { kn::K_KP_2, 2 },
        { kn::K_3, 3 },
        { kn::K_KP_3, 3 },
        { kn::K_4, 4 },
        { kn::K_KP_4, 4 },
        { kn::K_5, 5 },
        { kn::K_KP_5, 5 },
        { kn::K_6, 6 },
        { kn::K_KP_6, 6 },
        { kn::K_7, 7 },
        { kn::K_KP_7, 7 },
        { kn::K_8, 8 },
        { kn::K_KP_8, 8 },
        { kn::K_9, 9 },
        { kn::K_KP_9, 9 },
    };

    if (event.type == kn::KEYDOWN)
    {
        auto it = keyMap.find(event.key.keysym.sym);
        if (phoneBox.ready() && it != keyMap.end())
        {
            phoneBox.addNumber(it->second);
        }
    }
}

void OutsideState::update()
{
    if (!phoneBox.isOpen() && kn::key::isJustPressed(kn::K_ESC))
    {
        m_core->prevPauseState = m_core->currState;
        m_core->currState = AppState::PAUSE;
    }

    const auto winSize = kn::window::getSize();

    kn::camera = { player.getRect().bottomMid().x - winSize.x / 2, m_camera.y };
    kn::camera.x = std::clamp(kn::camera.x, 0.0, 224.0);

    kn::window::clear(m_bgColor);
    kn::window::blit(bgTrees, { 0, -22 });

    for (const auto& treeTile : tileMap.getLayer("big tree")->tiles)
        kn::window::blit(bigTreeTex, treeTile.rect.bottomLeft(), kn::BOTTOM_LEFT);
    for (const auto& treeTile : tileMap.getLayer("trees")->tiles)
        kn::window::blit(treeTex, treeTile.rect.bottomLeft(), kn::BOTTOM_LEFT);
    kn::window::blit(firstPass, { 0, kn::camera.y });

    tileMap.drawMap();

    const auto playerRect = player.getRect();
    if (playerRect.collideRect(doorRect))
    {
        kn::draw::rect(doorRect, kn::color::YELLOW, 1);
        if (kn::key::isJustPressed(kn::S_e))
            m_core->currState = AppState::ROOM;
    }

    if (car.updateAndCollide(playerRect) && kn::key::isJustPressed(kn::S_e))
        m_core->currState = AppState::CRIME;

    player.move(m_core->dt);

    phoneBox.drawBooth(playerRect);
    player.draw(m_core->dt);
    kn::window::blit(multLayer, { 0, kn::camera.y });
    tileMap.getLayer("grass")->draw();

    phoneBox.drawDial();
}
