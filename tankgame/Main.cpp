#include "Canvas.h"
#include "TankGame.h"

#include <glm.hpp>
#include <sdl.h>

#include <iostream>

//main code entry point
int main(int argc, char **argv)
{
	SDL_Init( SDL_INIT_VIDEO );
	const SDL_VideoInfo* info = SDL_GetVideoInfo(); 
	int height = info->current_h / 2; 
	int width = info->current_w / 2; 

	SDL_Surface* screen = SDL_SetVideoMode( width, height, 0, SDL_OPENGL );
	SDL_WM_SetCaption( "Tank App" , 0 ); 

	//init our sprite engine - the canvas for drawing and a vector to store
	Canvas * canvas = new Canvas(width, height, "tanks", 8);
	TankGame game = TankGame();

	SDL_Event event;
	bool gameRunning = true;

	while (gameRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw our tile based world.
		float tilesX = ((float)width) / 64.0f;
		float tilesY = ((float)height) / 64.0f;
		for (float x = 0; x < tilesX; x++) {
			for (float y = 0; y < tilesY; y++) {
				canvas->draw("grass", glm::translate(glm::mat4(1.0f), glm::vec3((float)x * 64 + 32, (float)y * 64 + 32, 0.0f)));
			}
		}

		//handle game logic
		game.run(*canvas);

		//Update Screen
		SDL_GL_SwapBuffers();
		
		//handle event polling
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			} else if (event.type == SDL_KEYDOWN) {
				SDLKey keyPressed = event.key.keysym.sym;
				switch (keyPressed) {
					case SDLK_ESCAPE:
						gameRunning = false;
						break;
					default:
						//player.keyDown(keyPressed);
						break;
				}
			} else if (event.type == SDL_KEYUP) {
				//player.keyUp(event.key.keysym.sym);
			}
		}
	}

	delete canvas;
	SDL_Quit();
	return 0;
}
