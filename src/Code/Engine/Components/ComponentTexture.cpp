#include "ComponentTexture.h"

using namespace EngineECS;


ComponentTexture::ComponentTexture() :
		_texture(std::weak_ptr<Texture>()) {
	_componentType = ComponentManager::GetInstance().GenerateIDByType(this);
}

ComponentTexture::ComponentTexture(const string& filepath) {
	_texture = ResourceManager::GetInstance().LoadTexture(filepath);
	_componentType = ComponentManager::GetInstance().GenerateIDByType(this);
}

ComponentTexture::ComponentTexture(std::weak_ptr<Texture> texture) :
	_texture(texture) {
	_componentType = ComponentManager::GetInstance().GenerateIDByType(this);
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

const std::weak_ptr<Texture> ComponentTexture::GetTexture() const {
	return _texture;
}

int ComponentTexture::GetID() const {
	return (!_texture.expired()) ? _texture.lock()->GetID() : 0;
}

int ComponentTexture::GetWidth() const {
	return (!_texture.expired()) ? _texture.lock()->GetWidth() : 0;
}

int ComponentTexture::GetHeight() const {
	return (!_texture.expired()) ? _texture.lock()->GetHeight() : 0;
}