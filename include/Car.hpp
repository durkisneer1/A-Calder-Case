#pragma once
#include <KrakenEngine.hpp>

enum class AppState;

class Car
{
public:
    Car();
    ~Car() = default;

    void update();

private:
    kn::Texture tex;
    kn::Rect drawRect;
    AppState nextState;
};
