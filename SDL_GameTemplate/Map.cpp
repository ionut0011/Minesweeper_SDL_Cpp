#include <cstdlib>
#include "Map.h"
#include <time.h>
#include "TextureManager.h"
#include <SDL.h>
#include "Game.h"

void Map::Dimensiunea()
{
	/// <summary>
	/// Initializarea parametrilor in functie de dimensiunea aleasa pentru "centrarea" jocului in fereastra
	/// </summary>
	if (this->dimension == 1)
	{
		maxX = 22;
		maxY = 23;
		xmain = 5;
		ymain = 7;
	}
	else if (this->dimension == 2)
	{
		maxX = 22;
		maxY = 23;
		xmain = 3;
		ymain = 6;
	}
	else if (this->dimension == 3)
	{
		maxX = 22;
		maxY = 23;
		xmain = 2;
		ymain = 1;
	}
	xPos = maxX - (2 * xmain - 1);
	yPos = maxY - 2 * ymain;
	Aria = xPos * yPos;
}
void Map::AlocareMemorie3D(int ***&mattr)
{
	
		mattr = new int**[22];
		for (int i = 0; i < 22; i++)
		{
			mattr[i] = new int*[23];
			for (int j = 0; j < 23; j++)
			{
				mattr[i][j] = new int[2];

			}
		}
	
}
void Map::Delete3D(int ***&mattr)
{
	for (int i = 0; i < maxX; i++)
	{
		for (int j = 0; j < maxY; j++)
		{
			delete[] mattr[i][j];
		}
		delete[] mattr[i];
	}
	delete[] mattr;
}

	/// <summary>
	///		Aici:
	///			- atribui valori pozitiilor matricei, care ulterior, in functie de valoarea data, va primi o anumita imagine.
	///		Primul for:
	///			- "desenez" fundalul ferestrei
	///		
	///		Al doilea for:	
	///			- generez aleator un numar intre 1 si x ( x fiind decis un functie de dificultatea aleasa ), iar in functie de valoarea
	///		generata se decide daca la pozitia curenta se va pune "bomba" sau nu.
	///		
	///		Al treilea for:
	///			- parcurg matricea, iar la fiecare pozitie, daca acesteia nu i-a fost atribuita o "bomba", atunci va numara cate
	///		bombe se afla in jurul acestei pozitii, iar valoarea atribuita acelei pozitii va fi numarul de bombe.
	/// 
	///		Observatie: Matricea este de 22x23, dar parcurg doar pozitiile pe care va fi generat jocul, ci nu intreaga matrice.
	/// </summary>
void Map::DoMap()
{
	
		
		for (int i = 0; i < maxX; i++)
		{
			for (int j = 0; j < maxY; j++)
			{
				mat[i][j][0] = 13;
			}
		}
		srand(time(NULL));
		for (int row = xmain; row < maxX - xmain + 1; row++)
		{
			for (int column = ymain; column < maxY - ymain + 1; column++)
			{
				mat[xmain - 1][column][0] = 15;
				mat[maxX - xmain + 1][column][0] = 17;
				{	if (difficulty == 1)
				{
					r = rand() % 14 + 1;
				}
				if (difficulty == 2)
				{
					r = rand() % 9 + 1;
				}
				if (difficulty == 3)
				{
					r = rand() % 7 + 1;
				}
				}
				if (r == 1 || r == 2)
				{

					mat[row][column][0] = 10;
				}
				if (r != 1 && r != 2)
				{
					mat[row][column][0] = 9;
				}
				mat[row][ymain - 1][0] = 18;
				mat[row][maxY - ymain][0] = 16;
			}
		}
		
		// in functie de dimensiunea aleasa, se atribuie valoarea "33" care ii este desemnata smiley face-ului 
		{
			mat[xmain - 1][ymain - 1][0] = 13;
			mat[xmain - 1][maxY - ymain][0] = 13;
			mat[maxX - xmain + 1][ymain - 1][0] = 13;
			mat[maxX - xmain + 1][maxY - ymain][0] = 13;
			if (dimension == 2)
			{
				mat[xmain - 1][maxY / 2][0] = 33;
			}
			if (dimension == 1)
			{
				mat[xmain - 1][maxY / 2][0] = 33;
			}
			if (dimension == 3)
			{
				mat[xmain - 1][maxY / 2][0] = 33;
			}

		}
		int ctr = 0;
		for (int i = xmain; i < maxX - xmain + 1; i++)
		{
			ctr = 0;
			for (int j = ymain; j < maxY - ymain; j++)
			{
				ctr = 0;
				// Colturile ( primele 4 ) > Laturile ( 5,6,7,8 ) > Centrul

				if (mat[i][j][0] == 9)
				{
					if (mat[i + 1][j][0] == 10)
					{
						ctr++;
					}
					if (mat[i + 1][j + 1][0] == 10)
					{
						ctr++;
					}
					if (mat[i + 1][j - 1][0] == 10)
					{
						ctr++;
					}
					if (mat[i - 1][j][0] == 10)
					{
						ctr++;
					}
					if (mat[i - 1][j + 1][0] == 10)
					{
						ctr++;
					}
					if (mat[i - 1][j - 1][0] == 10)
					{
						ctr++;
					}
					if (mat[i][j + 1][0] == 10)
					{
						ctr++;
					}
					if (mat[i][j - 1][0] == 10)
					{
						ctr++;
					}
					mat[i][j][0] = ctr;
					if (ctr == 0)
					{
						PosHasZero++;
					}
				}

				if (mat[i][j][0] == 10)
				{
					mat[i][j][0] = 10;
					count_bombs++;
				}
				
				mat[i][j][1] = 11;
			}

		}
	
}

Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	unu = TextureManager::LoadTexture("assets/unu.png", renderer);
	doi = TextureManager::LoadTexture("assets/doi.png", renderer);
	trei = TextureManager::LoadTexture("assets/trei.png", renderer);
	patru = TextureManager::LoadTexture("assets/patru.png", renderer);
	cinci = TextureManager::LoadTexture("assets/cinci.png", renderer);
	sase = TextureManager::LoadTexture("assets/sase.png", renderer);
	sapte = TextureManager::LoadTexture("assets/sapte.png", renderer);
	opt = TextureManager::LoadTexture("assets/opt.png", renderer);
	bomb = TextureManager::LoadTexture("assets/bomb.png", renderer);
	block = TextureManager::LoadTexture("assets/block.png", renderer);
	zero = TextureManager::LoadTexture("assets/zero.png", renderer);
	steag = TextureManager::LoadTexture("assets/steag.png", renderer);
	redbomb = TextureManager::LoadTexture("assets/redbomb.png", renderer);
	sideup = TextureManager::LoadTexture("assets/sideup.png", renderer);
	sideright = TextureManager::LoadTexture("assets/sideright.png", renderer);
	sidedown = TextureManager::LoadTexture("assets/sidedown.png", renderer);
	sideleft = TextureManager::LoadTexture("assets/sideleft.png", renderer);
	corner = TextureManager::LoadTexture("assets/corner.png", renderer);
	wrongflag = TextureManager::LoadTexture("assets/wrongflag.png", renderer);
	dific = TextureManager::LoadTexture("assets/dif.png", renderer);
	dead = TextureManager::LoadTexture("assets/dead.png", renderer);
	nodead = TextureManager::LoadTexture("assets/undead.png", renderer);
	halfdead = TextureManager::LoadTexture("assets/halfdead.png", renderer);

	easy0 = TextureManager::LoadTexture("assets/easy0.png", renderer);
	dimmedium0 = TextureManager::LoadTexture("assets/dimmedium0.png", renderer);
	large0 = TextureManager::LoadTexture("assets/large0.png", renderer);
	small0 = TextureManager::LoadTexture("assets/small0.png", renderer);
	difmedium0 = TextureManager::LoadTexture("assets/medium0.png", renderer);
	hard0 = TextureManager::LoadTexture("assets/hard0.png", renderer);
	easysmall = TextureManager::LoadTexture("assets/easysmall.png", renderer);
	easymed = TextureManager::LoadTexture("assets/easymed.png", renderer);
	easylarge = TextureManager::LoadTexture("assets/easylarge.png", renderer);
	medsmall = TextureManager::LoadTexture("assets/medsmall.png", renderer);
	medmed = TextureManager::LoadTexture("assets/medmed.png", renderer);
	medlarge = TextureManager::LoadTexture("assets/medlarge.png", renderer);
	hardlarge = TextureManager::LoadTexture("assets/hardlarge.png", renderer);
	hardmed = TextureManager::LoadTexture("assets/hardmed.png", renderer);
	hardsmall = TextureManager::LoadTexture("assets/hardsmall.png", renderer);


	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

}
Map::~Map()
{

}

	/// <summary>
	/// Incarcam matricea "mat" generata in DoMap() in matricea "map" cu care se va lucra mai departe. 
	/// </summary>
void Map::LoadMap(int*** arr)
{		

	for (int row = 0; row < maxX; row++)
	{
		for (int column = 0; column < maxY; column++)
		{
			map[row][column][0] = arr[row][column][0];
			map[row][column][1] = arr[row][column][1];
		}
	}
}

	/// <summary>
	/// Observatie: Am lucrat cu o matricea 3D
	/// 
	/// In primul for:
	///				- desemnam fiecarei pozitii a matricei o imagine specifica, pentru "a da forma" ferestrei.
	/// In al doilea for:
	///				- numaram nr. de steaguri prezente, nr. de steaguri puse bine ( peste o bomba ), nr. de steaguri puse prost,
	///			nr. de bombe si nr. de casute ramase nedescoperite.
	/// </summary>
void Map::DrawMap()
{	
	int type = 0;
	int type1 = 0;
	number_of_blocks = 0;
	number_of_flags = 0;
	good_flags = 0;
	
	wrongflags = 0;
	RevealedPos = 0;
	
		for (int row = 0; row < maxX; row++)
		{
			for (int column = 0; column < maxY; column++)
			{
				type = map[row][column][0];
				type1 = map[row][column][1];

				dest.x = column * 32;
				dest.y = row * 32;
				dest.w = 32;
				dest.h = 32;

				switch (type)
				{

				case 33:
				{
					TextureManager::Draw(halfdead, src, dest, renderer);
					break;
				}
				case 34:
				{
					TextureManager::Draw(dead, src, dest, renderer);
					break;
				}
				case 35:
				{
					TextureManager::Draw(nodead, src, dest, renderer);
					break;
				}
				case 13:
				{
					TextureManager::Draw(corner, src, dest, renderer);
					break;
				}
				case 15:
				{
					TextureManager::Draw(sideup, src, dest, renderer);
					break;
				}
				case 16:
				{
					TextureManager::Draw(sideright, src, dest, renderer);
					break;
				}
				case 17:
				{
					TextureManager::Draw(sidedown, src, dest, renderer);
					break;
				}
				case 18:
				{
					TextureManager::Draw(sideleft, src, dest, renderer);
					break;
				}
				case 10:
				{
					TextureManager::Draw(bomb, src, dest, renderer);
					break;
				}
				case 3:
				{
					TextureManager::Draw(trei, src, dest, renderer);
					break;
				}
				case 2:
				{
					TextureManager::Draw(doi, src, dest, renderer);
					break;
				}
				case 1:
				{
					TextureManager::Draw(unu, src, dest, renderer);
					break;
				}
				case 4:
				{
					TextureManager::Draw(patru, src, dest, renderer);
					break;
				}
				case 5:
				{
					TextureManager::Draw(cinci, src, dest, renderer);
					break;
				}
				case 6:
				{
					TextureManager::Draw(sase, src, dest, renderer);
					break;
				}
				case 7:
				{
					TextureManager::Draw(sapte, src, dest, renderer);
					break;
				}
				case 8:
				{
					TextureManager::Draw(opt, src, dest, renderer);
					break;
				}
				case 12:
				{
					TextureManager::Draw(redbomb, src, dest, renderer);
					break;
				}
				case 0:
				{
					TextureManager::Draw(zero, src, dest, renderer);
					break;
				}
				case 14:
				{
					TextureManager::Draw(zero, src, dest, renderer);
					break;
				}


				default:
					break;
				}

				switch (type1)
				{
				case 11:
				{
					TextureManager::Draw(block, src, dest, renderer);
					break;
				}
				case 9:
				{
					TextureManager::Draw(steag, src, dest, renderer);
					break;
				}
				case 27:
				{
					TextureManager::Draw(wrongflag, src, dest, renderer);
					break;
				}
				default:
					break;
				}

			}


		}
		for (int i = 0; i < maxX; i++)
		{
			for (int j = 0; j < maxY; j++)
			{
				if (map[i][j][1] == 9)
				{
					number_of_flags++;
				}
				if ((map[i][j][1] == 9) && map[i][j][0] == 10)
				{
					good_flags++;

				}
				if (map[i][j][1] == 11)
				{
					number_of_blocks++;
				}
				if ((map[i][j][1] == 9) && map[i][j][0] != 10)
				{
					wrongflags++;
				}
				if ((map[i][j][1] == 8) || (map[i][j][1] == 7) || (map[i][j][1] == 6) || (map[i][j][1] == 5) || (map[i][j][1] == 4))
				{
					RevealedPos++;
				}
				if ((map[i][j][1] == 3) || (map[i][j][1] == 2) || (map[i][j][1] == 1))
				{
					RevealedPos++;
				}
			}
		}
	}
	
	/// <summary>
	///	Functie prin care verificam daca s-a indeplinit conditia de castigare a jocului 
	/// </summary>	
bool Map::GameWon()
{
	
	if ((Aria - RevealedPos - PosHasZero) == count_bombs)
	{
		if (dimension == 2)
		{
			map[xmain - 1][maxY / 2][0] = 35;
		}
		if (dimension == 1)
		{
			map[xmain - 1][maxY / 2][0] = 35;
		}
		if (dimension == 3)
		{
			map[xmain - 1][maxY / 2][0] = 35;
		}
		return true;
	}
	else
	{
		return false;
	}
}
	/// <summary>
/// Verificam urmatoarele:
///			- Daca este 10 ( s-a atins o bomba ), jocul se incheie.
///			- Daca este 0 ( a atins o casuta in jurul careia nu se afla nicio bomba ), se descoperita toate casutele
///		"goale" din imprejur
///			- Daca nu este nici 10 nici 0, se descopera casuta.
	/// </summary>
bool Map::PressMine(int MouseX, int MouseY)
{
	
	int type = 0;
	type = map[MouseX][MouseY][0];
	if (map[MouseX][MouseY][1] != 9 && map[MouseX][MouseY][1]!=25)
	{
		switch (type)
		{
		case 10:
		{
			if (dimension == 2)
			{
				map[xmain - 1][maxY / 2][0] = 34;
			}
			else if (dimension == 1)
			{
				map[xmain - 1][maxY / 2][0] = 34;
			}
			else if (dimension == 3)
			{
				map[xmain - 1][maxY / 2][0] = 34;
			}
			map[MouseX][MouseY][0] = 12;
			
			return false;
		}
		case 0:
		{
			RevealAround(MouseX, MouseY);
			map[MouseX][MouseY][1] = 75;

			return true;
		}
		default:
		{
			map[MouseX][MouseY][1] = map[MouseX][MouseY][0];
			return true;
		}
		
		}
	}
	
}

void Map::RevealALL()
{
	for (int i = xmain; i < maxX-xmain+1; i++)
	{
		for (int j = ymain; j < maxY-ymain; j++)
		{
			if (map[i][j][1] != 9 )
			{
				map[i][j][1] = map[i][j][0];
			}
			else if (map[i][j][1] == 9 && map[i][j][0] >= -1 && map[i][j][0] <= 8) // flag pus gresit ( nu pe bomba)
			{
				map[i][j][1] = 27;
			}
		}
	}
}

	/// <summary>
	///		In momentul in care ai apasat pe o casuta, iar aceasta nu are nicio bomba imprejur, se executa urmatoarea functie,
	///	care are ca rol sa arate si casutele "goale" din imprejur.
	/// 
	///		Obs: Functie recursiva
	/// </summary>
void Map::RevealAround(int MouseX, int MouseY)
{
	map[MouseX][MouseY][0] = 14;
	for (int i = MouseX - 1; i < MouseX + 2; i++)
	{
		for (int j = MouseY - 1; j < MouseY + 2; j++)
		{
			if (map[i][j][1] != 9)
			{
				map[i][j][1] = map[i][j][0];
			}
		}
	}
	//CELE 8 IF-URI PENTRU REVEAL AROUND
	{
	if (map[MouseX - 1][MouseY][0] == 0)
	{
		RevealAround(MouseX - 1, MouseY);
	}
	if (map[MouseX + 1][MouseY][0] == 0)
	{
		RevealAround(MouseX + 1, MouseY);
	}
	if (map[MouseX][MouseY + 1][0] == 0)
	{
		RevealAround(MouseX, MouseY + 1);
	}
	if (map[MouseX][MouseY - 1][0] == 0)
	{
		RevealAround(MouseX, MouseY + 1);
	}
	if (map[MouseX + 1][MouseY + 1][0] == 0)
	{
		RevealAround(MouseX + 1, MouseY + 1);
	}
	if (map[MouseX - 1][MouseY + 1][0] == 0)
	{
		RevealAround(MouseX - 1, MouseY + 1);
	}
	if (map[MouseX + 1][MouseY - 1][0] == 0)
	{
		RevealAround(MouseX + 1, MouseY - 1);
	}
	if (map[MouseX - 1][MouseY - 1][0] == 0)
	{
		RevealAround(MouseX - 1, MouseY - 1);
	}
	}
	return;

}
	/// <summary>
	///   Primul IF:
	///			- daca numarul de steaguri este mai mic decat numele de bombe, atunci putem pune/scoate un steag.
	///	  Al doilea IF:
	///			- daca numarul de steaguri puse este egal cu numarul de bombe, atunci mai putem doar scoate steaguri. 
	/// </summary>
void Map::DoSteag(int MouseX, int MouseY)
{
	int type = map[MouseX][MouseY][1];
	if (number_of_flags < count_bombs)
	{
		switch (type)
		{
		case 9:
		{
			map[MouseX][MouseY][1] = 11;
			break;
		}
		case 11:
		{
			map[MouseX][MouseY][1] = 9;
			break;
		}
		default:
			break;
		}
		
	}
	if (number_of_flags == count_bombs)
	{
		if (type == 9)
		{
			map[MouseX][MouseY][1] = 11;
		}
		else
			return;
	}
	

}

void Map::givedata(int dificultatea, int dimensiunea)
{
	this->difficulty = dificultatea;
	this->dimension = dimensiunea;
}

	/// <summary>
	///		In functie de dimensiunea/dificultatea aleasa in timpul in care te afli in main menu,
	/// se va schimba imaginea pt a sti ce ai ales.
	/// </summary>
void Map::DrawMainMenu()
{
	dest.x = 0;
	dest.y = 0;
	dest.w = 736;
	dest.h = 704;
	{
		if (difficulty == 0 && dimension == 0)
		{
			TextureManager::Draw(dific, src, dest, renderer);
		}
		else if (difficulty == 1 && dimension == 0)
		{
			TextureManager::Draw(easy0, src, dest, renderer);
		}
		else if (difficulty == 1 && dimension == 1)
		{
			TextureManager::Draw(easysmall, src, dest, renderer);
		}
		else if (difficulty == 1 && dimension == 2)
		{
			TextureManager::Draw(easymed, src, dest, renderer);
		}
		else if (difficulty == 1 && dimension == 3)
		{
			TextureManager::Draw(easylarge, src, dest, renderer);
		}
		else if (difficulty == 2 && dimension == 0)
		{
			TextureManager::Draw(difmedium0, src, dest, renderer);
		}
		else if (difficulty == 2 && dimension == 1)
		{
			TextureManager::Draw(medsmall, src, dest, renderer);
		}
		else if (difficulty == 2 && dimension == 2)
		{
			TextureManager::Draw(medmed, src, dest, renderer);
		}
		else if (difficulty == 2 && dimension == 3)
		{
			TextureManager::Draw(medlarge, src, dest, renderer);
		}
		else if (difficulty == 3 && dimension == 0)
		{
			TextureManager::Draw(hard0, src, dest, renderer);
		}
		else if (difficulty == 3 && dimension == 1)
		{
			TextureManager::Draw(hardsmall, src, dest, renderer);
		}
		else if (difficulty == 3 && dimension == 2)
		{
			TextureManager::Draw(hardmed, src, dest, renderer);
		}
		else if (difficulty == 3 && dimension == 3)
		{
			TextureManager::Draw(hardlarge, src, dest, renderer);
		}
		else if (difficulty == 0 && dimension == 1)
		{
			TextureManager::Draw(small0, src, dest, renderer);
		}
		else if (difficulty == 0 && dimension == 2)
		{
			TextureManager::Draw(dimmedium0, src, dest, renderer);
		}
		else if (difficulty == 0 && dimension == 3)
		{
			TextureManager::Draw(large0, src, dest, renderer);
		}
	}
}
