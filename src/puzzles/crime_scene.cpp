#include "puzzles/CrimeScene.hpp"

CrimeScene::CrimeScene()
{
}

EvidenceItem::EvidenceItem(const std::string& iconPath, const std::string& imgPath, const kn::Vec2& pos)
    : iconTex(iconPath)
    , imgTex(imgPath)
    , pos(pos)
{
}

void EvidenceItem::update()
{
    
}