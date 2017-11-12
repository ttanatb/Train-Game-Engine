#pragma once
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <iostream>

class ShaderLoader
{
private:
	//file names for loading files in
	std::string vertexShaderFileName;
	std::string fragmentShaderFileName;

	//shader program
	GLuint program;
	GLuint vProgram;
	GLuint fProgram;

	//helper function to read binary files
	char* readBinaryFile(std::string fileName);
public:
	//constructor & desturctor
	ShaderLoader();
	~ShaderLoader();

	bool load();						//reads and loads the files
	bool compile(GLenum shaderType);	//compiles the shaders
	void use();							//selects a shader to be used
	void unload();						//unloads all the shaders

	const GLuint* getProgram();			//get the pointer to the program GLuint
};