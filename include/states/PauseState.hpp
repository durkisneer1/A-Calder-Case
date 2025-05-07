#pragma once

#include "states/BaseState.hpp"

class Core;

class PauseState final : public BaseState
{
public:
    PauseState(Core* core);
    ~PauseState() = default;

    void update() override;

private:
    kn::Texture pausedTex;
    kn::Texture resumeTex;
    kn::Texture quitTex;
};