#include "Vehicle.h"
#include <gtx/quaternion.hpp>

Vehicle::Vehicle(glm::vec3 pos, float width, float height) : width(width), height(height), rotation(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f))), health(100.0f) {
	this->position = pos;
	this->velocity = 0.0f;
}

void Vehicle::setVelocity(float amount) {
	this->velocity = amount;
}

void Vehicle::rotate(float amount) {
	this->setAngleDegrees(glm::degrees(2 * acos(this->rotation.w)) + amount);
}

void Vehicle::setAngleDegrees(float amount) {
	if (amount > 359) { //hacky, surely this can be changed
		amount -=359;
	}
	if (amount < 0) {
		amount += 359;
	}
	this->rotation = glm::angleAxis(amount, glm::vec3(0.0f, 0.0f, 1.0f));
}

float Vehicle::getVelocity() const {
	return this->velocity;
}

glm::mat4 Vehicle::getTransform() const {
	return glm::translate(glm::mat4(1.0f), this->position) * glm::toMat4(this->rotation);
}
 
void Vehicle::tick() {
	glm::mat4 newLocation = glm::translate(this->getTransform(), glm::vec3(this->velocity, 0.0f, 0.0f));
	this->position = glm::vec3(newLocation[3][0], newLocation[3][1], newLocation[3][2]);
}

glm::vec3 Vehicle::getPosition() const {
	return this->position;
}

float Vehicle::getWidth() const {
	return width;
}

float Vehicle::getHeight() const {
	return height;
}

float Vehicle::getAngleDegrees() const {
	return glm::degrees(2 * acos(this->rotation.w));
}

void Vehicle::setPosition(glm::vec3 pos) {
	this->position = pos;
}

void Vehicle::setHealth(float amt) {
	this->health = amt;
}

float Vehicle::getHealth() const {
	return health;
}