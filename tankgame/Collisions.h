#include <vector>
#include "Tank.h"
#include "Canvas.h"

class Collisions {
public:
	Collisions(int width, int height);
	void process(const std::vector<Tank*>& vehicles);
private:
	int worldWidth;
	int worldHeight;
};