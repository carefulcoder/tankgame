#include "Player.h"

Player::Player(Tank& tnk) : tank(tnk), rotAmount(0.0f), rotTAmount(0.0f), quitRequest(false) {}

/*
 * Poll keyboard / other input events from some place or other
 * In this case we're using SDL to get the events
 */
void Player::pollEvents() 
{
	SDL_Event evt;
	while  (SDL_PollEvent(&evt)) {
		if (evt.type == SDL_QUIT) {
			quitRequest = true;
		}
		if (evt.type == SDL_KEYDOWN) {
			SDLKey keyPressed = evt.key.keysym.sym;
			switch (keyPressed) {
				case SDLK_ESCAPE:
					quitRequest = true;
					break;
				default:
					this->keyDown(keyPressed);
					break;
			}
		}
		if (evt.type == SDL_KEYUP) {
			this->keyUp(evt.key.keysym.sym);
		}
	}
	tank.rotate(rotAmount);
	tank.getTurret().rotate(rotTAmount);
}

/*
 * Handle key down events- increase player velocity. 
 */
void Player::keyDown(SDLKey k) {
	if (k == SDLK_UP) {
		tank.setVelocity(5.0f);
	} else if (k == SDLK_DOWN) {
		tank.setVelocity(-5.0f);
	} else if (k == SDLK_RIGHT) {
		rotAmount = 3.0f;
	} else if (k == SDLK_LEFT) {
		rotAmount = -3.0f;
	} else if (k == SDLK_a) {
		rotTAmount = - 5.0f;
	} else if (k == SDLK_d) {
		rotTAmount = 5.0f;
	} else if (k == SDLK_SPACE) {
		tank.requestFire();
	}
}

/*
 * Handle key up events - decrease velocity
 * and/or tank & turret rotation
 */
void Player::keyUp(SDLKey k) {
	if (k == SDLK_RIGHT || k == SDLK_LEFT) {
		rotAmount = 0;
	} else if (k == SDLK_UP) {
		tank.setVelocity(0.0f);
	} else if (k == SDLK_DOWN) {
		tank.setVelocity(0.0f);
	} else if (k == SDLK_a || k == SDLK_d) {
		rotTAmount = 0;
	}
}

/*
 * Have we had enough?
 */
bool Player::wantsToQuit() {
	return quitRequest;
}