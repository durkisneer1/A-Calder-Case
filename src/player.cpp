#include "Player.hpp"

#define AxisX 0
#define AxisY 1

Player::Player(const kn::Layer* colLayer, const kn::Vec2& spawnPos)
    : rect(spawnPos, 21, 41)
    , colLayer(colLayer)
{
    anim.loadSpriteSheet("idle", "../assets/player/idle.png", rect.size(), 7);
    anim.loadSpriteSheet("walk", "../assets/player/walk.png", rect.size(), 7);
}

kn::Rect Player::getRect() const
{
    return rect;
}

void Player::update(const double dt)
{
    if (onGround)
    {
        if (kn::input::isJustPressed("jump"))
        {
            vel.y = -100;
            onGround = false;
        }
    }
    else
    {
        vel.y += 980.7 * dt;
    }

    const double xDir = kn::input::getAxis("left", "right");
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

    vel.x = xDir * SPEED;
    rect.x += static_cast<float>(vel.x * dt);
    handleCollision(AxisX);
    rect.y += static_cast<float>(vel.y * dt);
    handleCollision(AxisY);

    const auto winSize = kn::window::getSize();
    if (rect.left() < 0)
        rect.left(0);
    if (rect.right() > winSize.x)
        rect.right(winSize.x);

    const kn::Frame* frame = anim.nextFrame(dt);
    frame->tex->flip.h = !facingRight;
    kn::window::blit(*frame->tex, rect, frame->rect);
}

void Player::handleCollision(const int axis)
{
    for (const auto& tile : colLayer->tiles)
        if (rect.collideRect(tile.collider))
        {
            if (axis == AxisX)
            {
                if (vel.x > 0.0)
                    rect.right(tile.collider.left());
                else if (vel.x < 0.0)
                    rect.left(tile.collider.right());
            }
            else if (axis == AxisY)
            {
                if (vel.y > 0.0)
                {
                    rect.bottom(tile.collider.top());
                    onGround = true;
                }
                else if (vel.y < 0.0)
                    rect.top(tile.collider.bottom());
                vel.y = 0.0;
            }
            break;
        }
}