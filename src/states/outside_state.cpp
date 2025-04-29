#include "Window.hpp"
#include "states/OutsideState.hpp"
#include "Core.hpp"

#include <algorithm>

OutsideState::OutsideState(Core* core)
    : BaseState(core, kn::color::fromHex("#eaf0d8"))
    , tileMap("../assets/environ/outside.tmx")
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

void OutsideState::update()
{
    kn::camera = { player.getRect().bottomMid().x - m_camera.x, m_camera.y };
    kn::camera.x = std::clamp(kn::camera.x, 0.0, 224.0);

    kn::window::clear(m_bgColor);
    kn::window::blit(bgTrees, { 0, -22 });

    for (const auto& treeTile : tileMap.getLayer("big tree")->tiles)
        kn::window::blit(bigTreeTex, treeTile.rect.bottomLeft(), kn::BOTTOM_LEFT);
    for (const auto& treeTile : tileMap.getLayer("trees")->tiles)
        kn::window::blit(treeTex, treeTile.rect.bottomLeft(), kn::BOTTOM_LEFT);
    kn::window::blit(firstPass, { 0, kn::camera.y });

    tileMap.drawMap();

    if (player.getRect().collideRect(doorRect))
    {
        kn::draw::rect(doorRect, kn::color::YELLOW, 1);
        if (kn::key::isJustPressed(kn::S_e))
        {
            m_core->currState = AppState::ROOM;
        }
    }

    car.update();
    player.update(m_core->dt);
    tileMap.getLayer("grass")->draw();
    kn::window::blit(multLayer, { 0, kn::camera.y });
}
