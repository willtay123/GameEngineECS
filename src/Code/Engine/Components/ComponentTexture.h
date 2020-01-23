#pragma once

#include "Interfaces/IComponent.h"
#include "Objects/Texture.h"

#include "Managers/ResourceManager.h"

class ComponentTexture : public IComponent {
private:
	Texture* _texture;

public:
	ComponentTexture();
	ComponentTexture(const char* filepath);
	ComponentTexture(Texture* texture);
	ComponentTexture(const ComponentTexture& rhs);
	~ComponentTexture();
	ComponentTexture operator=(const ComponentTexture& rhs);

	ComponentTexture* Clone();
	int ComponentType() const;
	void Message(IMessage* message);

	const Texture* GetTexture() const;
	int GetID() const;
	int GetWidth() const;
	int GetHeight() const;
};