#include "TransientVehicle.h"

TransientVehicle::TransientVehicle(glm::vec3 pos, float width, float height) : Vehicle(pos, width, height) {}

void TransientVehicle::tick() {
	Vehicle::tick();
	if (this->getHealth() > 0) {
		this->setHealth(this->getHealth() - 1.0f);
	}
}