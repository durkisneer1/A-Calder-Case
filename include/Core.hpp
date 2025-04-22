#pragma once

#include <KrakenEngine.hpp>
#include <unordered_map>

class BaseState;

enum class AppState
{
    WORLD,
};

class Core final
{
public:
    double dt;
    AppState currState;

    Core();
    ~Core();

    void run();

private:
    kn::Event event;
    kn::Clock clock;
    std::unordered_map<AppState, BaseState*> stateMap;
};
