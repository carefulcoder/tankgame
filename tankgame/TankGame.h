#include <vector>
#include <time.h>
#include <algorithm>

#include "Tank.h"
#include "Vehicle.h"
#include "TransientVehicle.h"
#include "Score.h"

#include "Canvas.h"
#include "Computer.h"
#include "Collisions.h"
#include "Player.h"


class TankGame {
public:
	TankGame();
	void run(Canvas& canvas);
	bool shouldRun();
	~TankGame();
private:
	std::vector<Tank *> tanks;
	std::vector<Vehicle *> bullets;

	Computer * computer;
	Collisions* collisions;
	Player * player;
	Score * score;

	int wave;
	void sprinkleTanks();
};