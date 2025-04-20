#include <KrakenEngine.hpp>

#include "Player.hpp"

int main()
{
    const kn::Color BG_COLOR = kn::color::fromHex("#1f1f29");

    kn::window::init({ 320, 180 }, "Noir Jam", true);
    kn::Event event;
    kn::Clock clock;

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

    Player player;

    while (kn::window::isOpen())
    {
        const double dt = clock.tick(240);

        while (kn::window::pollEvent(event));
        if (kn::key::isJustPressed(kn::K_ESC))
            kn::window::close();

        kn::window::clear(BG_COLOR);

        player.update(dt);

        kn::window::flip();
    }

    kn::window::quit();

    return EXIT_SUCCESS;
}