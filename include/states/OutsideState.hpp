#pragma once

#include "BaseState.hpp"
#include "Car.hpp"
#include "Player.hpp"
#include <KrakenEngine.hpp>

class Core;

class OutsideState final : public BaseState
{
public:
    OutsideState(Core* core);
    ~OutsideState() = default;

    void update() override;

private:
    kn::TileMap tileMap;
    Player player;
    Car car;
    kn::Rect doorRect { 530, 56, 6, 48 };
    const kn::Texture firstPass;
    const kn::Texture treeTex;
    const kn::Texture bigTreeTex;
    const kn::Texture bgTrees;
    const kn::Texture multLayer;
};
