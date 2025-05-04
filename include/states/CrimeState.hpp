#pragma once

#include <KrakenEngine.hpp>
#include "states/BaseState.hpp"
#include "Player.hpp"
#include "puzzles/CrimeScene.hpp"

class Core;

class CrimeState final : public BaseState
{
public:
    CrimeState(Core* core);
    ~CrimeState() = default;

    void update() override;

private:
    kn::TileMap tileMap;
    Player player;
    const kn::Texture bgTex;

    CrimeScene crimeScene;
    bool inScene = false;
};
