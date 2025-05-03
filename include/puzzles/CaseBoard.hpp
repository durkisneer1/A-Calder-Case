#pragma once

#include <KrakenEngine.hpp>

struct CluePin;

class CaseBoardUI
{
public:
    CaseBoardUI();
    ~CaseBoardUI() = default;

    void update();

private:
    std::vector<CluePin> cluePins;
    std::vector<CluePin> activeCluePins;
    std::array<int, 3> password = { 1, 2, 3 };
};

struct CluePin
{
    CluePin(int id, const kn::Vec2& pos);

    int id;
    kn::Vec2 pos;
    int radius = 4;
    bool active = false;
};
