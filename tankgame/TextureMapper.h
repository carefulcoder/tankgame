#ifndef TEXMAPPER
#define TEXMAPPER
#include <iostream>
#include <fstream>
#include <sstream> 
#include <glm.hpp>
#include <string>
#include <map>

class TextureMapper {

public:
	TextureMapper(std::string& filename);
	glm::vec4 getCoordinates(const std::string& name);
	glm::vec2 getMaximumTextureSize();
	int countTextures();
private:
	std::map<std::string, glm::vec4> mappings;
	glm::vec2 maxSize; //max texture size
	int numTextures;
};

#endif