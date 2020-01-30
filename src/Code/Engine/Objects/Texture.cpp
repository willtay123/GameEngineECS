#include "Texture.h"

using namespace EngineECS;


Texture::Texture(int textureID) :
	_id(textureID),
	_width(0),
	_height(0),
	_mipLevel(0) {

}

Texture::Texture(int textureID, int width, int height, int mipLevel) :
	_id(textureID),
	_width(width),
	_height(height),
	_mipLevel(mipLevel) {

}

Texture::Texture(const Texture& rhs) :
	_id(rhs._id),
	_width(rhs._width),
	_height(rhs._height),
	_mipLevel(rhs._mipLevel) {

}

Texture::~Texture() {

}

Texture& Texture::operator=(const Texture& rhs) {
	if (this != &rhs) {
		_id = rhs._id;
		_width = rhs._width;
		_height = rhs._height;
		_mipLevel = rhs._mipLevel;
	}
	return *this;
}

int Texture::GetID() {
	return _id;
}

int Texture::GetWidth() {
	return _width;
}

int Texture::GetHeight() {
	return _height;
}

int Texture::GetMipLevel() {
	return _mipLevel;
}