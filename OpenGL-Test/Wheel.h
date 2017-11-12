#pragma once
#include "Object.h"
class Wheel :
	public Object
{
public:
	Wheel();
	Wheel(Model* wheelModel, const GLuint* shaderProgram);

	~Wheel();
};