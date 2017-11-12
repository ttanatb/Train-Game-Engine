#include "ShaderLoader.h"

ShaderLoader::ShaderLoader()
{
	vertexShaderFileName = "shaders/vertexShader.glsl";
	fragmentShaderFileName = "shaders/fragmentShader.glsl";
}

ShaderLoader::~ShaderLoader()
{
	unload();
}

bool ShaderLoader::load()
{
	//compiles the shader source
	if (!compile(GL_VERTEX_SHADER) || !compile(GL_FRAGMENT_SHADER))
	{
		std::cout << "Failed to compile shader(s)" <<std::endl;
		return false;
	}

	//create a program and link the vertex and fragment shaders
	program = glCreateProgram();
	glAttachShader(program, vProgram);
	glAttachShader(program, fProgram);
	glLinkProgram(program);

	//get shader compilation results
	GLint ivResults;
	glGetProgramiv(program, GL_LINK_STATUS, &ivResults);
	if (ivResults == GL_TRUE)
	{
		std::cout << "Shader compiled correctly";
		return true;
	}
	else
	{
		//log out error
		GLint length;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[255];
		glGetProgramInfoLog(program, 255, NULL, log);
		std::cout << log;

		glDeleteProgram(program);
		delete[] log;
		return false;
	}
}

char * ShaderLoader::readBinaryFile(std::string filename)
{
	// Open in binary reading mode
	std::ifstream instream(filename, std::ios::binary);
	//binary -- easy to parse ints, can read whole thing at once

	if (!instream.is_open()) return nullptr;

	// get length
	instream.seekg(0, std::ios::end);
	int length = (int)instream.tellg();
	instream.seekg(0, std::ios::beg);

	// read
	char* bytes = new char[length + 1];
	bytes[length] = '\0';
	instream.read(bytes, length);

	// close
	instream.close();

	return bytes;
}

bool ShaderLoader::compile(GLenum shaderType)
{
	char* shaderSource;
	if (shaderType == GL_VERTEX_SHADER)
	{
		shaderSource = readBinaryFile(vertexShaderFileName);
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		shaderSource = readBinaryFile(fragmentShaderFileName);
	}
	else
	{
		std::cout << "Wrong shaderType\n";
		return false;
	}

	//creates the shader program
	GLuint shaderProgram = glCreateShader(shaderType);
	glShaderSource(shaderProgram, 1, &shaderSource, NULL);
	glCompileShader(shaderProgram);

	delete[] shaderSource;

	//compiles it
	GLint compileResults;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &compileResults);

	if (compileResults != 0) {

		//assign the shader to the right pointer if compilation is successful
		if (shaderType == GL_VERTEX_SHADER)
		{
			vProgram = shaderProgram;
		}
		else if (shaderType == GL_FRAGMENT_SHADER)
		{
			fProgram = shaderProgram;
		}
		return true;
	}
	else {

		//log out errors
		GLint length;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetShaderInfoLog(shaderProgram, length, NULL, log);
		std::cout << "Compilation for shader type: ";
		if (shaderType == GL_VERTEX_SHADER) {
			std::cout << "Vertex Shader" << std::endl;
		}
		else { 
			std::cout << "Fragment Shader" << std::endl; 
		}
		std::cout << log << std::endl;

		glDeleteShader(shaderProgram);
		delete[] log;
		return false;
	}
}

void ShaderLoader::use()
{
	glUseProgram(program);
}

void ShaderLoader::unload()
{
	glDeleteProgram(program);
	glDeleteShader(vProgram);
	glDeleteShader(fProgram);

	program = vProgram = fProgram = 0;
}

const GLuint* ShaderLoader::getProgram()
{
	return &program;
}
