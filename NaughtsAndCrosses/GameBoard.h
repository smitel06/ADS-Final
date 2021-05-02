#pragma once
#include <SDL.H>
#include <SDL_image.h> //allows the ability to use more pic file types ie. png
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "res_path.h"

using namespace std;

struct Move
{
	int row, col;
};

class GameBoard
{
public:
	static char BLANK;
	static char CROSS;
	static char NAUGHT;

	//access the renderer and create textures for game pieces
	SDL_Renderer* renderer;
	SDL_Texture* blank, * cross, * naught;


	//size of board
	char board[3][3];
	//height and width
	int boardX = 500, boardY = 100;
	//size of tiles
	int tileSize = 50;

	//The pieces for each player
	char player = CROSS, opponent = NAUGHT;

	int minimaxCount = 0;

	//gameboard functions
	GameBoard(SDL_Renderer* renderer);
	~GameBoard();
	void clearBoard();
	bool setTile(char type, int x, int y);
	void getTileXYBasedOnPixlXY(int pixelX, int pixelY, int& tileX, int& tileY); //finds clicked tile
	bool checkForClick(SDL_Event& event, char type);
	bool checkForWin(char type);
	bool checkIfAnyPlacesFree();
	//DRAW EVERYTHING TO SCREEN
	void draw();

	//MINIMAX FUNCTIONS
	int evaluate();
	//recursive function
	int minimax(int depth, bool isMax);
	//minimax using alpha beta pruning
	int minimax(int depth, bool isMax, int alpha, int beta);

	Move findBestMove(char type);



};

