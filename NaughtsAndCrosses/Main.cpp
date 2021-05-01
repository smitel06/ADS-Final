//ADS FINAL ASSESSMENT ELIAH SMITH
//TIC TAC TOE GAME USING MINIMAX AI ALGORITHM FOR COMPUTER CONTROLLED PLAYED
//REPO:
//

#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

int main(int argc, char** argv)
{
	//Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Error: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}
	//create window for game screen
	SDL_Window* window = SDL_CreateWindow("gameScreen", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	//window error
	if (window == NULL)
	{
		cout << "Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}
	//renderer to draw the game to game screen
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//renderer error so destroy the window and quit
	if (renderer == NULL)
	{
		cout << "Error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		system("pause");
		return 1;
	}

	//what to render
	bool quit = false;
	//game loop while the player has not quit
	while (!quit)
	{
		//get player inputs
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//user presses close button
			if (e.type == SDL_QUIT)
				quit = true;
			//check for key presses
			if (e.type == SDL_KEYDOWN)
			{
				//if key down is escape key quit the game
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = true;
				}
			}
		}
		//uses rgba to render background colour to screen
		//i chose an almost blackcolor
		SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
		SDL_RenderClear(renderer);

		//swaps the buffers
		SDL_RenderPresent(renderer);
	}



	return 0;
}