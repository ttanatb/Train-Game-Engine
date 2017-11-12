#include "Object.h"
#include <ctime>
#define FLOOR_LOCATION		 0.f
#define GRAVITY_ACC			-9.8f

#include <iostream>

void Object::updateRigidBody(float dt)
{
	clearForce();
	applyForces();
	applyVelocity(dt);
	applyPosition(dt);
}

void Object::clearForce()
{
	rigidBody.force = glm::vec3(0.f);
}

void Object::applyForces()
{
}

void Object::applyVelocity(float dt)
{
	rigidBody.force /= rigidBody.mass;
	rigidBody.velocity += rigidBody.force * dt;
}

void Object::applyPosition(float dt)
{
	if (glm::length(rigidBody.velocity) > rigidBody.maxSpeed)
	{
		rigidBody.velocity = glm::normalize(rigidBody.velocity);
		rigidBody.velocity *= rigidBody.maxSpeed;
	}

	transform.location += rigidBody.velocity * dt;
}


Object::Object() { }
Object::Object(Model * model, Texture * texture, const GLuint* shaderProgram, bool useRigidBody)
{
	this->model = model;
	this->texture = texture;

	matLoc = glGetUniformLocation(*shaderProgram, "modelWorldMat");
	normMatLoc = glGetUniformLocation(*shaderProgram, "normalMat");

	transform.scale = glm::vec3(1, 1, 1);
	transform.rotation = glm::vec3(0, 0, 0);
	transform.location = glm::vec3(0, 0, 0);

	enabled = true;

	this->useRigidBody = useRigidBody;
	if (useRigidBody)
	{
		rigidBody.mass = 3.f;
		rigidBody.force = glm::vec3(0.f, 0.f, 0.f);
		rigidBody.velocity = glm::vec3(0.f, 0.f, 0.f);
		rigidBody.maxSpeed = static_cast<float>(rand() / static_cast<float>(RAND_MAX / 5)) + 1.f;
	}

	vertices = *(model->getVertexLocs());

	radius = model->getRadius();
}

Object::~Object() { }

void Object::update(float dt)
{
	if (useRigidBody) updateRigidBody(dt);

	transform.objWorldMat = glm::translate(transform.location) *
		glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z) *
		glm::scale(transform.scale);

	if (collider == Collider::aabbBox) {
		minVert = maxVert = transform.objWorldMat * vertices[0];
		for (std::vector<glm::vec4>::iterator i = vertices.begin(); i != vertices.end(); ++i) {
			glm::vec4 vert = transform.objWorldMat * glm::vec4(i->x, i->y, i->z, 1);
			
			if (vert.x < minVert.x) minVert.x = vert.x;
			else if (vert.x > maxVert.x) maxVert.x = vert.x;
			if (vert.y < minVert.y) minVert.y = vert.y;
			else if (vert.y > maxVert.y) maxVert.y = vert.y;
			if (vert.z < minVert.z) minVert.z = vert.z;
			else if (vert.z > maxVert.z) maxVert.z = vert.z;
		}
	}

	transform.normalMat = glm::transpose(glm::inverse(transform.objWorldMat));
	glUniformMatrix4fv(matLoc, 1, GL_FALSE, &(transform.objWorldMat[0][0]));
	glUniformMatrix4fv(normMatLoc, 1, GL_FALSE, &(transform.normalMat[0][0]));
}

void Object::render()
{
	if (texture != nullptr) texture->bind();
	if (model != nullptr) model->render();
}

void Object::unload() { }

bool Object::collidesWith(const Object*otherObj)
{
	if (collider == Collider::noCollider || otherObj->collider == Collider::noCollider) return false;
	if (collider == Collider::aabbBox && otherObj->collider == Collider::aabbBox)
	{
		if ((minVert.x < otherObj->maxVert.x) &&
			(minVert.y < otherObj->maxVert.y) &&
			(minVert.z < otherObj->maxVert.z) &&
			(maxVert.x > otherObj->minVert.x) &&
			(maxVert.y > otherObj->minVert.y) &&
			(maxVert.z > otherObj->minVert.z))
			return true;
		else return false;

	}
	else if (collider == Collider::sphere && otherObj->collider == Collider::sphere)
	{
		if (glm::distance2(transform.location, otherObj->transform.location) < glm::pow(radius + otherObj->radius, 2))
			return true;
		else return false;
	}
	else
	{
		float dist2 = 0;
		if (collider == Collider::sphere)
		{
			if (transform.location.x < otherObj->minVert.x)
				dist2 += glm::pow(otherObj->minVert.x - transform.location.x, 2);
			else if (transform.location.x > otherObj->maxVert.x)
				dist2 += glm::pow(transform.location.x - otherObj->maxVert.x, 2);

			if (transform.location.y < otherObj->minVert.y)
				dist2 += glm::pow(otherObj->minVert.y - transform.location.y, 2);
			else if (transform.location.y > otherObj->maxVert.y)
				dist2 += glm::pow(transform.location.y - otherObj->maxVert.x, 2);

			if (transform.location.z < otherObj->minVert.z)
				dist2 += glm::pow(otherObj->minVert.z - transform.location.z, 2);
			else if (transform.location.z > otherObj->maxVert.z)
				dist2 += glm::pow(transform.location.z - otherObj->maxVert.z, 2);

			if (dist2 < glm::pow(radius, 2)) return true;
			else return false;
		}
		else if (otherObj->collider == Collider::sphere)
		{
			if (otherObj->transform.location.x < minVert.x)
				dist2 += glm::pow(minVert.x - otherObj->transform.location.x, 2);
			else if (otherObj->transform.location.x > maxVert.x)
				dist2 += glm::pow(otherObj->transform.location.x - maxVert.x, 2);

			if (otherObj->transform.location.y < minVert.y)
				dist2 += glm::pow(minVert.y - otherObj->transform.location.y, 2);
			else if (otherObj->transform.location.y > maxVert.y)
				dist2 += glm::pow(otherObj->transform.location.y - maxVert.x, 2);

			if (otherObj->transform.location.z < minVert.z)
				dist2 += glm::pow(minVert.z - otherObj->transform.location.z, 2);
			else if (otherObj->transform.location.z > maxVert.z)
				dist2 += glm::pow(otherObj->transform.location.z - maxVert.z, 2);

			if (dist2 < glm::pow(otherObj->radius, 2)) return true;
			else return false;
		}
	}

	return false;
}
