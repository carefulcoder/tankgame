#include "RenderableVehicle.h"

//construct our sprite vehicle, initialising all relevant fields.
RenderableVehicle::RenderableVehicle(int texture, Vehicle& veh) : Renderable(), vehicle(veh), textureIndex(texture) {}

void RenderableVehicle::draw(Canvas &canvas) {
	this->vehicle.tick(); //update internal stuff
	canvas.draw("tank", this->vehicle.getTransform());
}