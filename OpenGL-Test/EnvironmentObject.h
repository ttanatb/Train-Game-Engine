#pragma once
#include "Object.h"

//fast moving lines that simulate space environment
class EnvironmentObject :
	public Object
{
private:
	void applyForces() override;

	float zPos;
	float movementSpeed;
public:
	EnvironmentObject();
	EnvironmentObject(Model* model, Texture* texture, const GLuint* shaderProgram);

	~EnvironmentObject();
	void update(float dt) override;
};