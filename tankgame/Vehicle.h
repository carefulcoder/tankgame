//header guard
#ifndef VEHICLE
#define VEHICLE

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

class Vehicle {

public:

	//constructor
	Vehicle(glm::vec3 pos, float width, float height);
	
	//get our transform matrix
	glm::mat4 getTransform();

	//get the position of this vehicle
	glm::vec3 getPosition();

	//get our current velocity
	float getVelocity();
	
	//add some velocity to us
	void setVelocity(float amount);

	virtual void rotate(float amount);

	//get width of vehicle
	float getWidth();

	//get height of vehicle
	float getHeight();

	float getAngleDegrees();
	
	//tick
	virtual void tick();

private:
	glm::vec3 position;
	glm::quat rotation;
	float velocity;
	float height;
	float width;
};

//end header
#endif 