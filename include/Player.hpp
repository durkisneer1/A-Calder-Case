#pragma once

#include <KrakenEngine.hpp>

class Player final
{
public:
    Player();
    ~Player() = default;

    void update(double dt);

private:
    kn::AnimationController anim;
    kn::Rect rect;
    kn::Vec2 pos;
    bool facingRight = true;
    const double SPEED = 40;
};