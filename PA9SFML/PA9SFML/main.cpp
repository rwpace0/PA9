#include "Game.hpp"
#include "test.hpp"



int main()
{
    Game game;

    bool result = test::run_tests();

    game.run();

    return 0;
}