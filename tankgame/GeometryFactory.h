#ifndef GEOMETRYFACTORY
#define GEOMETRYFACTORY
#include "TextureMapper.h"

/**
 * Class to create geometry and UV buffers from
 * Textures from a TextureMapper
 */
class GeometryFactory {
public:
	GeometryFactory(TextureMapper& mapper)
private:
	vector<GLfloat> vertices;
	vector<GLshort> indices;
	buildVBOs();
};
#endif