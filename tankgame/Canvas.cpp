#include "Canvas.h"

/*
 * Initialise the Sprite Engine.
 * We create an initial square shape which is textured
 * with different textures to represent sprites.
 */
Canvas::Canvas(int width, int height, std::string filename, int numSprites) {

	//initialise GLEW
	GLenum err = glewInit();

	//something is broken
	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	//generate buffers.
	GLuint buffers[3];
	glGenBuffers(3, buffers);

	//simple rectangle vertices
	GLfloat vertices[] = {
		-1,-1,-1,
		1,-1,-1,
		-1,1,-1,
		1,1,-1
	};

	//indices for the rectangle
	GLubyte indices[] = {
		3, 1, 0,
		2, 3, 0
	};

	//UV data for textures
	GLfloat textures[] = {
		0, 0,
		1, 0,
		0, 1,
		1, 1
	};

	//buffer vertex data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	//now buffer index data to GPU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//finally buffer texture UV data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

	//GL texture prereq
	glEnable(GL_TEXTURE_2D); 
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	// SOIL image loader to load our single texture atlas
	GLuint image = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, image); //below: nearest neighbour = retro
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//shaders... create our shader program first
	this->shaderProgram = glCreateProgramObjectARB();
	glUseProgramObjectARB(this->shaderProgram);

	//now load our fragment shader which is responsible
	//for adjusting UV co-ordinates per sprite for their image
	this->addShader(GL_VERTEX_SHADER_ARB, "vShader.glsl");
	this->addShader(GL_FRAGMENT_SHADER_ARB, "fShader.glsl");

	glLinkProgramARB(this->shaderProgram);
	glUseProgramObjectARB(this->shaderProgram);

	//send the number of sprites on our sprite sheet to the shaders
	int numSpritesLoc = glGetUniformLocation(this->shaderProgram, "numSprites");
	glUniform1fARB(numSpritesLoc, (float)numSprites);

	//send the texture unit we're using to the shaders.
	int texLoc = glGetUniformLocation(this->shaderProgram, "texture");
	glUniform1iARB(texLoc, 1);

	//now calculate an orthogonal perspective & initial view
	this->projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

	//texture info
	float texWidth;
	float texHeight;

	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);

	//create a transformation matrix scaling our 1x1 quad up to the size of each individual texture
	this->model = glm::scale(glm::mat4(1.0f), glm::vec3((texWidth / (float)numSprites) / 2, texHeight / 2, 1.0f));
}

/*
 * Draw our sprites onto the screen.
 */
void Canvas::draw(int textureIndex, glm::mat4 transform) {

	//let the GPU know which sprite we wish to draw
	int spriteNoLoc = glGetUniformLocation(this->shaderProgram, "spriteNo");
	glUniform1fARB(spriteNoLoc, (float)textureIndex);

	int modelLoc = glGetUniformLocation(this->shaderProgram, "mvp");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->projection * transform * model));
	
	//...and so draw the geometry. Fixed number of indices. 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

/*
 * Add a fragment or vertex shader
 */
void Canvas::addShader(GLenum type, std::string filename) {

	//read shader from a file
	std::ifstream shaderFile(filename);
	std::string line;
	std::string out;
	
	if (shaderFile.is_open()) {
		while ( shaderFile.good() ) {
			std::getline(shaderFile, line);
			out += line;
		}
		shaderFile.close();
	}

	if (out.length() == 0) {
		std::cout << "Failed to load shader! Could not find file " << filename << "\n";
		exit(1);
	}

	//convert string to C style const char *
	const char * cShader = out.c_str();

	//create our shader - a vertex shader in this case & prog obj.
	GLenum shaderObject = glCreateShaderObjectARB(type);
	
	//set source of the shader & compile it.
	glShaderSourceARB(shaderObject, 1, &cShader, NULL);
	glCompileShaderARB(shaderObject);

	//attach our vertex shader to our program, link it
	glAttachObjectARB(this->shaderProgram, shaderObject);
}