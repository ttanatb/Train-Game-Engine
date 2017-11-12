#pragma once
#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "ShaderLoader.h"
#include <vector>

struct Vertex {
	glm::vec3 location;
	glm::vec2 uv;
	glm::vec3 normal;
};

struct VertInd {
	unsigned int locInd;
	unsigned int uvInd;
	unsigned int normInd;
};

class Model
{
private:
	unsigned int vertCount = 0;
	GLuint vertArr = 0;

	glm::vec4 minVert = glm::vec4();
	glm::vec4 maxVert = glm::vec4();
	
	std::vector<glm::vec4> vertexLocs;
public:
	Model();
	~Model();

	bool buffer(std::string filePath, ShaderLoader* shader);
	void render();
	void unload();

	const std::vector<glm::vec4>* getVertexLocs();
	float getRadius();
};