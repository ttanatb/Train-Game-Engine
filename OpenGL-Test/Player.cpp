#include "Player.h"
#include <iostream>

#define MOVEMENT_FORCE		4.f
#define FRICTION_RATE		1.f

void Player::updateRigidBody(float dt)
{
	clearForce();
	applyForces();
	applyVelocity(dt);

	//collision resolution
	if (transform.location.y < -SCREEN_BOUNDS)
	{
		rigidBody.velocity.y = 0;
		transform.location.y = -SCREEN_BOUNDS;
	}
	else if (transform.location.y > SCREEN_BOUNDS) {
		rigidBody.velocity.y = 0;
		transform.location.y = SCREEN_BOUNDS;
	}

	if (transform.location.x < -SCREEN_BOUNDS)
	{
		rigidBody.velocity.x = 0;
		transform.location.x = -SCREEN_BOUNDS;
	}
	else if (transform.location.x > SCREEN_BOUNDS) {
		rigidBody.velocity.x = 0;
		transform.location.x = SCREEN_BOUNDS;
	}

	applyPosition(dt);
}

//applies forces based on button input
void Player::applyForces()
{
	GLFWwindow* window = glfwGetCurrentContext();
	if (glfwGetKey(window, GLFW_KEY_A)) {
		rigidBody.force += glm::vec3(MOVEMENT_FORCE, 0, 0);
	}
	else if (glfwGetKey(window, GLFW_KEY_D)) {
		rigidBody.force -= glm::vec3(MOVEMENT_FORCE, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		rigidBody.force += glm::vec3(0, MOVEMENT_FORCE, 0);
	}
	else if (glfwGetKey(window, GLFW_KEY_S)) {
		rigidBody.force -= glm::vec3(0, MOVEMENT_FORCE, 0);
	}

	//std::cout << sin(transform.rotation.x) * cos(transform.rotation.z);
	//std::cout << cos(transform.rotation.x) * cos(transform.rotation.z);
	//std::cout << sin(transform.rotation.z);
	/*if (glfwGetKey(window, GLFW_KEY_W)) {
		rigidBody.force += -3.f * glm::vec3(0, 0, 1);
	}
	else if (glfwGetKey(window, GLFW_KEY_S)) {
		rigidBody.force += 3.f * glm::vec3(0, 0, -1);
	}*/

	rigidBody.force -= FRICTION_RATE *  rigidBody.velocity;
}

Player::Player() { }
Player::Player(Model* model, Texture* texture, const GLuint* shaderProgram) : 
	Object(model, texture, shaderProgram, true) { }

Player::Player(Model* mainTrainModel, Model* freightModel, Model* wheelModel, Texture* texture, const GLuint* shaderProgram) : 
	Object(mainTrainModel, texture, shaderProgram, true)
{
	collider = Collider::aabbBox;
	transform.location = glm::vec3(-1, -1, 0.f);

	freight = Freight(freightModel, shaderProgram);
	for (int i = 0; i < WHEEL_COUNT; i++) 
	{
		wheels[i] = Wheel(wheelModel, shaderProgram);
		wheels[i].transform.rotation = transform.rotation;
		if (i % 2 == 0) {
			wheels[i].transform.rotation.y = 1.8f;
		}
	}
}

Player::~Player() { }

//updates, then renders each part
void Player::update(float dt)
{
	glm::vec3 prevRot = transform.rotation;

	Object::update(dt);
	Object::render();

	//sets the transforms for the freight
	freight.transform.location = glm::vec3(transform.objWorldMat * glm::vec4(0, 0, -.638f, 1));
	freight.transform.rotation = prevRot;
	
	freight.update(dt);
	freight.render();

	for (int i = 0; i < WHEEL_COUNT; i++) {
		//repositioning the wheel
		wheels[i].transform.location = glm::vec3(transform.objWorldMat * glm::vec4(-.0f, -.2205f, -.0 - .448f * i, 1));
		wheels[i].transform.rotation.x = transform.rotation.x;
		wheels[i].transform.rotation.z = transform.rotation.z;

		//adjust the wheels rotation based on speed (faking animation)
		if (i % 2 == 0) 
			wheels[i].transform.rotation.y += (2.f * glm::length2(rigidBody.velocity) + 2.f) * dt;
		else wheels[i].transform.rotation.y -= (2.f * glm::length2(rigidBody.velocity) + 2.f) * dt;
		//updates and renders the wheels
		wheels[i].update(dt);
		wheels[i].render();
	}
}