#include <vector>
#include "Tank.h"

class Computer {
public:
	Computer(const Tank& player);
	void processMove(Tank& tank);
private:
	const Tank& player;
};