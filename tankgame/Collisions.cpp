#include "Collisions.h"

Collisions::Collisions(const std::vector<Vehicle *>& vehs) : vehicles(vehs) {
	//uh, I have no state atm
}

//process collisions between vehicles, imparting damage to them based on the force of colliding
const Vehicle * Collisions::getObjectCollidingWith(const Vehicle& test, Canvas& canvas) {

	const Vehicle * vehicle = &test;
	glm::vec3 vehiclePos = vehicle->getPosition();

	for (std::vector<Vehicle *>::const_iterator o = vehicles.begin(); o != vehicles.end(); ++o) {

		const Vehicle * other = *o;
		glm::vec3 otherPos = other->getPosition();

		//do a quick bounding sphere test first to see if there is any chance of these two vehicles colliding.
		if (glm::distance(vehiclePos, otherPos) < std::max(other->getWidth(), other->getHeight()) + std::max(vehicle->getWidth(), vehicle->getHeight())) {

			float vehHeight = vehicle->getHeight() / 2;
			float vehWidth = vehicle->getWidth() / 2;

			float otherWidth = other->getWidth() / 2;
			float otherHeight = other->getHeight() / 2;

			if (vehHeight > otherHeight && vehWidth > otherWidth) {
				std::swap(other, vehicle);
				std::swap(vehHeight, otherHeight);
				std::swap(vehWidth, otherWidth);
			}

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
				glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), angleOfOther, glm::vec3(0.0f, 0.0f, 1.0f)) * difference;


				if (rotated.x > -otherWidth && rotated.x < otherWidth && rotated.y > -otherHeight && rotated.y <  otherHeight) {
					return other;		
				}
			}			
		}
	}

	//if we got here there were none
	return NULL;
}