#include "Tank.h"
#include <SDL_keyboard.h>


class Player {
public:
	Player(Tank& tank);
	void keyDown(SDLKey key);
	void keyUp(SDLKey key);
	void tick();
private:
	Tank& tank;
	float rotAmount;
	float rotTAmount;
};