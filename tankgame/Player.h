#include "Tank.h"
#include <SDL_keyboard.h>
#include <SDL_events.h>

class Player {
public:
	Player(Tank& tank);
	bool wantsToQuit();
	void pollEvents();
private:
	Tank& tank;
	float rotAmount;
	float rotTAmount;
	bool quitRequest;
	void keyUp(SDLKey k);
	void keyDown(SDLKey k);
};