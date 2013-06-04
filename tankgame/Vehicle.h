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
	glm::mat4 getTransform() const;

	//get the position of this vehicle
	glm::vec3 getPosition() const;

	//get our current velocity
	float getVelocity() const;
	
	//add some velocity to us
	virtual void setVelocity(float amount);

	virtual void rotate(float amount);

	void setPosition(glm::vec3 pos);

	//get width of vehicle
	float getWidth() const;

	//get height of vehicle
	float getHeight() const;

	float getAngleDegrees() const;

	void setAngleDegrees(float amount);
	
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