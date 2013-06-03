
#include "Canvas.h"
#include "TextureMapper.h"
#include "RenderableTank.h"
#include "Player.h"
#include "Computer.h"
#include "Collisions.h"

#include <glm.hpp>

#include <sdl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <time.h>

//main code entry point
int main(int argc, char **argv)
{
	SDL_Init( SDL_INIT_VIDEO );
	const SDL_VideoInfo* info = SDL_GetVideoInfo(); 
	int height = info->current_h / 2; 
	int width = info->current_w / 2; 

	SDL_Surface* screen = SDL_SetVideoMode( width, height, 0, SDL_OPENGL );
	SDL_WM_SetCaption( "Tank App" , 0 ); 

	//SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);

	//init our sprite engine - the canvas for drawing and a vector to store
	Canvas * canvas = new Canvas(width, height, "tanks", 8);
	std::vector<Renderable *> sprites;

	//create the player's Tank and give it to a player controller for manipulation
	Tank * playerTank = new Tank(glm::vec3(width / 2, height / 2, 0.0f));
	Player player = Player(*playerTank);

	//now attach our player tank to a RenderableTank to render it
	sprites.push_back(new RenderableTank(0, 1, *playerTank));
	srand((int)time(NULL));

	//add AI tanks
	std::vector<Tank *> ai;
	ai.push_back(playerTank);

	const std::vector<Tank*>& aiConst = ai;

	Collisions collisions = Collisions(width, height);
	collisions.process(ai);

	for (int i = 0; i < 1; i++) {
		Tank * aiTank = new Tank(glm::vec3(rand() % width, rand() % height, 0.0f));
		sprites.push_back(new RenderableTank(0, 1, *aiTank));
		ai.push_back(aiTank);
	}

	//give AI tanks to controller
	Computer computer = Computer(ai, 0);

	SDL_Event event;
	bool gameRunning = true;

	while (gameRunning)
	{
		player.tick();
		computer.tick();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//draw our tile based world.
		float tilesX = ((float)width) / 64.0f;
		float tilesY = ((float)height) / 64.0f;
		for (float x = 0; x < tilesX; x++) {
			for (float y = 0; y < tilesY; y++) {
				canvas->draw("grass", glm::translate(glm::mat4(1.0f), glm::vec3((float)x * 64 + 32, (float)y * 64 + 32, 0.0f)));
			}
		}

		canvas->draw("a", glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0)));

		//call our renderable objects to get them to draw to our OpenGL canvas.
		for (std::vector<Renderable*>::iterator it = sprites.begin(); it != sprites.end(); ++it) {
			Renderable * renderable = *it;
			renderable->draw(*canvas);
		}
		
		//handle collisions
		collisions.process(ai);
		
		//Update Screen
		SDL_GL_SwapBuffers();
		//SDL_Delay(1000 / 120);
		
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
						player.keyDown(keyPressed);
						break;
				}
			} else if (event.type == SDL_KEYUP) {
				player.keyUp(event.key.keysym.sym);
			}
		}
	}

	SDL_Quit();
	return 0;
}
