#pragma once
#include <SDL_image.h>
#include "Game.h"

class Map
{
public:
	Map(SDL_Renderer* renderer);
	
	~Map();

	int maxX;
	int maxY;
	int xPos;
	int yPos;
	int Aria;
	int difficulty;
	int dimension;
	int xmain;
	int ymain; // coordonatele de unde incep sa construiesc matricea
	void AlocareMemorie3D(int ***&matt);
	void Delete3D(int ***&matt);
	void DoMap();
	void LoadMap(int*** arr);	
	void DrawMainMenu();
	void DrawMap();
	int r;
	int*** dif;
	int count_bombs;
	
	int number_of_flags ;
	int number_of_blocks;
	int good_flags;
	int wrongflags;
	int RevealedPos;
	int PosHasZero;
	bool GameWon();
	void Dimensiunea();
	
	bool PressMine(int MouseX, int MouseY);
	void RevealAround(int MouseX, int MouseY);
	void DoSteag(int MouseX,int MouseY);
	void RevealALL();
	void givedata(int dificultatea, int dimensiunea); // aducem dificultatea in main
	
	

	int*** map;
	int*** mat;


private:
	
	SDL_Renderer* renderer;
	
	SDL_Rect src, dest;
	
	SDL_Texture* unu;
	SDL_Texture* dific;
	SDL_Texture* doi;
	SDL_Texture* trei;
	SDL_Texture* patru;
	SDL_Texture* cinci;
	SDL_Texture* sase;
	SDL_Texture* sapte;
	SDL_Texture* opt;
	SDL_Texture* bomb;
	SDL_Texture* steag;
	SDL_Texture* block;
	SDL_Texture* zero;
	SDL_Texture* sideup;
	SDL_Texture* sideright;
	SDL_Texture* sidedown;
	SDL_Texture* sideleft;
	SDL_Texture* corner;
	SDL_Texture* redbomb;
	SDL_Texture* wrongflag;
	SDL_Texture* nodead;
	SDL_Texture* dead;
	SDL_Texture* halfdead;
	
	SDL_Texture* easy0;
	SDL_Texture* dimmedium0;
	SDL_Texture* large0;
	SDL_Texture* small0;
	SDL_Texture* difmedium0;
	SDL_Texture* hard0;
	SDL_Texture* easysmall;
	SDL_Texture* easymed;
	SDL_Texture* easylarge;
	SDL_Texture* medsmall;
	SDL_Texture* medmed;
	SDL_Texture* medlarge;
	SDL_Texture* hardlarge;
	SDL_Texture* hardmed;
	SDL_Texture* hardsmall;
	
};