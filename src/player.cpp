#include "Player.hpp"

Player::Player()
    : pos(kn::window::getSize() / 2)
{
    rect.size({ 21, 41 });
    anim.loadSpriteSheet("idle", "../assets/player/idle.png", rect.size(), 7);
    anim.loadSpriteSheet("walk", "../assets/player/walk.png", rect.size(), 7);
}

void Player::update(const double dt)
{
    const double xDir = kn::input::getAxis("left", "right");
    pos.x += xDir * SPEED * dt;
    rect.center(pos);

    if (xDir)
    {
        anim.setAnim("walk");

        if (xDir > 0.0)
            facingRight = true;
        else if (xDir < 0.0)
            facingRight = false;
    }
    else
        anim.setAnim("idle");

    anim.setAnim(xDir ? "walk" : "idle");
    const kn::Frame* frame = anim.nextFrame(dt);
    frame->tex->flip.h = !facingRight;
    kn::window::blit(*frame->tex, rect, frame->rect);
}