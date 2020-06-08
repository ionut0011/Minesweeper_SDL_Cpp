#include "Game.h"
#include <iostream>
#include <ctime>
#include "TextureManager.h"
#include "Map.h"


Map* map;
Map* map1;


Game::Game(): isRunning(false), window(nullptr), renderer(nullptr), Start_it(false), Go_Reset(false), is_Reseted(false), getout(false), You_Win(false)
{
}

Game::~Game()
{
   
}

void Game::initgamewindow()
{
	SCREEN_WIDTH = 736;
	SCREEN_HEIGHT = 704;
	init("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
}

void Game::YouWon()
{
	if (map->GameWon())
	{
		isRunning = false;
		You_Win = true;
		reveal();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Congratulations!", "You've won the game!", NULL);
		map->count_bombs = 0; // apareau doua ferestre de "you won", nu stiu de ce, cu conditia asta va aparea doar 1..
	}
}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
		if (window!=nullptr)
		{
			std::cout << "Window created" << std::endl;
		}
		SDL_SetWindowResizable(window,SDL_TRUE);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
			std::cout << "Renderer created" << std::endl;
		}
		
		isRunning = true;
		Go_Reset = false;
		is_Reseted = false;
	}
	else
	{
		
		isRunning = false;
		Go_Reset = true;
		is_Reseted = true;
	}

	map = new Map(renderer);
	
   }

void Game::ShowGameMap()
{
	givedata(DifSelected, DimSelected);
	map->Dimensiunea();
	map->AlocareMemorie3D(map->mat);
	map->AlocareMemorie3D(map->map);
	map->DoMap();
	map->LoadMap(map->mat);
}

	/// <summary>
	///		Aceasta functie preia coordonatele (x,y) selectate de jucator cu mouse-ul, in timpul jocului, si le transmite mai departe
	/// pentru urmatoare operatii de descoperire a patratelelor.
	/// </summary>
void Game::PlayingEvents()
{
	render();
	YouWon();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
		{
			Go_Reset = true;
			i_have_quitted = true;
			clean();
			SDL_Quit();
			break;
		}
		default:
			break;
		}

		switch (event.button.type)
		{

		case SDL_MOUSEBUTTONDOWN:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{

				MouseX = event.motion.y / 32;
				MouseY = event.motion.x / 32;
				if (map->dimension == 1)
				{
					if ((event.motion.x >= 7 * 32) && (event.motion.y >= 5 * 32) && (event.motion.x < 16 * 32) && (event.motion.y <= 18 * 32))
					{
						isRunning = map->PressMine(MouseX, MouseY);

						SDL_WaitEvent(&event);

					}
					if ((event.motion.x >= 11 * 32) && (event.motion.y >= 4 * 32) && (event.motion.x <= 12 * 32) && (event.motion.y < 5 * 32))
					{
						Go_Reset = true;
						SDL_WaitEventTimeout(&event, 500);
					}
					YouWon();
				}
				if (map->dimension == 2)
				{
					if ((event.motion.x >= 6 * 32) && (event.motion.y >= 3 * 32) && (event.motion.x <= 17 * 32) && (event.motion.y <= 20 * 32))
					{
						isRunning = map->PressMine(MouseX, MouseY);
						SDL_WaitEvent(&event);
					}
					if ((event.motion.x >= 11 * 32) && (event.motion.y >= 2 * 32) && (event.motion.x <= 12 * 32) && (event.motion.y <= 3 * 32))
					{
						Go_Reset = true;
						SDL_WaitEventTimeout(&event, 500);
					}
					YouWon();
				}
				if (map->dimension == 3)
				{
					if ((event.motion.x >= 32) && (event.motion.y >= 64) && (event.motion.x <= 704) && (event.motion.y <= 736))
					{
						isRunning = map->PressMine(MouseX, MouseY);
						SDL_WaitEvent(&event);
					}
					if ((event.motion.x >= 11 * 32) && (event.motion.y >= 1 * 32) && (event.motion.x <= 12 * 32) && (event.motion.y <= 2 * 32))
					{
						Go_Reset = true;
						SDL_WaitEventTimeout(&event, 500);
					}
					YouWon();
				}

				break;
			}
			case SDL_BUTTON_RIGHT:
			{

				MouseX = event.motion.y / 32;
				MouseY = event.motion.x / 32;
				if (map->dimension == 1)
				{
					if ((event.motion.x > 7 * 32) && (event.motion.y > 5 * 32) && (event.motion.x < 16 * 32) && (event.motion.y < 18 * 32) && isflag == true)
					{
						SDL_WaitEvent(&event);
						map->DoSteag(MouseX, MouseY);
					}
					YouWon();
				}
				if (map->dimension == 2)
				{
					if ((event.motion.x > 6 * 32) && (event.motion.y > 3 * 32) && (event.motion.x < 17 * 32) && (event.motion.y < 20 * 32) && isflag == true)
					{
						map->DoSteag(MouseX, MouseY);
						SDL_WaitEvent(&event);
					}
					YouWon();
				}
				if (map->dimension == 3)
				{
					if ((event.motion.x > 32) && (event.motion.y > 64) && (event.motion.x < 704) && (event.motion.y < 736) && isflag == true)
					{
						map->DoSteag(MouseX, MouseY);
						SDL_WaitEvent(&event);
					}
					YouWon();
				}

				break;
			}

			default:
			{
				break;
			}
			}
		}
		}
	}
}
void Game::reveal()
{
	map->RevealALL();
}
void Game::render() const
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	
	if (DifSelected != 0 && DimSelected != 0 && Start_it == true)
	{
		map->DrawMap();
	}
	else
	{
		map->DrawMainMenu();
	}
	SDL_RenderPresent(renderer);
	
}
void Game::alocamemorie()
{
	map->AlocareMemorie3D(map->mat);
	map->AlocareMemorie3D(map->map);
}
void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	if (DifSelected != 0)
	{
		map->Delete3D(map->mat);
		map->Delete3D(map->map);
	}
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}

void Game::givedata(int difficulty, int dimension)
{
	map->givedata(difficulty,dimension);
}

	/// <summary>
	///		Aceasta functie se apeleaza in momentul in care jucatorul loveste o bomba, acesta avand in caz afirmativ
	/// doar 2 solutii, sa reseteze jocul sau sa inchida fereastra.
	/// </summary>
void Game::boom_do_reset_or_quit()
{
	render();
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
		{
			Go_Reset = true;
			i_have_quitted = true;
			SDL_Quit();
			break;
		}
		default:
			break;
		}
		event.type = SDL_MOUSEBUTTONDOWN;
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
		{

			//contor++;
			if (map->dimension == 1)
			{
				if ((event.motion.x >= 11 * 32) && (event.motion.y >= 4 * 32) && (event.motion.x <= 12 * 32) && (event.motion.y <= 5 * 32))
				{
					
					Go_Reset = true;
					SDL_WaitEventTimeout(&event, 500);
				}
			}
			if (map->dimension == 2)
			{
				if ((event.motion.x >= 11 * 32) && (event.motion.y >= 2 * 32) && (event.motion.x <= 12 * 32) && (event.motion.y <= 3 * 32))
				{
					Go_Reset = true;
					SDL_WaitEventTimeout(&event, 500);
				}
			}
			if (map->dimension == 3)
			{
				if ((event.motion.x >= 11 * 32) && (event.motion.y >= 1 * 32) && (event.motion.x <= 12 * 32) && (event.motion.y <= 2 * 32))
				{
					Go_Reset = true;
					SDL_WaitEventTimeout(&event, 500);
				}
			}
		}
		default:
			break;
		}
	}
}
	/// <summary>
	/// In aceasta functie are loc totul:
	///		- ce se intampla in timpul jocului
	///		- cand playerul a lovit o bomba
	///		- cand doreste sa iasa din joc
	///		- cand doreste sa reseteze jocul
	/// </summary>
void Game::GoGame()
{

	//render();
	Go_Reset = false;
	isRunning = true;
	{
		ShowGameMap();
		while (running() && !doreset())
		{
			PlayingEvents();
			
		}
		if (i_have_quitted == false)
		{
			reveal();
			render();
		}
		if (!running() && !Winner())
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Congratulations!", "You've lost!", NULL);
		}	
		while (!doreset()) // daca apesi pe bomba, mai ai 2optiuni, reset sau quit
		{
			boom_do_reset_or_quit();
		}
		if ((doreset()) && (i_have_quitted == false))
		{
			is_Reseted = true;
			GoChoice();
		}
	}
	getout = true;
}

	/// <summary>
	/// Functia prin care jucatorul selecteaza dificultate si dimensiunea necesare pentru a incepe jocul.
	/// </summary>
void Game::ChoosingModeEvent()
{
	givedata(DifSelected, DimSelected);
	render();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
		{
			clean();
			getout = true;
			Start_it = true;
			SDL_Quit();
			break;
		}
		default:
			break;
		}
		switch (event.button.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				if (event.motion.x >= 145 && event.motion.x <= 250 && event.motion.y >= 390 && event.motion.y <= 440)
				{
					DifSelected = 1;
					SDL_WaitEventTimeout(&event, 300);
				}
				if (event.motion.x >= 145 && event.motion.x <= 250 && event.motion.y >= 445 && event.motion.y <= 495)
				{
					DifSelected = 2;
					SDL_WaitEventTimeout(&event, 300);
				}
				if (event.motion.x >= 145 && event.motion.x <= 250 && event.motion.y >= 500 && event.motion.y <= 550)
				{
					DifSelected = 3;
					SDL_WaitEventTimeout(&event, 300);
				}
				if (event.motion.x >= 470 && event.motion.x <= 570 && event.motion.y >= 390 && event.motion.y <= 440)
				{
					DimSelected = 1;
					SDL_WaitEventTimeout(&event, 300);
				}
				if (event.motion.x >= 470 && event.motion.x <= 570 && event.motion.y >= 445 && event.motion.y <= 495)
				{
					DimSelected = 2;
					SDL_WaitEventTimeout(&event, 300);
				}
				if (event.motion.x >= 470 && event.motion.x <= 570 && event.motion.y >= 500 && event.motion.y <= 550)
				{
					DimSelected = 3;
					SDL_WaitEventTimeout(&event, 300);
				}
				if (event.motion.x >= 310 && event.motion.x <= 410 && event.motion.y >= 390 && event.motion.y <= 440)
				{
					if (DimSelected != 0 && DifSelected != 0)
					{
						Start_it = true;
						Dim_and_Dif_selected = true;
						SDL_WaitEventTimeout(&event, 650);
					}
				}

			}
			}
		}
		}
	}
}
void Game::GoChoice()
{
	Dim_and_Dif_selected = false;
	Start_it = false;
	DimSelected = 0;
	DifSelected = 0;
	if (Dim_and_Dif_selected == false)
	{
		while (!start())
		{
			ChoosingModeEvent();
		}
	}
	if (Dim_and_Dif_selected == true)
	{
		GoGame();
	}
	getout = true;
}



// daca deschizi a 2-a oara fereastra de joc, nu o poti inchide ...........
// daca este deja deschisa fereastra de selectare dificultate, sa nu mai poti deschide alta cu butonul reset
