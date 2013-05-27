#include "Computer.h"
#include "Tank.h"
#include <vector>
#include <iostream>

//Constructor - don't need to do anything, just initialise variables.
Computer::Computer(std::vector<Tank *> &tnks, int ply) : tanks(tnks), player(ply) {}

//called each frame
void Computer::tick() {

	//figure out where the player is
	glm::vec3 playerPos = tanks[player]->getPosition();
	for (std::vector<Tank *>::iterator it = tanks.begin(); it != tanks.end(); ++it) {

		Tank * tank = *it;
		if (tank != tanks[player]) {
			glm::vec3 myPos = tank->getPosition();
			float oldAngle = tank->getTurretRotation();
			float dx = myPos.x - playerPos.x;
			float dy = myPos.y - playerPos.y;

			//TOA, then get result in degrees.
			float angle = glm::degrees(90.0f - atan(dx / dy));

			//sort out angle issues
			if (dx > 0 && dy > 0) {
				angle += 180;
			} else if (dx < 0 && dy > 0) {
				angle -= 180;
			}

			tank->setTurretRotation(angle);
		}	
	}
}