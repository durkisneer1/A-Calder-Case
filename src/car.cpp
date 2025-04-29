#include "Car.hpp"
#include "Core.hpp"

Car::Car()
    : tex("../assets/car.png"), drawRect(tex.getRect()), nextState(AppState::CRIME)
{
    drawRect.bottomLeft({16, 104});
}

void Car::update()
{
    kn::window::blit(tex, drawRect);
}