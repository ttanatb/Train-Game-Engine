#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Object.h"

class Camera
{
private:
	GLint worldViewLoc;
	GLint camPosLoc;

	glm::mat4x4 worldViewMat;
	glm::vec3 position;

	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;

	float zoom;
	int width;
	int height;
	float zNear;
	float zFar;

	glm::mat4 calcLookAtMat();
	glm::mat4 calcProjectionMat();
public:
	Camera();
	~Camera();

	void start();
	void upload(const GLuint* shaderProgram);

	void update(float dt, GLFWwindow* window);
	//void move(float dt, GLFWwindow* window);
	//void rotate(GLFWwindow* window, float dt);
};