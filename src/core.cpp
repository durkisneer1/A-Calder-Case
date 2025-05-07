#include "Core.hpp"
#include "Input.hpp"
#include "states/RoomState.hpp"
#include "states/OutsideState.hpp"
#include "states/CrimeState.hpp"
#include "states/EndState.hpp"
#include "states/PauseState.hpp"

Core::Core()
    : currState(AppState::ROOM) // AppState::ROOM
{
    prevPauseState = currState;

    kn::window::init({ 320, 180 }, "A Calder Case", true);

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
    stateMap[AppState::CRIME] = new CrimeState(this);
    stateMap[AppState::GOOD] = new EndState(this, "You figured out the killer.");
    stateMap[AppState::BAD] = new EndState(this, "You imprisoned the wrong suspect.");
    stateMap[AppState::PAUSE] = new PauseState(this);
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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    kn::Event event;
    kn::Clock clock;
    clock.tick(); // Clear first tick

    kn::music::load("../assets/audio/The Calder Case.ogg");
    kn::music::setVolume(0.03f);
    kn::music::play(-1, 5000);

    while (kn::window::isOpen())
    {
        dt = clock.tick(240);
        BaseState* state = stateMap.at(currState);

        while (kn::window::pollEvent(event))
        {
            state->handleEvents(event);
        }

        state->update();
        kn::window::flip();
    }
}
