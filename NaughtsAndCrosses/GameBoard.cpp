#include "GameBoard.h"

//INITIALIZE STATIC VARIABLES
char GameBoard::BLANK = '-';
char GameBoard::CROSS = 'X';
char GameBoard::NAUGHT = 'O';

GameBoard::GameBoard(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	//here we set up the images for our textures to use on the gameboard
	blank = IMG_LoadTexture(renderer, "assets/blank.png");
	cross = IMG_LoadTexture(renderer, "assets/cross.png");
	naught = IMG_LoadTexture(renderer, "assets/naught.png");

	clearBoard();
}

GameBoard::~GameBoard()
{
	SDL_DestroyTexture(blank);
	SDL_DestroyTexture(cross);
	SDL_DestroyTexture(naught);
}

//loops through the board using a nested for loop
//changes all tiles to blank
void GameBoard::clearBoard()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			board[x][y] = BLANK;
		}
	}
}

bool GameBoard::setTile(char type, int x, int y)
{
	//if x,y is on board, try and set tile
	if (x >= 0 && x <= 2 && y >= 0 && y <= 2)
	{
		//set if this tile is blank
		if (board[x][y] == BLANK)
		{
			board[x][y] = type;
			return true;
		}

	}
	//if the tile was not set, return false
	return false;
}

void GameBoard::getTileXYBasedOnPixlXY(int pixelX, int pixelY, int& tileX, int& tileY)
{
	//if pixel is not on board
	if (pixelX < boardX || pixelX > boardX + (tileSize * 3)
		|| pixelY < boardY || pixelY > boardY + (tileSize * 3))
	{
		tileX = -1;
		tileY = -1;
		return; //exit, the move is not valid
	}

	//simplify math to ignore offset of board
	pixelX = pixelX - boardX;
	pixelY = pixelY - boardY;
	
	//divide pixel values by tilesize to get spot on the board
	tileX = tileX / tileSize;
	tileY = tileY / tileSize;
}

bool GameBoard::checkForClick(SDL_Event& event, char type)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		int tileX, tileY;
		//get x and y values based on position of mouseclick
		//push values into variables tilex, tiley
		getTileXYBasedOnPixlXY(event.button.x, event.button.y, tileX, tileY);
		//checks for valid move
		if (tileX != -1 && tileY != -1)
		{
			//is valid move
			return setTile(type, tileX, tileY);
		}
		
	}
 	return false;
}

bool GameBoard::checkForWin(char type)
{
	//check horizontals for a matching line
	for (int x = 0; x < 3; x++)
	{
		if (board[x][0] == type && board[x][1] == type && board[x][2] == type)
			return true;
	}


	//check verticals for matching lines
	for (int y = 0; y < 3; y++)
	{
		if (board[0][y] == type && board[1][y] == type && board[2][y] == type)
			return true;
	}

	//check for diagonals
	if (board[0][0] == type && board[1][1] == type && board[2][2] == type)
		return true;
	if (board[2][0] == type && board[1][1] == type && board[0][2] == type)
		return true;

	//if there is no win return false
	return false;
}

bool GameBoard::checkIfAnyPlacesFree()
{
	//loop each square on the board checking for blank type
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (board[x][y] == BLANK)
				return true;
		}
	}
	
	return false; //if there are no empty spaces
}

void GameBoard::draw()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			//draw each space on the board
			SDL_Rect drawRect;
			drawRect.x = boardX + (x * tileSize);
			drawRect.y = boardY + (y * tileSize);
			drawRect.w = tileSize;
			drawRect.h = tileSize;

			//draws naughts and crosses onto board
			if (board[x][x] == BLANK)
			{
				SDL_RenderCopy(renderer, blank, NULL, &drawRect);
			}
			if (board[x][x] == CROSS)
			{
				SDL_RenderCopy(renderer, cross, NULL, &drawRect);
			}
			if (board[x][x] == NAUGHT)
			{
				SDL_RenderCopy(renderer, naught, NULL, &drawRect);
			}
		}
	}
}

int GameBoard::evaluate()
{
	return 0;
}

int GameBoard::minimax(int depth, bool isMax)
{
	return 0;
}

int GameBoard::minimax(int depth, bool isMax, int alpha, int beta)
{
	return 0;
}

Move GameBoard::findBestMove(char type)
{
	return Move();
}
