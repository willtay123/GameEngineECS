#pragma once
#include "Interfaces/IResource.h"

#include <iostream>


class Texture : public IResource {
private:
	int _id;
	int _width;
	int _height;
	int _mipLevel;

public:
	Texture(int textureID);
	Texture(int textureID, int width, int height, int mipLevel);
	Texture(const Texture& rhs);
	~Texture();
	Texture& operator=(const Texture& rhs);

	int GetID();
	int GetWidth();
	int GetHeight();
	int GetMipLevel();
};