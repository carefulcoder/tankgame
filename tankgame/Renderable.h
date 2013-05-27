#ifndef RENDERABLE
#define RENDERABLE

#include "Canvas.h"

class Renderable {
public:
	virtual void draw(Canvas& canvas) = 0;
};

#endif