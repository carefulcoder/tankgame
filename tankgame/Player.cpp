#include "Player.h"

Player::Player(Tank& tnk) : tank(tnk), rotAmount(0.0f), rotTAmount(0.0f) {}

void Player::keyDown(SDLKey k) {
	if (k == SDLK_UP) {
		tank.setVelocity(5.0f);
	} else if (k == SDLK_DOWN) {
		tank.setVelocity(0.0f);
	} else if (k == SDLK_RIGHT) {
		rotAmount = 3.0f;
	} else if (k == SDLK_LEFT) {
		rotAmount = -3.0f;
	} else if (k == SDLK_a) {
		rotTAmount = - 5.0f;
	} else if (k == SDLK_d) {
		rotTAmount = 5.0f;
	}
}

void Player::keyUp(SDLKey k) {
	if (k == SDLK_RIGHT || k == SDLK_LEFT) {
		rotAmount = 0;
	} else if (k == SDLK_UP) {
		tank.setVelocity(0.0f);
	} else if (k == SDLK_DOWN) {
		tank.setVelocity(5.0f);
	} else if (k == SDLK_a || k == SDLK_d) {
		rotTAmount = 0;
	}
}

void Player::tick() {
	tank.rotate(rotAmount);
	tank.getTurret().rotate(rotTAmount);
}