#pragma once
#include "Object.h"
#include "Timer.h"
#include "Camera.h"
#include "ShaderLoader.h"
#include "Window.h"
#include "Model.h"
#include "Texture.h"
#include "Player.h"
#include "Collectible.h"
#include "EnvironmentObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <vector>

class Engine
{
private:
	static std::vector<Model> models;
	static std::vector<Texture> textures;
	static std::vector<Collectible> collectibles;
	static std::vector<EnvironmentObject> environmentObjs;
	static Player player;

	static bool bufferModels();
	static bool loadTextures();
public:
	static Timer timer;
	static Camera camera;
	static ShaderLoader shaderLoader;
	static Window window;

	Engine();
	~Engine();

	static bool init();
	static void stop();
	static void update();
};