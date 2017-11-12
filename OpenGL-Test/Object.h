#pragma once
#include <string>
#include "Texture.h"
#include "Model.h"
#include "ShaderLoader.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

struct Transform {
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 forward;
	glm::mat4 objWorldMat;
	glm::mat4 normalMat;
};

struct RigidBody {
	glm::vec3 velocity;
	glm::vec3 force;
	float maxSpeed;
	float mass;
};

enum Collider {
	noCollider,
	aabbBox,
	sphere,
};

class Object
{
protected:
	Model* model;
	Texture* texture;
	ShaderLoader shader;
	GLuint matLoc;
	GLuint normMatLoc;

	//used for collision detection
	glm::vec4 minVert;
	glm::vec4 maxVert;
	std::vector<glm::vec4> vertices;
	float radius;
	
	bool useRigidBody;
	virtual void updateRigidBody(float dt);

	void clearForce();
	virtual void applyForces();
	void applyVelocity(float dt);
	void applyPosition(float dt);

public:
	RigidBody rigidBody;
	Transform transform;
	Collider collider = Collider::noCollider;
	bool enabled;

	Object();
	Object(Model* model, Texture* texture, const GLuint* shaderProgram, bool useRigidBody);
	virtual ~Object();

	virtual void update(float dt);
	virtual void render();
	virtual void unload();
	
	bool collidesWith(const Object *otherObj);
};