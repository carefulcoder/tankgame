#include <vector>
#include "Tank.h"
#include "Canvas.h"

class Collisions {
public:
	Collisions(const std::vector<Vehicle *>& vehicles);
	const Vehicle * getObjectCollidingWith(const Vehicle& test, Canvas& cvs);
private:
	const std::vector<Vehicle *>& vehicles;
};