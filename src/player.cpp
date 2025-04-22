#include "Player.hpp"

#define AxisX 0
#define AxisY 1

Player::Player()
    : rect(8, 56, 21, 41)
{
    anim.loadSpriteSheet("idle", "../assets/player/idle.png", rect.size(), 7);
    anim.loadSpriteSheet("walk", "../assets/player/walk.png", rect.size(), 7);
}

void Player::update(const double dt, const std::vector<kn::Tile>& colTiles)
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
    handleCollision(AxisX, colTiles);
    rect.y += static_cast<float>(vel.y * dt);
    handleCollision(AxisY, colTiles);

    const kn::Frame* frame = anim.nextFrame(dt);
    frame->tex->flip.h = !facingRight;
    kn::window::blit(*frame->tex, rect, frame->rect);
}

void Player::handleCollision(const int axis, const std::vector<kn::Tile>& colTiles)
{
    for (const auto& tile : colTiles)
        if (rect.collideRect(tile.rect))
        {
            if (axis == AxisX)
            {
                if (vel.x > 0.0)
                    rect.right(tile.rect.left());
                else if (vel.x < 0.0)
                    rect.left(tile.rect.right());
            }
            else if (axis == AxisY)
            {
                if (vel.y > 0.0)
                {
                    rect.bottom(tile.rect.top());
                    onGround = true;
                }
                else if (vel.y < 0.0)
                    rect.top(tile.rect.bottom());
                vel.y = 0.0;
            }
            break;
        }
}