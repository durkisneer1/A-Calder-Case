#pragma once
#include "BaseState.hpp"
#include "Player.hpp"
#include <KrakenEngine.hpp>

class Core;
class Player;

class WorldState final : public BaseState
{
public:
    WorldState(Core* core);
    ~WorldState() = default;

    void update() override;

private:
    const kn::Texture bgTex;
    kn::TileMap tileMap;
    const kn::Layer* groundLayer;
    Player player;
};
