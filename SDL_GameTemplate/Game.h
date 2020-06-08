#pragma once
#include <SDL.h>
#include "Map.h"

class Game
{
public:
	Game();
	~Game();
	//void DoGame();
	bool isflag = true;
	//void flagfalse();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	int DimSelected;
	int DifSelected;
	int DimSelected1()  { return DimSelected; }
	int DifSelected1()  { return DifSelected;  }
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	int MouseX = 0;
	int MouseY = 0;

	void ShowGameMap();
	void PlayingEvents();
	void ChoosingModeEvent();
	
	void reveal();
	void render() const;
	void clean();
	bool i_have_quitted;

	bool Dim_and_Dif_selected;

	void initgamewindow();
	bool running() const { return isRunning;  }
	bool start() const { return Start_it; }
	bool doreset() const { return Go_Reset; }
	bool Reset_is_up() const { return is_Reseted;  }
	void givedata(int difficulty, int dimension); 

	void alocamemorie();
	
	void GoGame();
	void GoChoice();
	void YouWon();
	bool Program_is_done() const { return getout; }
	bool Winner() const { return You_Win; }
	void boom_do_reset_or_quit();
	
	
	SDL_Event goquit;
private:

	
	SDL_Renderer* renderer;
	
	SDL_Window* window;
	bool isRunning;
	bool Start_it;
	bool Go_Reset;
	bool is_Reseted;
	bool getout;
	bool You_Win;
};
