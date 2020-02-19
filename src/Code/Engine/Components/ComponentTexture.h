#pragma once

#include <memory>
#include "Interfaces/IComponent.h"
#include "Objects/Texture.h"

#include "Managers/ResourceManager.h"

namespace EngineECS {
	class ComponentTexture : public IComponent {
	private:
		std::weak_ptr<Texture> _texture;

	public:
		ComponentTexture();
		ComponentTexture(const string& filepath);
		ComponentTexture(std::weak_ptr<Texture> texture);
		ComponentTexture(const ComponentTexture& rhs);
		~ComponentTexture();
		ComponentTexture operator=(const ComponentTexture& rhs);

		ComponentTexture* Clone();
		int ComponentType() const;
		void Message(IMessage* message);

		const std::weak_ptr<Texture> GetTexture() const;
		int GetID() const;
		int GetWidth() const;
		int GetHeight() const;
	};
}