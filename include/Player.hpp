#pragma once

#include <KrakenEngine.hpp>
#include <vector>

class Player final
{
public:
    Player(const kn::Layer* colLayer);
    ~Player() = default;

    void update(double dt);

private:
    kn::AnimationController anim;
    kn::Vec2 vel;
    kn::Rect rect;
    bool facingRight = true;
    const double SPEED = 40;
    bool onGround = false;
    const kn::Layer* colLayer;

    void handleCollision(int axis);
};