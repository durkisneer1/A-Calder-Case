#pragma once

#include <KrakenEngine.hpp>
#include "Dialogue.hpp"

class PhoneBox
{
public:
    PhoneBox();
    ~PhoneBox() = default;

    void addNumber(int num);
    bool ready() const;
    bool isOpen() const
    {
        return open;
    }

    void drawBooth(const kn::Rect& playerRect);
    void drawDial();

private:
    const kn::Texture phoneBooth;
    const kn::Texture phoneHighlight;
    kn::Rect phoneRect;

    const kn::Texture phoneOpen;

    bool open = false;
    bool justOpened = false;

    std::string phoneNumber = "";
    bool readyToDial = true;

    kn::Sound phoneDialSfx;
    kn::Sound phoneRingSfx;
    kn::Sound phoneInvalidSfx;
    kn::Sound phoneHangupSfx;

    kn::Timer ringTimer;

    std::unordered_map<std::string, Dialogue> dialogues;
    Dialogue* currentDialogue = nullptr;
};
