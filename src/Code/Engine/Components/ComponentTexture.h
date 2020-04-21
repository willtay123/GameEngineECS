#pragma once

#include "Interfaces/IComponent.h"
#include "Objects/Texture.h"
#include "Managers/ResourceManager.h"
#include "CleverPointers.h"

namespace EngineECS {
	class ComponentTexture : public IComponent {
	private:
		ResourceID _texture;

	public:
		ComponentTexture();
		ComponentTexture(ResourceID texture);
		ComponentTexture(const ComponentTexture& rhs);
		~ComponentTexture();
		ComponentTexture operator=(const ComponentTexture& rhs);

		ComponentTexture* Clone();
		int ComponentType() const;
		void Message(IMessage* message);

		ResourceID GetTexture() const;
		int GetID() const;
		int GetWidth() const;
		int GetHeight() const;
	};
}