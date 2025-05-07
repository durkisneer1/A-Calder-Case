#pragma once

#include "states/BaseState.hpp"

class Core;

class EndState final : public BaseState
{
public:
    EndState(Core* core, const std::string& message);
    ~EndState() = default;

    void update() override;

private:
    kn::Texture messageTex;
    kn::Texture escTex;
};
