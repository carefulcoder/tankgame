#include "Tank.h"

//constructor - initialise with vehicle constructor & 0 degrees rotation
Tank::Tank(glm::vec3 pos) : Vehicle(pos, 64.0f, 39.0f), turretRotation(0.0f) {};

//rotate our turret by the given amount
void Tank::rotateTurret(float amt) {
	this->turretRotation += amt;
}
 
void Tank::setTurretRotation(float amt) {
	this->turretRotation = amt;
}

//get the amount the turret is rotated
float Tank::getTurretRotation() {
	return this->turretRotation;
}

void Tank::rotate(float amt) {
	Vehicle::rotate(amt);
}