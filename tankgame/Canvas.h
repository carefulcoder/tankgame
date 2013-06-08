#ifndef CANVAS
#define CANVAS


#include <vector>
#include <GL/glew.h>

#include <fstream>
#include <string>
#include <glm.hpp>

#include <GL/gl.h>
#include <GL/glu.h>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "TextureMapper.h"
#include <iostream>
#include <SOIL.h>
#include <locale>

class Canvas {

public:

	//constructor, aspect ratio
	Canvas(int width, int height, std::string filename, int numSprites);
	
	//draw the given texture with the given transform, repeating it x by x times
	void draw(const std::string& texture, glm::mat4 transform, glm::vec2 textureRepeat);


	//draw the given texture with the given transform
	void draw(const std::string& texture, glm::mat4 transform);

	//draw a string of text on the screen
	void text(const std::string& text, glm::vec2 start);

	//destructor
	~Canvas();

private:

	//buffers (vertex, index, texture)
	GLuint buffers[3];

	//stores the shader prog
	GLhandleARB shaderProgram;

	//add a shader to our rendering pipeline of the given type
	void addShader(GLenum type, std::string filename);

	//texture mapping for sprites
	TextureMapper mapper;

	//projection matrix
	glm::mat4 projection;

	//view matrix
	glm::mat4 view;

	//texture id
	GLuint image;

	//texture size info
	float texWidth;

	float texHeight;
};

#endif