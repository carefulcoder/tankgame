#include "TankGame.h"

TankGame::TankGame() : tanks(std::vector<Tank *>(0)), bullets(std::vector<Vehicle *>(0)), computer(NULL), collisions(NULL) {
	srand((int)time(NULL));
	for (int i = 0; i < 2; i++) {
		this->tanks.push_back(new Tank(glm::vec3(rand() % 1280, rand() % 720, 0.0f))); //todo fix res hard coding
	}

	computer = new Computer(*this->tanks[0]);
	collisions = new Collisions(this->bullets);
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
		
		} else {
			computer->processMove(tank);
		}

		//firing of bullet
		if (tank.serviceFireRequest()) {
			glm::vec4 pos =  glm::translate(tank.getTurret().getTransform(), glm::vec3((tank.getWidth() / 2) + 4.0f, 0.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			Vehicle * bullet = new Vehicle(glm::vec3(pos.x, pos.y, pos.z), 8, 6);
			bullet->setAngleDegrees(tank.getAngleDegrees());
			bullet->setVelocity(0.5f);
			bullets.push_back(bullet);
		}

		//find out if a bullet in the game world has hit our tank
		const Vehicle * bullet = collisions->getObjectCollidingWith(tank, canvas);

		//dying - if we're AI just remove
		if (bullet && it != tanks.begin()) {

			//it = tanks.erase(it);
			if (it == tanks.end()) {
				break;
			}

		//dying - it was the player, so do more
		} else if (bullet && it == tanks.begin()) {
			canvas.text("oh dear you are rather dead", glm::vec2(20.0f, 50.0f));
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
	canvas.text("javaguys tank game", glm::vec2(20.0f, 20.0f));
}