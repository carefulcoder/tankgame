#include "Collisions.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Collisions::Collisions(int width, int height) : worldWidth(width), worldHeight(height) {
	//uh, I have no state atm
}

//process collisions between vehicles, imparting damage to them based on the force of colliding
void Collisions::process(const std::vector<Tank*>& vehicles) {


	//loop through all our vehicles and place them into a grid cell depending on their location
	//and so find any vehicles potentially close enough to be colliding if there are any duplicates.
	for (std::vector<Tank*>::const_iterator it = vehicles.begin(); it != vehicles.end(); ++it) {
		
		Vehicle * vehicle = *it;
		glm::vec3 vehiclePos = vehicle->getPosition();

		for (std::vector<Tank*>::const_iterator it2 = vehicles.begin(); it2 != vehicles.end(); ++it2) {

			if (*it2 == vehicle) {
				continue;
			}

			Vehicle * other = *it2;
			glm::vec3 otherPos = other->getPosition();

			//do a quick bounding sphere test first to see if there is any chance of these two vehicles colliding.
			if (glm::distance(vehiclePos, otherPos) < std::max(other->getWidth(), other->getHeight()) + std::max(vehicle->getWidth(), vehicle->getHeight())) {

				//temp swap until I get this to work
				Vehicle * temp = other;
				other = vehicle;
				vehicle = temp;

				float vehHeight = vehicle->getHeight() / 2;
				float vehWidth = vehicle->getWidth() / 2;

				float otherWidth = vehicle->getWidth() / 2;
				float otherHeight = vehicle->getHeight() / 2;

				//find out where the corners are
				glm::vec4 vehicleCorners[] = { 
					vehicle->getTransform() * glm::vec4( - vehWidth,  - vehHeight, 0.0f, 1.0f),
					vehicle->getTransform() * glm::vec4( + vehWidth,  - vehHeight, 0.0f, 1.0f),
					vehicle->getTransform() * glm::vec4( - vehWidth,  + vehHeight, 0.0f, 1.0f),
					vehicle->getTransform() * glm::vec4( + vehWidth,  + vehHeight, 0.0f, 1.0f)
				};

				//find out what the angle of the other tank is.
				float angleOfOther = other->getAngleDegrees();

				//iterate through vehicle corners
				for (int i = 0; i < 4; i++) {

					//find the vector between our vertex and the centre of the other tank
					glm::vec4 difference = vehicleCorners[i] - glm::vec4(other->getPosition(), 1.0f);

					//rotate that vector found, subtracting the angle of the other tank, to map to the non-rotated bounding box of the other tank.
					glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), -angleOfOther, glm::vec3(0.0f, 0.0f, 1.0f)) * difference;

					if (rotated.x > -otherWidth && rotated.x < otherWidth && rotated.y > -otherHeight && rotated.y <  otherHeight) {
						//other->addVelocity(other->getVelocity() * -1); collision response goes here!
						break;				
					}
				}			
			}
		}
	}
}