#ifndef TANK
#define TANK

#include "Vehicle.h"

class Tank : public Vehicle {
public:
	Tank(glm::vec3 pos);
	virtual void rotate(float amt);
	virtual void setVelocity(float amt);
	virtual void tick();
	Vehicle& getTurret();

	void requestFire();
	bool serviceFireRequest();

private:
	float turretRotation;
	Vehicle& turret;
	int fireDelay;
};

#endif