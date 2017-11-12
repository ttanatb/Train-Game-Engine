#include "EnvironmentObject.h"

void EnvironmentObject::applyForces()
{
	rigidBody.force += glm::vec3(0, 0, -movementSpeed);
}

EnvironmentObject::EnvironmentObject() { }

EnvironmentObject::EnvironmentObject(Model * model, Texture * texture, const GLuint * shaderProgram)
	: Object(model, texture, shaderProgram, true)
{
	collider = Collider::noCollider;
	rigidBody.maxSpeed = static_cast<float>(rand() / static_cast<float>(RAND_MAX / 15)) + 10.f; // 10 - 25
	movementSpeed = static_cast<float>(rand() / static_cast<float>(RAND_MAX / 25)) + 30; // 30 - 55

	//sets position
	float posX = static_cast<float>(rand() / static_cast<float>(RAND_MAX / 3)) + 1;
	if (rand() % 2 == 0) posX = -posX;
	float posY = static_cast<float>(rand() / static_cast<float>(RAND_MAX / 4));
	if (rand() % 2 == 0) posY = -posY;
	zPos = static_cast<float>(rand() / static_cast<float>(RAND_MAX / 30)) + 30.f;
	
	transform.location.x = posX;
	transform.location.y = posY;
	transform.location.z = zPos - static_cast<float>(rand() / static_cast<float>(RAND_MAX / 30));
}

EnvironmentObject::~EnvironmentObject() { }

void EnvironmentObject::update(float dt)
{
	Object::update(dt);
	
	//puts the obj back at the end of the screen
	if (transform.location.z < -3.f) transform.location.z += zPos;
}
