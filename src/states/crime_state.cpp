#include "states/CrimeState.hpp"
#include "Core.hpp"

CrimeState::CrimeState(Core* core)
    : BaseState(core, {}) // color
    , player(nullptr, {}) // colLayer, spawnPos
{
}

void CrimeState::update()
{
}