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

//destructor
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

//function sets tile to the gameboard
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
	tileX = pixelX / tileSize;
	tileY = pixelY / tileSize;
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
{	for (int x = 0; x < 3; x++)
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
			if (board[x][y] == BLANK)
			{
				SDL_RenderCopy(renderer, blank, NULL, &drawRect);
			}
			if (board[x][y] == CROSS)
			{
				SDL_RenderCopy(renderer, cross, NULL, &drawRect);
			}
			if (board[x][y] == NAUGHT)
			{
				SDL_RenderCopy(renderer, naught, NULL, &drawRect);
			}
		}
	}
}

//player is maximiser (+10 points for winning)
//opponent is minimiser(-10 points for winning)
//0 for no wins or draw
int GameBoard::evaluate()
{
	if (checkForWin(player))
		return 10;
	if (checkForWin(opponent))
		return -10;

	return 0;//no winners
}

//minimax is a recursive function that explores 
//all posible game playouts from current board
int GameBoard::minimax(int depth, bool isMax)
{
	minimaxCount++;
	int score = evaluate();

	//if maximiser has won the game, return his/her evaluate score
	if (score == 10)
		return score;
	//if minimiser has won, do the same
	if (score == -10)
		return score;
	//if no winner and no movesa return 0
	if (checkIfAnyPlacesFree() == false)
		return 0;

	//If this is maximisers move
	if (isMax)
	{
		int best = -1000;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				//check if cell is empty
				if (board[x][y] == BLANK)
				{
					//make the move
					board[x][y] = player;

					//call minimax
					best = max(best, minimax(depth + 1, !isMax));

					//undo move this is just checking
					board[x][y] = BLANK;

				}
			}
		}
		return best;
	}
	else //minimisers turn
	{
		int best = 1000;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				//check if cell is empty
				if (board[x][y] == BLANK)
				{
					//make the move
					board[x][y] = opponent;

					//call minimax
					best = min(best, minimax(depth + 1, !isMax));

					//undo move this is just checking
					board[x][y] = BLANK;
				}
			}
		}
		return best;
	}
}

int GameBoard::minimax(int depth, bool isMax, int alpha, int beta)
{
	minimaxCount++;
	int score = evaluate();

	//if maximiser has won the game, return his/her evaluate score
	if (score == 10)
		return score;
	//if minimiser has won, do the same
	if (score == -10)
		return score;
	//if no winner and no movesa return 0
	if (checkIfAnyPlacesFree() == false)
		return 0;

	bool breakLoops = false;

	//If this is maximisers move
	if (isMax)
	{
		int best = -1000;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				//check if cell is empty
				if (board[x][y] == BLANK)
				{
					//make the move
					board[x][y] = player;

					//call minimax
					best = max(best, minimax(depth + 1, !isMax, alpha, beta));

					//undo move this is just checking
					board[x][y] == BLANK;

					alpha = max(alpha, best);
					if (beta <= alpha)
						breakLoops = true;

					if (breakLoops)
						break;
				}
				if (breakLoops)
					break;
			}
		}
		return best;
	}
	else //minimisers turn
	{
		int best = 1000;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				//check if cell is empty
				if (board[x][y] == BLANK)
				{
					//make the move
					board[x][y] = opponent;

					//call minimax
					best = min(best, minimax(depth + 1, !isMax, alpha, beta));

					//undo move this is just checking
					board[x][y] == BLANK;

					beta = min(beta, best);
					if (beta <= alpha)
						breakLoops = true;

					if (breakLoops)
						break;
				}
				if (breakLoops)
					break;
			}
		}
		return best;
	}
}

Move GameBoard::findBestMove(char type)
{
	minimaxCount = 0;

	bool isMaximiser = true;//if type is equal to player
	if (type == opponent)
		isMaximiser = false;
	int bestVal = -1000;
	if (!isMaximiser)
		bestVal = 1000;

	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			//check if cell is empty
			if (board[x][y] == BLANK)
			{
				//make move
				board[x][y] = type;

				int moveVal = minimax(0, !isMaximiser);

				board[x][y] = BLANK; //undo the move

				//MAXIMISER - is this move better then previously computed ones
				if (isMaximiser && moveVal > bestVal)
				{
					bestMove.row = x;
					bestMove.col = y;
					bestVal = moveVal;
				}
				//MINIMISER
				if (!isMaximiser && moveVal < bestVal)
				{
					bestMove.row = x;
					bestMove.col = y;
					bestVal = moveVal;
				}


			}
		}
	}

	cout << "The value of the best move is " << bestVal << endl;
	cout << "Number of minimaxs run " << minimaxCount << endl;
	
	return bestMove;
}
