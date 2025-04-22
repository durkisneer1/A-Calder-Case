#include "states/WorldState.hpp"
#include "Core.hpp"

WorldState::WorldState(Core* core)
    : BaseState(core)
    , bgTex("../assets/environ/room.png")
    , tileMap("../assets/environ/border.tmx")
{
    groundLayer = tileMap.getLayer("ground");
}

void WorldState::update()
{
    kn::window::blit(bgTex, { 8, 8 });
    tileMap.drawMap();
    player.update(m_core->dt, groundLayer->tiles);
}
