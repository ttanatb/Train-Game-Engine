#include "Texture.h"
#include <iostream>

Texture::Texture() { }
Texture::~Texture() { }

bool Texture::load(const char* fileSrc)
{
	FREE_IMAGE_FORMAT type = FreeImage_GetFileType(fileSrc);
	FIBITMAP* image = FreeImage_Load(type, fileSrc);
	if (image == nullptr)
	{
		std::cout << "Texture at '" << fileSrc << "' could not be found" << std::endl;
		return false;
	}

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);

	width = FreeImage_GetWidth(image32Bit);
	height = FreeImage_GetHeight(image32Bit);
	address = FreeImage_GetBits(image32Bit);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	FreeImage_Unload(image32Bit);

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void Texture::unload()
{
	glDeleteTextures(1, &(texID));
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, texID);
}
