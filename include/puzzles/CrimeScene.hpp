#pragma once

#include <KrakenEngine.hpp>

class EvidenceItem
{
public:
    EvidenceItem(const std::string& iconPath, const std::string& iconHL, const std::string& imgPath, const kn::Vec2& pos, const kn::Font& font, const int descID);
    ~EvidenceItem() = default;

    void drawIcon();
    void drawDetails();

private:
    const kn::Texture iconTex;
    const kn::Texture iconHighlight;
    const kn::Texture imgTex;
    kn::Rect rect;

    kn::Texture textDesc;

    bool opened = false;
    bool justOpened = false;
};

class CrimeScene
{
public:
    CrimeScene();
    ~CrimeScene() = default;

    void update();

private:
    const kn::Texture concreteBg;
    const kn::Vec2 bgSize;
    const kn::Font font;

    EvidenceItem wetTowel;
    EvidenceItem bootPrint;
    EvidenceItem burnedLetter;

    kn::Vec2 panCam;
};
