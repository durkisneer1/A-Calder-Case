#pragma once

#include <KrakenEngine.hpp>

class Player final
{
public:
    Player(const kn::Layer* colLayer, const kn::Vec2& spawnPos);
    ~Player() = default;

    void update(double dt);

    kn::Rect getRect() const;

private:
    kn::AnimationController anim;
    kn::Vec2 vel;
    kn::Rect rect;
    bool facingRight = true;
    const double SPEED = 40; // 40
    bool onGround = false;
    const kn::Layer* colLayer;

    void handleCollision(int axis);
};
