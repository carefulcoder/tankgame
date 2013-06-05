#include <vector>
#include <time.h>

#include "Tank.h"
#include "Vehicle.h"
#include "TransientVehicle.h"

#include "Canvas.h"
#include "Computer.h"
#include "Collisions.h"
#include "Player.h"

class TankGame {
public:
	TankGame();
	void run(Canvas& canvas);
	bool shouldRun();
private:
	std::vector<Tank *> tanks;
	std::vector<Vehicle *> bullets;

	Computer * computer;
	Collisions* collisions;
	Player * player;
};