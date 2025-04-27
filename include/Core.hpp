#pragma once

#include <KrakenEngine.hpp>
#include <unordered_map>

class BaseState;

enum class AppState
{
    ROOM,
    OUTSIDE,
    CRIME,
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
    std::unordered_map<AppState, BaseState*> stateMap;
};
