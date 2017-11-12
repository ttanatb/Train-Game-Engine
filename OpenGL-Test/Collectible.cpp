#include "Collectible.h"

void Collectible::applyForces()
{
	rigidBody.force += glm::vec3(0, 0, -movementForce);
}

Collectible::Collectible() { }

Collectible::Collectible(Model * model, Texture * texture, const GLuint * shaderProgram) :
	Object(model, texture, shaderProgram, true) 
{
	collider = Collider::sphere;
	rotationSpeed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2)) + 0.5f;
	movementForce = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.5f)) + 1.5f;
}

Collectible::~Collectible()  { }

void Collectible::update(float dt)
{
	//spins the thing
	transform.rotation.y += rotationSpeed * dt;

	Object::update(dt);
}

void Collectible::randomizeLoc(float bounds)
{
	transform.location = { -bounds + static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / (bounds + bounds))),
		-bounds + static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / (bounds * 2))),
		static_cast<float>(rand()) / static_cast<float> (RAND_MAX / 200)
	};

	transform.rotation = { static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / 3.f)),
		0,
		static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / 3.f))
	};
}