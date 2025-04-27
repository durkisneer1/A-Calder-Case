#include "Core.hpp"
#include "Input.hpp"
#include "states/RoomState.hpp"
#include "states/OutsideState.hpp"

Core::Core()
    : currState(AppState::OUTSIDE)
{
    kn::window::init({ 320, 180 }, "Noir Jam", true);

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

    stateMap[AppState::ROOM] = new RoomState(this);
    stateMap[AppState::OUTSIDE] = new OutsideState(this);
}

Core::~Core()
{
    for (auto& [key, value] : stateMap)
    {
        delete value;
        value = nullptr;
    }
    stateMap.clear();
    kn::window::quit();
}

void Core::run()
{
    kn::Event event;
    kn::Clock clock;
    clock.tick(240); // Clear first tick

    while (kn::window::isOpen())
    {
        dt = clock.tick(240);

        while (kn::window::pollEvent(event));
        if (kn::key::isJustPressed(kn::K_ESC))
            kn::window::close();

        stateMap.at(currState)->update();
        kn::window::flip();
    }
}
