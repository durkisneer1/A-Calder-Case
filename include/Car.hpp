#pragma once
#include <KrakenEngine.hpp>

enum class AppState;

class Car
{
public:
    Car();
    ~Car() = default;

    bool updateAndCollide(const kn::Rect &playerRect);

private:
    kn::Texture tex;
    kn::Texture highlight;
    kn::Rect rect;
    AppState nextState;
};
