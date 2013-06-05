#include "Tank.h"

//constructor - initialise with vehicle constructor & 0 degrees rotation
Tank::Tank(glm::vec3 pos) : Vehicle(pos, 64.0f, 40.0f), turretRotation(0.0f), turret(*new Vehicle(pos, 64.0f, 30.0f)), fireDelay(0) {
};


//get the amount the turret is rotated
Vehicle& Tank::getTurret() {
	return this->turret;
}

void Tank::setVelocity(float amt) {
	this->turret.setVelocity(amt);
	Vehicle::setVelocity(amt);
}

void Tank::rotate(float amt) {
	this->turret.rotate(amt);
	Vehicle::rotate(amt);
}

void Tank::tick() {
	Vehicle::tick();
	this->turret.setPosition(this->getPosition());
	if (fireDelay > 0) {
		fireDelay--;
	}
}

void Tank::requestFire() {
	if (this->fireDelay == 0) {
		fireDelay = -1;
	}
}

bool Tank::serviceFireRequest() {
	bool should = fireDelay == -1;
	if (should) {
		fireDelay = 100;
	}
	return should;
}