//Using SDL and standard IO
#include "Game.h"
#include <SDL.h>
#include "Map.h"

//Screen dimension constants



int main(int argc, char* args[])
{

	auto game = new Game();
	game->initgamewindow();
	while (!game->Program_is_done())
	{	
		game->GoChoice();
	}
		
	delete game;
	SDL_Delay(500);
	return 0;
}