#pragma once

#include <KrakenEngine.hpp>
#include <vector>

class Player final
{
public:
    Player();
    ~Player() = default;

    void update(double dt, const std::vector<kn::Tile>& colTiles);

private:
    kn::AnimationController anim;
    kn::Vec2 vel;
    kn::Rect rect;
    bool facingRight = true;
    const double SPEED = 40;
    bool onGround = false;

    void handleCollision(int axis, const std::vector<kn::Tile>& colTiles);
};