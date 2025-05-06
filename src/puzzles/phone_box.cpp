#include "puzzles/PhoneBox.hpp"

PhoneBox::PhoneBox()
    : phoneBooth("../assets/phone-booth.png")
    , phoneHighlight("../assets/phone-booth-highlight.png")
    , phoneRect(phoneBooth.getRect())
{
    phoneRect.bottomLeft({ 36 * 8, 13 * 8 });
}

void PhoneBox::drawBooth(const kn::Rect& playerRect)
{
    if (open)
        return;

    if (phoneRect.collideRect(playerRect))
    {
        kn::window::blit(phoneHighlight, phoneRect);
        if (kn::key::isJustPressed(kn::S_e))
        {
            open = true;
        }
    }
    kn::window::blit(phoneBooth, phoneRect);
}

void PhoneBox::drawDial()
{
    if (!open)
        return;

    kn::draw::rect({ 0, 0, kn::window::getSize() }, { 0, 0, 0, 150 });
}