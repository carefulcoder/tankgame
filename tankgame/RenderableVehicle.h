#include "Renderable.h"
#include "Vehicle.h"

class RenderableVehicle : public Renderable {
public:
	RenderableVehicle(int texture, Vehicle& veh);
	virtual void draw(Canvas &canvas);
protected:
	Vehicle& vehicle;
	int textureIndex;
};