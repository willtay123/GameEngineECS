#pragma once

#include "Interfaces/IComponent.h"
#include "Objects/Texture.h"
#include "Managers/ResourceManager.h"
#include "CleverPointers.h"

namespace EngineECS {
	class ComponentTexture : public IComponent {
	private:
		shared_ptr<Texture> _texture;

	public:
		ComponentTexture();
		ComponentTexture(ResourceID resourceID);
		ComponentTexture(const ComponentTexture& rhs);
		~ComponentTexture();
		ComponentTexture operator=(const ComponentTexture& rhs);

		ComponentTexture* Clone();
		int ComponentType() const;
		void Message(IMessage* message);

		const shared_ptr<const Texture> GetTexture() const;
		int GetTextureID() const;
		int GetWidth() const;
		int GetHeight() const;
	};
}