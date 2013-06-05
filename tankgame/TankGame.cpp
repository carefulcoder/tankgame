#include "TankGame.h"
#include <algorithm>

bool dead(Vehicle * v) {
	return v->getHealth() <= 0;
}

TankGame::TankGame() : tanks(std::vector<Tank *>(0)), bullets(std::vector<Vehicle *>(0)), computer(NULL), collisions(NULL) {
	srand((int)time(NULL));
	for (int i = 0; i < 8; i++) {
		this->tanks.push_back(new Tank(glm::vec3(rand() % 1280, rand() % 720, 0.0f))); //todo fix res hard coding
	}	

	computer = new Computer(*this->tanks[0]);
	collisions = new Collisions(this->bullets);
	player = new Player(*this->tanks[0]);
}

/**
 * The core application logic of our tank game
 * We loop through tanks, adding bullets and removing casualties while applying AI and collisions.
 * We also loop through the bullets to draw 'em and move them rapidly about.
 */
void TankGame::run(Canvas& canvas) {

	//iterate through all the tanks, handling all application logic related to them
	for (std::vector<Tank *>::iterator it = tanks.begin(); it != tanks.end(); ++it) {
		
		//dereference iterator
		Tank& tank = **it;
		tank.tick();

		//the first tank is the human
		if (it == tanks.begin()) {
			player->pollEvents();
		} else {
			computer->processMove(tank);
		}

		//firing of bullet
		if (tank.serviceFireRequest()) {
			glm::vec4 pos =  glm::translate(tank.getTurret().getTransform(), glm::vec3((tank.getWidth() / 2) + 10.0f, 0.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			Vehicle * bullet = new TransientVehicle(glm::vec3(pos.x, pos.y, pos.z), 8, 6);
			bullet->setAngleDegrees(tank.getTurret().getAngleDegrees());
			bullet->setVelocity(10.0f);
			bullets.push_back(bullet);
		}

		//find out if a bullet in the game world has hit our tank
		const Vehicle * bullet = collisions->getObjectCollidingWith(tank, canvas);

		//dying - if we're AI just remove
		if (bullet && it != tanks.begin()) {

			it = tanks.erase(it);
			//ssbullet->setHealth(0.0f);
			if (it == tanks.end()) {
				break;
			}

		//dying - it was the player, so do more
		} else if (bullet && it == tanks.begin()) {
			canvas.text("hit r to respawn", glm::vec2(20.0f, 50.0f));
		//not dying
		} else {
			canvas.draw("tank", tank.getTransform());
			canvas.draw("turret", tank.getTurret().getTransform());
		}
	}

	//now just draw our bullets
	for (std::vector<Vehicle *>::iterator bullet = bullets.begin(); bullet != bullets.end(); ++bullet) {
		(*bullet)->tick();
		canvas.draw("bullet", (*bullet)->getTransform());
	}

	//I am narcissitichch
	//canvas.text("javaguys tank game opengl", glm::vec2(20.0f, 20.0f));

	//now clean up dead bullets and tanks
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), dead), bullets.end()); 

}

/*
 * Should the game continue running?
 */
bool TankGame::shouldRun() {
	return !player->wantsToQuit();
}