#include "Camera.h"
#include <iostream>
# define M_PI           3.14159265358979323846f

glm::mat4 Camera::calcLookAtMat()
{
	return glm::lookAt(position, position + direction, up);
}

glm::mat4 Camera::calcProjectionMat()
{
	return glm::perspective(M_PI * .4f / zoom, (float)width / (float)height, zNear, zFar);
}

Camera::Camera() { }
Camera::~Camera() { }

void Camera::start()
{
	worldViewMat = glm::mat4();
	position = { .0f, 0.f, -2.f };
	direction = { 0, 0, 1 };
	up = { 0, 1, 0 };

	zoom = 1.f;
	width = 800;
	height = 600;
	zNear = .01f;
	zFar = 800.f;
}

void Camera::upload(const GLuint* shaderProgram)
{
	worldViewLoc = glGetUniformLocation(*shaderProgram, "worldViewMat");
	camPosLoc = glGetUniformLocation(*shaderProgram, "camLoc");
}

void Camera::update(float dt, GLFWwindow* window)
{
	//move(dt, window);
	//rotate(window, dt);

	worldViewMat = calcProjectionMat() * calcLookAtMat();
	glUniformMatrix4fv(worldViewLoc, 1, GL_FALSE, &worldViewMat[0][0]);
	glUniform3fv(camPosLoc, 1, &position[0]);
}

/*
void Camera::move(float dt, GLFWwindow* window)
{
	velocity = glm::vec3();

	if (velocity != glm::vec3()) {
		velocity = glm::normalize(velocity) * speed;
	}

	position += velocity * dt;
}

void Camera::rotate(GLFWwindow* window, float dt)
{
	direction = { 0, 0, 1 };
	up = { 0, 1, 0 };
}
*/