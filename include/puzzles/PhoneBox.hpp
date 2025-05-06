#pragma once

#include <KrakenEngine.hpp>

class PhoneBox
{
public:
    PhoneBox();
    ~PhoneBox() = default;

    void drawBooth(const kn::Rect& playerRect);
    void drawDial();

private:
    const kn::Texture phoneBooth;
    const kn::Texture phoneHighlight;
    kn::Rect phoneRect;

    bool open = false;
};
