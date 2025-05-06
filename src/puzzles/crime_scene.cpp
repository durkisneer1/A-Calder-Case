#include "puzzles/CrimeScene.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static bool anyItemOpen = false;
static const kn::Color textColor = kn::color::fromHex("#eaf0d8");

CrimeScene::CrimeScene()
    : concreteBg("../assets/environ/concrete-bg.png")
    , bgSize(concreteBg.getSize())
    , font("kraken-retro", 8)
    , wetTowel("../assets/clue-items/towel.png",
          "../assets/clue-items/towel-highlight.png",
          "../assets/clue-items/big-towel.png",
          { 340, 200 },
          font,
          1)
    , bootPrint("../assets/clue-items/bootprint.png",
          "../assets/clue-items/bootprint-highlight.png",
          "../assets/clue-items/big-bootprint.png",
          { 277, 54 },
          font,
          2)
    , burnedLetter("../assets/clue-items/note.png",
          "../assets/clue-items/note-highlight.png",
          "../assets/clue-items/big-note.png",
          { 54, 39 },
          font,
          3)
    , tornPicture("../assets/clue-items/photo.png",
          "../assets/clue-items/photo-highlight.png",
          "../assets/clue-items/big-photo.png",
          { 65, 200 },
          font,
          4)
    , usbStick("../assets/clue-items/usb.png",
          "../assets/clue-items/usb-highlight.png",
          "../assets/clue-items/big-usb.png",
          { 374, 99 },
          font,
          5)
{
}

void CrimeScene::update()
{
    if (!anyItemOpen)
    {
        const auto mRel = kn::mouse::getRel();
        if (kn::mouse::isPressed(kn::M_RIGHT))
        {
            panCam -= mRel;
            panCam = kn::math::clampVec(panCam, { 0, 0 }, bgSize - kn::window::getSize());
        }
    }

    kn::camera = panCam;
    kn::window::blit(concreteBg);

    wetTowel.drawIcon();
    bootPrint.drawIcon();
    burnedLetter.drawIcon();
    tornPicture.drawIcon();
    usbStick.drawIcon();

    wetTowel.drawDetails();
    bootPrint.drawDetails();
    burnedLetter.drawDetails();
    tornPicture.drawDetails();
    usbStick.drawDetails();
}

EvidenceItem::EvidenceItem(const std::string& iconPath, const std::string& iconHL, const std::string& imgPath, const kn::Vec2& pos, const kn::Font& font, const int descID)
    : iconTex(iconPath)
    , iconHighlight(iconHL)
    , imgTex(imgPath)
    , rect(iconTex.getRect())
{
    rect.center(pos);

    std::ifstream file("../assets/crime_scene_clues.json");
    json clues;
    file >> clues;
    textDesc = font.render(clues[std::to_string(descID)], false, textColor, kn::window::getSize().x / 3);
}

void EvidenceItem::drawIcon()
{
    const bool colliding = rect.collidePoint(kn::mouse::getPos());

    if (kn::mouse::isJustPressed(kn::M_LEFT) && colliding && !anyItemOpen)
    {
        opened = true;
        anyItemOpen = true;
        justOpened = true;
    }

    if (colliding && !anyItemOpen)
        kn::window::blit(iconHighlight, rect);
    kn::window::blit(iconTex, rect);
}

void EvidenceItem::drawDetails()
{
    if (!opened)
        return;

    const auto winSize = kn::window::getSize();
    kn::draw::rect({ kn::camera, winSize }, { 0, 0, 0, 150 });

    const kn::Vec2 imgPos = { winSize.x * 3 / 4, winSize.y / 2 };
    kn::window::blit(imgTex, kn::camera + imgPos, kn::CENTER);

    const kn::Vec2 textPos = { winSize.x / 4, winSize.y / 2 };
    kn::window::blit(textDesc, kn::camera + textPos, kn::CENTER);

    if (justOpened)
    {
        justOpened = false;
        return;
    }

    if (kn::mouse::isJustPressed(kn::M_LEFT))
    {
        opened = false;
        anyItemOpen = false;
    }
}
