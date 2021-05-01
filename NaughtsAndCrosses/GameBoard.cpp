#include "GameBoard.h"

GameBoard::GameBoard(SDL_Renderer* renderer)
{
}

GameBoard::~GameBoard()
{
}

void GameBoard::clearBoard()
{
}

bool GameBoard::setTile(char type, int x, int y)
{
	return false;
}

void GameBoard::getTileXYBasedOnPixlXY(int pixel, , int, int& tileX)
{
}

booll GameBoard::checkForClick(SDL_Event& event, char type)
{
	return booll();
}

bool GameBoard::checkForWin(char type)
{
	return false;
}

bool GameBoard::checkIfAnyPlacesFree()
{
	return false;
}

void GameBoard::draw()
{
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
