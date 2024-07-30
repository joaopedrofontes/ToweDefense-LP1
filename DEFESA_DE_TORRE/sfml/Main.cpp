
#include "Game.h"

int main()
{
 //Initalize random seed
    srand(static_cast<unsigned>(time(0)));

    //Initialize game object
    Game game;

    //Game loop
    while (game.running()) 
    {
        game.update();
        game.render();
    }

    //End
    return 0;
}