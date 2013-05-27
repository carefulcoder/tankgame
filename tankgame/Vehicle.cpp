#include "Vehicle.h"
#include <gtx/quaternion.hpp>

Vehicle::Vehicle(glm::vec3 pos, float width, float height) : width(width), height(height), rotation(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f))) {
	this->position = pos;
	this->velocity = 0.0f;
}

void Vehicle::addVelocity(float amount) {
	this->velocity += amount;
}

void Vehicle::rotate(float amount) {
	float newAngle = glm::degrees(2 * acos(this->rotation.w)) + amount;
	if (newAngle > 359) { //hacky, surely this can be changed
		newAngle -=359;
	}
	if (newAngle < 0) {
		newAngle += 359;
	}
	this->rotation = glm::angleAxis(newAngle, glm::vec3(0.0f, 0.0f, 1.0f));
}

float Vehicle::getVelocity() {
	return this->velocity;
}

glm::mat4 Vehicle::getTransform() {
	return glm::translate(glm::mat4(1.0f), this->position) * glm::toMat4(this->rotation);
}
 
void Vehicle::tick() {
	glm::mat4 newLocation = glm::translate(this->getTransform(), glm::vec3(this->velocity, 0.0f, 0.0f));
	this->position = glm::vec3(newLocation[3][0], newLocation[3][1], newLocation[3][2]);
}

glm::vec3 Vehicle::getPosition() {
	return this->position;
}

float Vehicle::getWidth() {
	return width;
}

float Vehicle::getHeight() {
	return height;
}

float Vehicle::getAngleDegrees() {
	return glm::degrees(2 * acos(this->rotation.w));
}