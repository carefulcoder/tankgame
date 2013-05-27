#include "RenderableVehicle.h"
#include "Tank.h"

class RenderableTank : public RenderableVehicle {
public:
	RenderableTank(int tankTex, int turTex, Tank& tank);
	virtual void draw(Canvas &canvas);
};