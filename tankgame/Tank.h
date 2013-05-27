#ifndef TANK
#define TANK

#include "Vehicle.h"

class Tank : public Vehicle {
public:
	Tank(glm::vec3 pos);
	void rotateTurret(float amt);
	void setTurretRotation(float amt);
	virtual void rotate(float amt);
	float getTurretRotation();
private:
	float turretRotation;
};

#endif