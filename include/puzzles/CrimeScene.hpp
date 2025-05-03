#pragma once

#include <KrakenEngine.hpp>

class EvidenceItem;

class CrimeScene
{
public:
    CrimeScene();
    ~CrimeScene() = default;

    void draw();

private:
    const kn::Texture bgImg;
    EvidenceItem note;
    EvidenceItem pen;
};

class EvidenceItem
{
public:
    EvidenceItem(const std::string& iconPath, const std::string& imgPath, const kn::Vec2& pos);
    ~EvidenceItem() = default;

    void update();

private:
    const kn::Vec2 pos;
    const kn::Texture iconTex;
    const kn::Texture imgTex;
};