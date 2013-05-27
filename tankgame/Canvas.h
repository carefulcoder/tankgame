#ifndef CANVAS
#define CANVAS

#include <vector>
#include <GL/glew.h>
#include <fstream>
#include <string>
#include <glm.hpp>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <SOIL.h>

class Canvas {

public:

	//constructor, aspect ratio
	Canvas(int width, int height, std::string filename, int numSprites);
	
	//draw the given texture with the given transform
	void draw(int textureIndex, glm::mat4 transform);

private:

	//stores the shader prog
	GLhandleARB shaderProgram;

	//add a shader to our rendering pipeline of the given type
	void addShader(GLenum type, std::string filename);

	//projection matrix
	glm::mat4 projection;

	//view matrix
	glm::mat4 view;

	//global model transforms
	glm::mat4 model;
};

#endif