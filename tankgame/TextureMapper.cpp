#include "TextureMapper.h"

//init the texture mapper, loading in texture maps from a given file.	
TextureMapper::TextureMapper(std::string& filename) : mappings(std::map<std::string, glm::vec4>()), numTextures(0), maxSize(glm::vec2(0.0f))
{
	//open our map file
	std::ifstream file;
	file.open(filename);

	//temp data store
	std::string data;

	//now read in data
	if (file.is_open()) {
		while (file.good()) {

			//grab a line from the file
			std::getline(file, data);
		
			//initialise an istringstream to split the line
			std::istringstream strStream = std::istringstream(data);

			//grab the name
			std::string name;
			strStream >> name;
			glm::vec4 positions(0.0f);

			//now grab all the integers
			for (int i = 0; i < 4; i++) {
				strStream >> positions[i];
			}

			//was the format okay?
			if (!strStream.fail()) {

				//add these texture maps into our mapping map... map is a word used a lot.
				this->mappings.insert(std::pair<std::string, glm::vec4>(name, positions));
				this->maxSize.x = std::max(this->maxSize.x, positions[2]);
				this->maxSize.y = std::max(this->maxSize.y, positions[3]);
				this->numTextures++;
			}		
		}
	}
}

//get a set of co-ordinates for a given texture handle
glm::vec4 TextureMapper::getCoordinates(const std::string& name) {
	if (this->mappings.count(name) == 1) {
		return this->mappings[name];
	} else if (this->mappings.count("error") == 1) {
		return this->mappings["error"];
	} else {
		return glm::vec4(0.0f);
	}
}

glm::vec2 TextureMapper::getMaximumTextureSize() {
	return this->maxSize;
}

int TextureMapper::countTextures() {
	return this->numTextures;
}