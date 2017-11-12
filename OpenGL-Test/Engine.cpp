#include "Engine.h"
#include <iostream>

Timer Engine::timer;
Camera Engine::camera;
ShaderLoader Engine::shaderLoader;
Window Engine::window;
std::vector<Model> Engine::models;
std::vector<Texture> Engine::textures;
std::vector<Collectible> Engine::collectibles;
std::vector<EnvironmentObject> Engine::environmentObjs;
Player Engine::player;

//loads in all the models
bool Engine::bufferModels()
{
	std::string modelSrcs[] = { "diamond.obj", "emerald.obj", "lapisLazuli.obj", "coin.obj", "frontTrain.obj",  
		"freight.obj" , "wheels.obj", "spaceLights.obj" };
	for (int i = 0; i < sizeof(modelSrcs) / sizeof(std::string); i++) {
		models.push_back(Model());
		if (!models[i].buffer("models/" + modelSrcs[i], &shaderLoader))
			return false;
	}

	return true;
}

//loads in all the textures
bool Engine::loadTextures()
{
	std::string textureSrcs[] = { "jewelTexture.png", "spaceEnv.png", "trainTexture.png" };
	for (int i = 0; i < sizeof(textureSrcs) / sizeof(std::string); i++)
	{
		textures.push_back(Texture());
		textureSrcs[i] = "textures/" + textureSrcs[i];
		if (!textures[i].load(textureSrcs[i].c_str()))
			return false;
	}

	return true;
}

Engine::Engine() { }
Engine::~Engine() { }

//Initialization logic
bool Engine::init()
{
	window.start();
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	if (shaderLoader.load()) 
		shaderLoader.use();
	else return false;

	if (!bufferModels()) return false;
	if (!loadTextures()) return false;

	timer = Timer();
	camera.start();
	camera.upload(shaderLoader.getProgram());

	for (int i = 0; i < 200; i++) {
		int randNum = rand() % 4;
		collectibles.push_back(Collectible(&(models[randNum]), &(textures[0]), shaderLoader.getProgram()));
		collectibles[i].randomizeLoc(SCREEN_BOUNDS);
	}

	for (int i = 0; i < 100; i++) {
		environmentObjs.push_back(EnvironmentObject(&models[7], &textures[1], shaderLoader.getProgram()));
	}
	
	player = Player(&models[4], &models[5], &models[6], &textures[2], shaderLoader.getProgram());

	return true;
}

void Engine::stop()
{
	glfwTerminate();
}

void Engine::update()
{
	//sets light at {5, -3, 0}
	GLint lightPosLoc = glGetUniformLocation(*(shaderLoader.getProgram()), "lightLoc");
	glm::vec3 lightPos = glm::vec3(5, -3, 0);
	glUniform3fv(lightPosLoc, 1, &lightPos[0]);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glClearColor(36.f / 255.f, 27.f / 255.f, 65.f / 255.f, 1.0f);

	while (!glfwWindowShouldClose(window.GLFWwindowPtr)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		timer.update();

		for (std::vector<Collectible>::iterator i = collectibles.begin(); i != collectibles.end(); ++i) {
			if (!i->enabled) continue;	//skips if disabled
			i->update(timer.dt);
			i->render();
			if (player.collidesWith(&(*i))) i->enabled = false;
			else if (i->transform.location.z < -3.f) i->enabled = false;
		}

		for (std::vector<EnvironmentObject>::iterator i = environmentObjs.begin(); i != environmentObjs.end(); ++i) {
			i->update(timer.dt);
			i->render();
		}

		player.update(timer.dt);
		camera.update(timer.dt, window.GLFWwindowPtr);
		window.update();

		glfwPollEvents();

		if (glfwGetKey(window.GLFWwindowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			break;
	}

	shaderLoader.unload();
	for (std::vector<Texture>::iterator i = textures.begin(); i != textures.end(); ++i) {
		i->unload();
	}
	for (std::vector<Model>::iterator i = models.begin(); i != models.end(); ++i) {
		i->unload();
	}

}
