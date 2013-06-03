#include "Canvas.h"

/*
 * Initialise the Sprite Engine.
 * We create an initial square shape which is textured
 * with different textures to represent sprites.
 */
Canvas::Canvas(int width, int height, std::string filename, int numSprites) : mapper(TextureMapper((filename + ".txt"))) {

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
	GLuint image = SOIL_load_OGL_texture((filename + ".png").c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);

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

	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->texWidth);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->texHeight);
}

/*
 * Draw our sprites onto the screen.
 */
void Canvas::draw(const std::string& texture, glm::mat4 transform) {

	//grab the UV texture maps of the image we want to draw
	glm::vec4 uvs = this->mapper.getCoordinates(texture);

	//create a transformation matrix scaling our 1x1 quad up to the size of the texture we're about to draw
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(uvs[2] / 2, uvs[3] / 2, 1.0f));

	//convert into normalised distances (so 32 is 0.5 of a 64px texture width, etc)
	uvs[2] = (uvs[0] + uvs[2]) / this->texWidth;  //x width to x end UV
	uvs[3] = (uvs[1] + uvs[3]) / this->texHeight; // y width to y end UV
	uvs[1] /= texHeight;
	uvs[0] /= texWidth;
	
	//send our UV vec4 to the vertex shader to be applied to the UV data
	int uvVecLoc = glGetUniformLocation(this->shaderProgram, "uvs");
	glUniform4fARB(uvVecLoc, uvs[0], uvs[1], uvs[2], uvs[3]);

	int modelLoc = glGetUniformLocation(this->shaderProgram, "mvp");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->projection * transform * model));
	
	//...and so draw the geometry. Fixed number of indices. 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

//helper method to draw sprite text onto the screen
void Canvas::text(const std::string& text, glm::vec2 start) {

	glm::vec3 translate = glm::vec3(start, 0.0f);
	for (int i = 0; i < text.length(); i++) {

		//grab the letter to draw
		std::string letter = text.substr(i, 1);

		//handle spaces
		if (letter == " ") {
			letter = "space";
		}

		glm::vec4 coords = this->mapper.getCoordinates(letter);
		this->draw(letter, glm::translate(glm::mat4(1.0f), translate));			
		translate.x += coords[2]; //2 = x width
	}
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