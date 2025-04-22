#include "Core.hpp"
#include "states/WorldState.hpp"

Core::Core()
    : currState(AppState::WORLD)
{
    kn::window::init({ 320, 180 }, "Noir Jam", true);
    kn::camera = { -8, -30 };

    kn::input::bind("left",
        {
            kn::InputAction(kn::S_a),
            kn::InputAction(kn::C_AXIS_LEFTX, false),
        });
    kn::input::bind("right",
        {
            kn::InputAction(kn::S_d),
            kn::InputAction(kn::C_AXIS_LEFTX, true),
        });
    kn::input::bind("jump",
        {
            kn::InputAction(kn::S_SPACE),
            kn::InputAction(kn::C_SOUTH),
        });

    stateMap[AppState::WORLD] = new WorldState(this);
}

Core::~Core()
{
    kn::window::quit();
}

void Core::run()
{
    const kn::Color BG_COLOR = kn::color::fromHex("#1f1f29");
    clock.tick(240);

    while (kn::window::isOpen())
    {
        dt = clock.tick(240);

        while (kn::window::pollEvent(event));
        if (kn::key::isJustPressed(kn::K_ESC))
            kn::window::close();

        kn::window::clear(BG_COLOR);
        stateMap.at(currState)->update();
        kn::window::flip();
    }
}
