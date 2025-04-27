#pragma once

#include "BaseState.hpp"
#include "Player.hpp"
#include <KrakenEngine.hpp>

class Core;
class Player;

class OutsideState final : public BaseState
{
public:
    OutsideState(Core* core);
    ~OutsideState() = default;

    void update() override;

private:
    kn::TileMap tileMap;
    Player player;
    kn::Rect doorRect { 530, 56, 6, 48 };
    kn::Texture bgDarken;
};
