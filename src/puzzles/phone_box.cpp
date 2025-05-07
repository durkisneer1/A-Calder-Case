#include "puzzles/PhoneBox.hpp"
#include <unordered_map>

PhoneBox::PhoneBox()
    : phoneBooth("../assets/phone-booth.png")
    , phoneHighlight("../assets/phone-booth-highlight.png")
    , phoneRect(phoneBooth.getRect())
    , phoneOpen("../assets/phone-dial.png")
    , phoneDialSfx("../assets/audio/phone dial.ogg")
    , phoneRingSfx("../assets/audio/phone ring.ogg")
    , phoneInvalidSfx("../assets/audio/invalid.ogg")
    , phoneHangupSfx("../assets/audio/hang up.ogg")
    , ringTimer(11) // 11
{
    phoneRect.bottomLeft({ 288, 104 });

    dialogues.emplace("Darlene", Dialogue("Darlene", "4"));
    dialogues.emplace("Mallory", Dialogue("Mallory", "1"));
    dialogues.emplace("Andre", Dialogue("Andre", "3"));

    phoneDialSfx.setVolume(0.1f);
    phoneRingSfx.setVolume(0.15f);
    phoneInvalidSfx.setVolume(0.1f);
    phoneHangupSfx.setVolume(0.2f);
}

bool PhoneBox::ready() const
{
    return readyToDial && open;
}

void PhoneBox::addNumber(int num)
{
    static std::unordered_map<std::string, std::string> phoneNumbers = {
        { "3124483", "Darlene" }, { "2849001", "Mallory" }, { "7650214", "Andre" }
    };

    phoneDialSfx.play();

    phoneNumber += std::to_string(num);
    if (phoneNumber.size() == 7)
    {
        if (phoneNumbers.find(phoneNumber) != phoneNumbers.end())
        {
            currentDialogue = &dialogues.at(phoneNumbers.at(phoneNumber));
            currentDialogue->reset();
            phoneRingSfx.play();
            ringTimer.start();
            readyToDial = false;
        }
        else
        {
            phoneInvalidSfx.play();
            phoneNumber.clear();
            readyToDial = true;
        }
    }
}

void PhoneBox::drawBooth(const kn::Rect& playerRect)
{
    kn::window::blit(phoneBooth, phoneRect);
    if (open)
        return;

    if (phoneRect.collideRect(playerRect))
    {
        kn::window::blit(phoneHighlight, phoneRect);
        if (kn::key::isJustPressed(kn::S_e))
        {
            open = true;
            justOpened = true;
        }
    }
}

void PhoneBox::drawDial()
{
    if (!open)
        return;

    if (justOpened)
    {
        justOpened = false;
        return;
    }

    if (kn::key::isJustPressed(kn::K_ESC))
    {
        open = false;
    }

    kn::draw::rect({ kn::camera, kn::window::getSize() }, { 0, 0, 0, 150 });
    kn::window::blit(phoneOpen, kn::camera + kn::window::getSize() / 2, kn::CENTER);

    if (!ringTimer.isFinished() || readyToDial)
        return;

    currentDialogue->animate();
    if (currentDialogue->isDone())
    {
        phoneHangupSfx.play();
        currentDialogue = nullptr;
        readyToDial = true;
        phoneNumber.clear();
    }
}
