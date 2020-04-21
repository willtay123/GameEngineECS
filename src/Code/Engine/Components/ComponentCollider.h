#pragma once
#include "Interfaces/IComponent.h"

#include <string>

using std::string;


namespace EngineECS {
	class ComponentCollider : public IComponent {
	private:

	protected:
		ComponentCollider();
		ComponentCollider(bool enabled);

		bool _enabled;
		string _colliderType;

	public:
		virtual ~ComponentCollider();
		virtual IComponent* Clone();

		virtual int ComponentType() const;
		virtual void Message(IMessage* message);

		virtual const string& GetColliderType();
		virtual bool IsEnabled();
		virtual void SetEnabled(bool enabled);
	};
}