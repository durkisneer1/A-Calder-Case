#include "states/WorldState.hpp"
#include "Core.hpp"

WorldState::WorldState(Core* core)
    : BaseState(core)
{
}

void WorldState::update()
{
    m_core->player.update(m_core->dt);
}