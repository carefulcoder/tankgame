#include "TankGame.h"


bool deletePtrIfDead(Vehicle * v) {
	if (v->getHealth() <= 0) {
		delete v;
		return true;
	}
	return false;
}

TankGame::TankGame(int width, int height) : tanks(std::vector<Tank *>(0)), bullets(std::vector<Vehicle *>(0)), computer(NULL), collisions(NULL), wave(1), width(width), height(height) {
	srand((int)time(NULL));
	this->sprinkleTanks(); //place a player
	computer = new Computer(*this->tanks[0]);
	collisions = new Collisions(this->bullets);
	player = new Player(*this->tanks[0]);
	score = new Score();
	music = new Music();
	wave = 0;
}

/**
 * The core application logic of our tank game
 * We loop through tanks, adding bullets and removing casualties while applying AI and collisions.
 * We also loop through the bullets to draw 'em and move them rapidly about.
 */
void TankGame::run(Canvas& canvas) {

	if (tanks.size() == 1) {
		this->wave++;
		this->sprinkleTanks();
	}

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

		//don't bother with collisions if we're dead
		if (tank.getHealth() > 0.0f) {

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

			if (bullet) { //dying!
				tank.setHealth(0.0f);

				//add score if AI, reset if player
				if (it != tanks.begin()) {
					score->addScore();
				} else {
					score->resetMultiplier();
				}

			} else  { //not dying
				canvas.draw("tank", tank.getTransform());
				canvas.draw("turret", tank.getTurret().getTransform());
			}		
		} else if (it == tanks.begin()) {
			canvas.text("press r to respawn", glm::vec2(20.0f, 50.0f));
		}
	}

	//now just draw our bullets
	for (std::vector<Vehicle *>::iterator bullet = bullets.begin(); bullet != bullets.end(); ++bullet) {
		(*bullet)->tick();
		canvas.draw("bullet", (*bullet)->getTransform());
	}

	//show the wave #
	std::ostringstream ss;
	ss << wave << " score " << score->getScore() << " x" << score->getMultiplier();

	canvas.text("wave " + ss.str(), glm::vec2(20.0f, 20.0f));

	//now clean up dead bullets and tanks with the erase / remove idiom
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), deletePtrIfDead), bullets.end()); 
	tanks.erase(std::remove_if(tanks.begin()+1, tanks.end(), deletePtrIfDead), tanks.end());
}

/*
 * Should the game continue running?
 */
bool TankGame::shouldRun() {
	return !player->wantsToQuit();
}

void TankGame::sprinkleTanks() {
	for (int i = 0; i <  wave; i++) {
		this->tanks.push_back(new Tank(glm::vec3(rand() % width, rand() % height, 0.0f))); //todo fix res hard coding
	}
}

TankGame::~TankGame() {
	delete score;
	delete collisions;
	delete computer;
	delete player;
}