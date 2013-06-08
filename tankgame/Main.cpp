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
	int height = info->current_h; 
	int width = info->current_w; 

	SDL_Surface* screen = SDL_SetVideoMode( width, height, 0, SDL_OPENGL | SDL_FULLSCREEN );
	SDL_WM_SetCaption( "Tank App" , 0 ); 
	SDL_ShowCursor(0);

	//init our sprite engine - the canvas for drawing and a vector to store
	Canvas * canvas = new Canvas(width, height, "tanks", 8);
	TankGame game = TankGame();
	bool gameRunning = true;

	glm::mat4 grass = glm::scale(glm::mat4(1.0f), glm::vec3(width / 32.0f, height / 32.0f, 1.0f));

	Uint32 dtime = 0;
	Uint32 delay = 1000.0f / 60;

	while (game.shouldRun())
	{
		Uint32 time = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//draw some grass
		canvas->draw("grass", grass, glm::vec2(width / 32.0f, height / 32.0f));

		//handle game logic
		game.run(*canvas);

		//Update Screen
		SDL_GL_SwapBuffers();

		//very ropey timing code
		Uint32 timeNow = SDL_GetTicks();
		if (timeNow - time < delay) {
			dtime = delay - (timeNow - time);
			SDL_Delay((Uint32)dtime);
		}
	}

	//clean up
	delete canvas;
	SDL_Quit();
	return 0;
}
