#pragma once
#include "Object.h"
class Freight :
	public Object
{
public:
	Freight();
	Freight(Model* freightModel, const GLuint* shaderProgram);

	~Freight();
};

