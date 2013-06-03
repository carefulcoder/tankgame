#include "RenderableTank.h"

//constructor - pass our tank & its texture through to the basic vehicle sprite
RenderableTank::RenderableTank(int tankTex, int turTex, Tank& tank) : RenderableVehicle(tankTex, tank) {}

void RenderableTank::draw(Canvas &canvas) {
	RenderableVehicle::draw(canvas); //draw the body of our tank, then below cast to a tank & draw the turret.
	canvas.draw("turret", glm::rotate(glm::translate(glm::mat4(1.0f), this->vehicle.getPosition()), ((Tank&)this->vehicle).getTurretRotation(), glm::vec3(0.0f, 0.0f, 1.0f)));
}