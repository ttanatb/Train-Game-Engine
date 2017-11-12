#pragma once
#include "Object.h"
#include "Freight.h"
#include "Wheel.h"
#include <GLFW/glfw3.h>
#define SCREEN_BOUNDS		1.45f
#define WHEEL_COUNT			4

//The class for player (train)
class Player :
	public Object
{
private:
	Wheel wheels[WHEEL_COUNT];
	Freight freight;

	void updateRigidBody(float dt) override;
	void applyForces() override;
public:
	Player();
	Player(Model* model, Texture* texture, const GLuint* shaderProgram);
	Player(Model* mainTrainModel, Model* freightModel, Model* wheelModel, Texture* texture, const GLuint* shaderProgram);
	~Player();

	void update(float dt) override;
};

