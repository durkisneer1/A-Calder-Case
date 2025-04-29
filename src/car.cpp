#include "Car.hpp"
#include "Core.hpp"

Car::Car()
    : tex("../assets/car.png")
    , highlight("../assets/car-highlight.png")
    , rect(tex.getRect())
    , nextState(AppState::CRIME)
{
    rect.bottomLeft({ 16, 104 });
}

bool Car::updateAndCollide(const kn::Rect& playerRect)
{
    const bool collides = rect.collideRect(playerRect);
    if (collides)
        kn::window::blit(highlight, rect);
    kn::window::blit(tex, rect);

    return collides;
}