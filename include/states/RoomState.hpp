#pragma once
#include "states/BaseState.hpp"
#include "Player.hpp"
#include "puzzles/TypeWriter.hpp"
#include <KrakenEngine.hpp>

class Core;
class Player;

class RoomState final : public BaseState
{
public:
    RoomState(Core* core);
    ~RoomState() = default;

    void update() override;

    void handleEvents(const kn::Event& event) override;

private:
    const kn::Texture bgTex;
    kn::Texture lightTex;
    kn::TileMap tileMap;
    Player player;

    const kn::Rect doorRect { 8, 56, 6, 48 };

    TypeWriter typeWriter;
};
