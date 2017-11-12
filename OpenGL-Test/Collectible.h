#pragma once
#include "Object.h"

//Objects that can be collected in the game
class Collectible :
	public Object
{
private:
	void applyForces() override;

	float rotationSpeed;
	float movementForce;
public:
	Collectible();
	Collectible(Model* model, Texture* texture, const GLuint* shaderProgram);
	~Collectible();

	void update(float dt) override;
	void randomizeLoc(float bounds);

};