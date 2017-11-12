#pragma once
#include <GL/glew.h>
#include <FreeImage.h>
#include <string>

class Texture
{
private:
	GLuint texID;
	GLsizei width;
	GLsizei height;
	BYTE* address;

public:
	Texture();
	~Texture();

	bool load(const char* fileSrc);
	void unload();

	void bind();
};

