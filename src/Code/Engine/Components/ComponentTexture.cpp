#include "ComponentTexture.h"

using namespace EngineECS;


ComponentTexture::ComponentTexture() :
		_texture() {
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTexture));
}

ComponentTexture::ComponentTexture(ResourceID texture) :
	_texture(texture) {
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentTexture));
}

ComponentTexture::ComponentTexture(const ComponentTexture& rhs) :
	_texture(rhs._texture) {
	_componentType = rhs._componentType;
}

ComponentTexture::~ComponentTexture() {
	// TODO: should delete the texture, but other things may be using it, so tell resource manager to delete it? or override texture delete to implement a counter
}

ComponentTexture ComponentTexture::operator=(const ComponentTexture& rhs) {
	if (this != &rhs) {
		_componentType = rhs._componentType;
		_texture = rhs._texture;
	}
	return *this;
}

ComponentTexture* ComponentTexture::Clone() {
	ComponentTexture* clone = new ComponentTexture(*this);
	return clone;
}

int ComponentTexture::ComponentType() const {
	return _componentType;
}

void ComponentTexture::Message(IMessage* message) {

}

ResourceID ComponentTexture::GetTexture() const {
	return _texture;
}

int ComponentTexture::GetID() const {
	return _texture._resourceID;
}

int ComponentTexture::GetWidth() const {
	return 0;
}

int ComponentTexture::GetHeight() const {
	return 0;
}