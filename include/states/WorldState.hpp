#pragma once
#include "BaseState.hpp"

class Core;

class WorldState final : public BaseState
{
public:
    WorldState(Core* core);
    ~WorldState() = default;

    void update() override;
};
