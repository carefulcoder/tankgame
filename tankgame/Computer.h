#include <vector>
#include "Tank.h"

class Computer {
public:
	Computer(std::vector<Tank *>& tnks, int ply);
	void tick();
private:
	std::vector<Tank *> &tanks;
	int player;
};