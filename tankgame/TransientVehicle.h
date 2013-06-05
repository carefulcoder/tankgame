#include "Vehicle.h"

class TransientVehicle : public Vehicle {

public:
	//constructor
	TransientVehicle(glm::vec3 pos, float width, float height);
	virtual void tick();
};