#include <vector>
#include <time.h>

#include "Tank.h"
#include "Vehicle.h"

#include "Canvas.h"
#include "Computer.h"
#include "Collisions.h"

class TankGame {
public:
	TankGame();
	void run(Canvas& canvas);
private:
	std::vector<Tank *> tanks;
	std::vector<Vehicle *> bullets;

	Computer * computer;
	Collisions* collisions;
};