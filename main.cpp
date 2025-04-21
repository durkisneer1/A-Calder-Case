#include <KrakenEngine.hpp>

#include "Core.hpp"

int main()
{
    kn::window::init({ 320, 180 }, "Noir Jam", true);
    
    Core core;
    core.run();

    return EXIT_SUCCESS;
}